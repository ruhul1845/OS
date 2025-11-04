#ifndef _TASK_H_
#define _TASK_H_

#include <stdint.h>

/* Magic number to detect stack corruption or invalid TCB */
#define TASK_MAGIC 0xFECABAA0

/* Task states */
typedef enum
{
    TASK_UNUSED = 0,
    TASK_READY,
    TASK_RUNNING,
    TASK_WAITING,
    TASK_KILLED,
    TASK_TERMINATED
} task_state_t;

/* Full-featured Task Control Block */
typedef struct tcb
{
    uint32_t magic_number;       // Integrity check (0xFECABAA0)
    uint16_t task_id;            // Unique 16-bit task ID
    void *psp;                   // Task stack pointer
    uint16_t state;              // Current task state
    uint8_t priority;            // Lower = higher priority
    uint16_t parent_id;          // Parent process/task ID
    uint32_t execution_time;     // Total execution time in ms
    uint32_t waiting_time;       // Total waiting time in ms
    uint32_t digital_signature;  // Integrity signature (e.g., 0x00000001)
    uint32_t w_chld[16];         // Suspended child task IDs or signals
    uint32_t *heap_mem_start;    // Start address of task heap
    uint32_t heap_mem_size;      // Heap size in bytes
    uint32_t *open_resources[8]; // Pointers to opened files/devices
    uint8_t sem_waiting_count;   // Number of semaphores task waits on
    uint8_t mutex_locked_count;  // Number of mutexes locked
    uint32_t last_wakeup_time;   // Last wakeup time in ms
    struct tcb *next;            // Next task (for ready/wait queue)
} tcb_t;

/* Pointer to current running task */
extern tcb_t *current_tcb;

/* Function prototypes */
void task_init(tcb_t *task, void (*task_func)(void), uint8_t *stack, uint32_t stack_size, uint8_t priority);
void task_set_state(tcb_t *task, task_state_t new_state);
void task_print_info(tcb_t *task);

#endif /* _TASK_H_ */
