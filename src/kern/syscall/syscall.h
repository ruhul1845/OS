#ifndef _SYSCALL_H_
#define _SYSCALL_H_
#include <stdint.h>

/* SVC handler C entry */
void SVC_Handler_C(uint32_t *svc_args);

/* syscall dispatch */
int do_syscall(uint32_t svc_num, uint32_t *args);

#endif
