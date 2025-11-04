#include "task.h"
#include <string.h>
#include <kern/include/kstdio.h>

tcb_t *current_tcb = NULL;

/* Initialize a task control block */
void task_init(tcb_t *task, void (*task_func)(void), uint8_t *stack, uint32_t stack_size, uint8_t priority)
{
    memset(task, 0, sizeof(tcb_t));
    task->magic_number = TASK_MAGIC;
    task->task_id = 1000; /* You may auto-increment in future */
    task->psp = (void *)(stack + stack_size - 16 * 4); /* initial stack top */
    task->state = TASK_READY;
    task->priority = priority;
    task->digital_signature = 0x00000001;
    task->heap_mem_start = NULL;
    task->heap_mem_size = 0;
    task->sem_waiting_count = 0;
    task->mutex_locked_count = 0;
    task->next = NULL;

    /* Simulate initial stack frame for context switch */
    uint32_t *stk = (uint32_t *)task->psp;
    stk[15] = 0x01000000;            // xPSR
    stk[14] = (uint32_t)task_func;   // PC
    stk[13] = 0xFFFFFFFD;            // LR (return to thread mode using PSP)
}

/* Change task state */
void task_set_state(tcb_t *task, task_state_t new_state)
{
    if (task && task->magic_number == TASK_MAGIC)
        task->state = new_state;
}

/* Debug info print */
void task_print_info(tcb_t *task)
{
    if (!task || task->magic_number != TASK_MAGIC)
        return;
    kprintf("[Task %d] state=%d, prio=%d, exec=%lu, wait=%lu\n",
            task->task_id, task->state, task->priority,
            task->execution_time, task->waiting_time);
}
