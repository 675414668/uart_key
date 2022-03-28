#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#include <stdint.h>
extern uint32_t SystemCoreClock;

#define configUSE_PREEMPTION		          1 //1ʹ����ռʽ�ںˣ�0ʹ��Э��
#define configUSE_IDLE_HOOK			          0 //1��ʹ�ÿ��й��ӣ�0����ʹ��
#define configUSE_TICK_HOOK			          0 //1��ʹ��ʱ��Ƭ���ӣ�0����ʹ��
#define configCPU_CLOCK_HZ			         ( ( unsigned long ) SystemCoreClock ) //CPUƵ��
#define configTICK_RATE_HZ			         ( ( TickType_t ) 1000 ) //ʱ�ӽ���Ƶ�ʣ���������Ϊ1000�����ھ���1ms
#define configMAX_PRIORITIES		         ( 5 ) //��ʹ�õ�������ȼ�
#define configMINIMAL_STACK_SIZE	       ( ( unsigned short ) 130 ) //��������ʹ�õĶ�ջ��С
#define configTOTAL_HEAP_SIZE		         ( ( size_t ) ( 6 * 1024 ) ) //ϵͳ�����ܵĶѴ�С
#define configMAX_TASK_NAME_LEN		       ( 10 ) //���������ַ�������
#define configUSE_TRACE_FACILITY	        0 //Ϊ1���ÿ��ӻ����ٵ���
#define configUSE_16_BIT_TICKS		        0 //ϵͳ���ļ�����������������
#define configIDLE_SHOULD_YIELD		        1 //Ϊ1ʱ�����������CPUʹ��Ȩ������ͬ���ȼ����û�����
#define configUSE_MUTEXES                 1
#define configQUEUE_REGISTRY_SIZE         5 //����ע����ź�������Ϣ������
#define configCHECK_FOR_STACK_OVERFLOW    0 //��ջ������,����ֵ1,2
#define configUSE_RECURSIVE_MUTEXES       1 //���ó�1��ʾʹ�õݹ黥����,���ó�0��ʾ��ʹ��
#define configUSE_MALLOC_FAILED_HOOK      0 //1ʹ���ڴ�����ʧ�ܹ��Ӻ���
#define configUSE_APPLICATION_TASK_TAG    0 //Ϊ��������ǩֵ������Ϊ1��ʹ��vTaskSetApplicationTaskTag����������ı�ǩֻ��Ӧ�ó������ã��ں˲�ʹ��
#define configUSE_COUNTING_SEMAPHORES     1 //Ϊ1ʱʹ�ü����ź���
#define configGENERATE_RUN_TIME_STATS     0 //Ϊ1,��ú�����������ʱ��д��*pulTotalRunTime��
#define configUSE_CO_ROUTINES 		        0 //Ϊ1ʱ����Э�̣�����Э���Ժ��������ļ�croutine.c
#define configMAX_CO_ROUTINE_PRIORITIES   ( 2 ) //Э�̵���Ч���ȼ���Ŀ

#define configKERNEL_INTERRUPT_PRIORITY 		    255 //��������RTOS�ں��Լ����ж����ȼ�
#define configMAX_SYSCALL_INTERRUPT_PRIORITY 	  191 //����ϵͳ�ں����ȼ�
#define configLIBRARY_KERNEL_INTERRUPT_PRIORITY	15  //����ϵͳ�ں����ȼ�,����ʹ�õ���4bit���ȼ�,�������Ϊ15,��1 �е�������ͬ
 //FreeRTOS��ѡ��������ѡ�� 
#define INCLUDE_xTaskGetSchedulerState          1                       
#define INCLUDE_vTaskPrioritySet                1
#define INCLUDE_uxTaskPriorityGet               1
#define INCLUDE_vTaskDelete                     1
#define INCLUDE_vTaskCleanUpResources           1
#define INCLUDE_vTaskSuspend                    1
#define INCLUDE_vTaskDelayUntil                 1
#define INCLUDE_vTaskDelay                      1
#define INCLUDE_eTaskGetState                   1
#define INCLUDE_uxTaskGetStackHighWaterMark     1

#define xPortPendSVHandler  PendSV_Handler
#define vPortSVCHandler     SVC_Handler
#define xPortSysTickHandler SysTick_Handler

#endif /* FREERTOS_CONFIG_H */

