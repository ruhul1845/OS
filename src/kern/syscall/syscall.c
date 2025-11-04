#include "syscall.h"
#include "syscall_def.h"
#include <stdint.h>
#include <kstdio.h>
#include <UsartRingBuffer.h>
#include <system_config.h>
#include <scheduler.h>
#include <kstring.h>

#include <sys_usart.h>  // For noIntSendString

/*
 * Minimal syscall dispatcher implementation.
 *
 * The SVC handler in assembly will pass a pointer to the stacked registers:
 * stacked_r0 = stack_frame[0]
 * stacked_r1 = stack_frame[1]
 * stacked_r2 = stack_frame[2]
 * stacked_r3 = stack_frame[3]
 * stacked_r12= stack_frame[4]
 * stacked_lr = stack_frame[5]
 * stacked_pc = stack_frame[6]
 * stacked_psr= stack_frame[7]
 *
 * The SVC number is encoded in the SVC instruction immediate.
 * We extract it by reading the SVC opcode at PC-2 (Thumb).
 */

/* forward */
extern UART_HandleTypeDef huart2; /* __CONSOLE in system_config.h points to &huart2 */

static inline uint8_t extract_svc_number(uint32_t stacked_pc)
{
	uint16_t *instr = (uint16_t *)(stacked_pc - 2);
	uint16_t svc_instr = *instr;
	/* SVC (Thumb) encoding: 0xDF00 | imm8 */
	return (uint8_t)(svc_instr & 0xFF);
}

int do_syscall(uint32_t svc_num, uint32_t *args)
{
	switch (svc_num)
	{
    case SYS_write:
    {
        int fd = (int)args[0];
        char *buf = (char *)args[1];
        int size = (int)args[2];

        if (fd != 1) return -1;
        if (size <= 0) return 0;

        /* send in small NUL-terminated chunks using existing API */
        int sent = 0;
        while (sent < size) {

            if (buf[sent] == '\0') break;   // ✅ STOP AT STRING END

            int chunk = (size - sent) < 256 ? (size - sent) : 256;

            char tmp[257];
            int real = 0;

            // copy only printable part
            while (real < chunk && buf[sent + real] != '\0')
                tmp[real] = buf[sent + real], real++;

            tmp[real] = '\0';

            noIntSendString(__CONSOLE, tmp);

            sent += real;
        }

        return sent;
    }

	case SYS_read:
	{
		int fd = (int)args[0];
		char *buf = (char *)args[1];
		int size = (int)args[2];
		if (fd == 0) /* STDIN_FILENO */
		{
			int i = 0;
			int c;
			while (i < size - 1)
			{
				c = Uart_read(__CONSOLE);
				if (c < 0)
					continue;
				buf[i++] = (char)c;
				if ((char)c == '\n')
					break;
			}
			buf[i] = 0;
			return i;
		}
		return -1;
	}
	case SYS_getpid:
	{
		/* For now return a dummy pid */
		return 1000;
	}
	case SYS___time:
	{
		extern uint32_t __getTime(void);
		return (int)__getTime();
	}
	// case SYS__exit:
	// {
	// 	/* mark task terminated; for now just yield */
	// 	/* trigger PendSV or set flag - simplified: return code */
	// 	extern tcb_t *current_tcb;
	// 	current_tcb->state = TASK_TERMINATED;

	// 	/* PendSV bit (bit 28) in ICSR */
	// 	volatile uint32_t *ICSR = (uint32_t *)0xE000ED04;
	// 	const uint32_t PENDSVSET = (1 << 28);
	// 	*ICSR |= PENDSVSET;
	// }
	
	case SYS_reboot:
	{
		/* Perform a system reset using AIRCR */
		volatile uint32_t *AIRCR = (uint32_t *)0xE000ED0C;
		const uint32_t VECTKEY = 0x5FA << 16;
		*AIRCR = VECTKEY | (1 << 2);
		while (1)
			;
		return 0;
	}
	case SYS_yield:
	{
		/* trigger PendSV by setting PENDSVSET bit */
		volatile uint32_t *ICSR = (uint32_t *)0xE000ED04;
		const uint32_t PENDSVSET = (1 << 28);
		*ICSR |= PENDSVSET;
		return 0;
	}
	default:
		return -1;
	}
}

/* This is the C entry called from the assembly SVC handler */
void SVC_Handler_C(uint32_t *svc_args)
{
	uint32_t stacked_pc = svc_args[6];
	uint8_t svc_number = extract_svc_number(stacked_pc);
	/* svc_args[0..3] contain r0..r3 */
	int ret = do_syscall((uint32_t)svc_number, svc_args);
	/* place return value in r0 for the interrupted context */
	svc_args[0] = (uint32_t)ret;
}
