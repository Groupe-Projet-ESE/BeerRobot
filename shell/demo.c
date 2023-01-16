/*
 * demo.c
 *
 *  Created on: 11 janv. 2023
 *      Author: Loicia
 */

#include "cmsis_os.h"
#include <stdio.h>
#include "usart.h"
#include "gpio.h"
#include "demo.h"
#include "main.h"
#include "motor.h"

TaskHandle_t h_task_demo = NULL;
extern TaskHandle_t h_motor;
extern h_motor_t h_cmd_motor;

int demo_run(h_demo_t *pdemo){

	vTaskDelay(5);
	uint16_t s = 300;
	h_cmd_motor.cmd='d';
	h_cmd_motor.speed=s;
	vTaskResume(h_motor);
	vTaskDelay(5);
	h_cmd_motor.cmd='s';
	h_cmd_motor.speed=s;

	while(1){

	}
}

