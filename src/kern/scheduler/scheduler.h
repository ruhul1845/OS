#ifndef _SCHEDULER_H_
#define _SCHEDULER_H_
#include "task.h"

void scheduler_init(void);
void scheduler_add_task(tcb_t *task);
void schedule_next(void);       /* rotates ready queue; called by PendSV assembly */
void scheduler_yield(void);      /* sets PendSV pending */
tcb_t *scheduler_current(void);

#endif
