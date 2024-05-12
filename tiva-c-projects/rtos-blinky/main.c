#include <stdint.h>
#include <FreeRTOS.h>
#include <task.h>
#include "TM4C129.h"                    // Device header



void Led1Task(void *pvParameters)
{
	// Establish the task's period.
	const TickType_t xDelay = pdMS_TO_TICKS(100);
	TickType_t xLastWakeTime = xTaskGetTickCount();

	while(1)
	{
		GPION->DATA |= 0x02;

		vTaskDelayUntil(&xLastWakeTime, xDelay);

		GPION->DATA &= ~(0x02);
		
		vTaskDelayUntil(&xLastWakeTime, xDelay);
	}
}

void Led2Task(void *pvParameters)
{
	// Establish the task's period.
	const TickType_t xDelay = pdMS_TO_TICKS(200);
	TickType_t xLastWakeTime = xTaskGetTickCount();

	while(1)
	{
		GPION->DATA |= 0x01;

		vTaskDelayUntil(&xLastWakeTime, xDelay);

		GPION->DATA &= ~(0x01);

		vTaskDelayUntil(&xLastWakeTime, xDelay);
	}
}

void Led3Task(void *pvParameters)
{
	// Establish the task's period.
	const TickType_t xDelay = pdMS_TO_TICKS(400);
	TickType_t xLastWakeTime = xTaskGetTickCount();
	
	while(1)
	{
		GPIOF_AHB->DATA |= (1 << 4);

		vTaskDelayUntil(&xLastWakeTime, xDelay);

		GPIOF_AHB->DATA &= ~((1 << 4));

		vTaskDelayUntil(&xLastWakeTime, xDelay);
	}
}

void Led4Task(void *pvParameters)
{
	// Establish the task's period.
	const TickType_t xDelay = pdMS_TO_TICKS(800);
	TickType_t xLastWakeTime = xTaskGetTickCount();

	while(1)
	{
		GPIOF_AHB->DATA |= (1 << 0);

		vTaskDelayUntil(&xLastWakeTime, xDelay);

		GPIOF_AHB->DATA &= ~((1 << 0));

		vTaskDelayUntil(&xLastWakeTime, xDelay);
	}
}



int main()
{
	   //
	// Enable the GPIO port that is used for the on-board LED.
	//
	SYSCTL->RCGCGPIO = (1<<12) | (1<<5);

	//
	// Enable the GPIO pin for the LED (PN0).  Set the direction as output, and
	// enable the GPIO pin for digital function.
	//
	GPION->DIR = 0x03;
	GPION->DEN = 0x03;

	//
	// Enable the GPIO pin for the LED (PN0).  Set the direction as output, and
	// enable the GPIO pin for digital function.
	//
	GPIOF_AHB->DIR = (1 << 4) | (1 << 0);
	GPIOF_AHB->DEN = (1 << 4) | (1 << 0);

	BaseType_t return_task;

	return_task = xTaskCreate(Led1Task, "LED 1", 256, NULL, 1, NULL);
	if(return_task == pdPASS)
	{
		GPION->DATA |= 0x01;
	}
	
	return_task = xTaskCreate(Led2Task, "LED 2", 256, NULL, 1, NULL);
	if(return_task == pdPASS)
	{
		GPION->DATA |= 0x02;
	}
	
	
	return_task = xTaskCreate(Led3Task, "LED 3", 256, NULL, 1, NULL);
	if(return_task == pdPASS)
	{
		GPION->DATA |= (1 << 0);
	}
	
	return_task = xTaskCreate(Led4Task, "LED 4", 256, NULL, 1, NULL);
	if(return_task == pdPASS)
	{
		GPION->DATA |= (1 << 4);
	}
	

	//GPION->DATA &= ~0x03;
	//GPIOF_AHB->DATA &= ~((1 << 4)| (1 << 0));
	// Startup of the FreeRTOS scheduler.  The program should block here.  
	vTaskStartScheduler();
	GPION->DATA |= 0x03;
	GPIOF_AHB->DATA |= (1 << 4)| (1 << 0);
	// The following line should never be reached.  Failure to allocate enough
	//	memory from the heap would be one reason.
	for (;;);
	
}
