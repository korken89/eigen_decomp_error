#include <cstdint>

/**
 * @brief Unhandled exception definition.
 */
extern "C"
{
void _unhandled_exception(void)
{
  while(1);
}
void Reset_Handler(void) __attribute__((weak, alias("_unhandled_exception")));
void NMI_Handler(void) __attribute__((weak, alias("_unhandled_exception")));
void HardFault_Handler(void) __attribute__((weak, alias("_unhandled_exception")));
void MemManage_Handler(void) __attribute__((weak, alias("_unhandled_exception")));
void BusFault_Handler(void) __attribute__((weak, alias("_unhandled_exception")));
void UsageFault_Handler(void) __attribute__((weak, alias("_unhandled_exception")));
void SVCall_Handler(void) __attribute__((weak, alias("_unhandled_exception")));
void DebugMon_Handler(void) __attribute__((weak, alias("_unhandled_exception")));
void PendSV_Handler(void) __attribute__((weak, alias("_unhandled_exception")));
void SysTick_Handler(void) __attribute__((weak, alias("_unhandled_exception")));

extern uint32_t __stack;
__attribute__((used, section(".isr_vector")))
static const void* vector_table[] = {
    (void *)&__stack,
    (void *)Reset_Handler,      /* Reset Handler */
    (void *)NMI_Handler,        /* NMI Handler */
    (void *)HardFault_Handler,  /* Hard Fault Handler */
    (void *)MemManage_Handler,  /* MPU Fault Handler */
    (void *)BusFault_Handler,   /* Bus Fault Handler */
    (void *)UsageFault_Handler, /* Usage Fault Handler */
    (void *)nullptr,            /* Reserved */
    (void *)nullptr,            /* Reserved */
    (void *)nullptr,            /* Reserved */
    (void *)nullptr,            /* Reserved */
    (void *)SVCall_Handler,     /* SVCall Handler */
    (void *)DebugMon_Handler,   /* Debug Monitor Handler */
    (void *)nullptr,            /* Reserved */
    (void *)PendSV_Handler,     /* PendSV Handler */
    (void *)SysTick_Handler     /* SysTick Handler */
  };


}
