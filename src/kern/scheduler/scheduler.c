#include "scheduler.h"
#include "task.h"
#include <stddef.h>

static tcb_t *ready_queue_head = NULL;
tcb_t *current_tcb = NULL;
static uint16_t next_task_id = 1000;

void scheduler_init(void)
{
    ready_queue_head = NULL;
    current_tcb = NULL;
    next_task_id = 1000;
}

/* Add task to end of ready queue */
void scheduler_add_task(tcb_t *task)
{
    if (!task) return;
    task->magic_number = TASK_MAGIC;
    task->task_id = next_task_id++;
    task->state = TASK_READY;
    task->next = NULL;

    if (ready_queue_head == NULL) {
        ready_queue_head = task;
    } else {
        tcb_t *p = ready_queue_head;
        while (p->next) p = p->next;
        p->next = task;
    }

    if (current_tcb == NULL) {
        current_tcb = ready_queue_head;
        current_tcb->state = TASK_RUNNING;
    }
}

/* Rotate ready queue and pick next runnable task (skips terminated) */
void schedule_next(void)
{
    if (ready_queue_head == NULL) {
        current_tcb = NULL;
        return;
    }

    /* remove any terminated tasks from head */
    while (ready_queue_head && ready_queue_head->state == TASK_TERMINATED) {
        tcb_t *dead = ready_queue_head;
        ready_queue_head = dead->next;
        dead->next = NULL;
    }
    if (ready_queue_head == NULL) { current_tcb = NULL; return; }

    /* only one runnable task -> keep it */
    if (ready_queue_head->next == NULL) {
        current_tcb = ready_queue_head;
        current_tcb->state = TASK_RUNNING;
        return;
    }

    /* rotate head -> tail */
    tcb_t *old = ready_queue_head;
    ready_queue_head = old->next;
    old->next = NULL;
    tcb_t *q = ready_queue_head;
    while (q->next) q = q->next;
    q->next = old;

    if (current_tcb) current_tcb->state = TASK_READY;
    current_tcb = ready_queue_head;
    current_tcb->state = TASK_RUNNING;
}

/* Request PendSV for context switch */
void scheduler_yield(void)
{
    volatile uint32_t *ICSR = (uint32_t *)0xE000ED04;
    const uint32_t PENDSVSET = (1U << 28);
    *ICSR |= PENDSVSET;
}

tcb_t *scheduler_current(void)
{
    return current_tcb;
}
