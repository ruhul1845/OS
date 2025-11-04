/*
 * SysTick Handler
 * ---------------
 * Runs every 1 ms (as configured in __SysTick_init(1000)).
 * Every 10 ms, it triggers PendSV to request a context switch.
 */

#include <stdint.h>

volatile uint32_t sys_tick_count = 0;  // global tick counter

void SysTick_Handler(void)
{
    sys_tick_count++;

    /* Trigger PendSV every 10 ms */
    if ((sys_tick_count % 10) == 0)
    {
        volatile uint32_t *ICSR = (uint32_t *)0xE000ED04;  // Interrupt Control and State Register
        const uint32_t PENDSVSET = (1U << 28);
        *ICSR = PENDSVSET;  // set PendSV pending bit
    }
}
