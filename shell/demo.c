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
#include "servomotor.h"

TaskHandle_t h_task_demo = NULL;
extern TaskHandle_t h_motor;
extern h_motor_t h_cmd_motor;
extern TaskHandle_t h_servomotor;
extern h_motor_t h_cmd_servomotor;
extern TaskHandle_t h_tof;
extern TaskHandle_t h_recherche;

int demo_run(h_demo_t *pdemo){



	vTaskDelay(1000);
	h_cmd_motor.cmd='a';
	h_cmd_motor.speed=250;
	xTaskNotifyGive(h_motor);
	h_cmd_servomotor.cmd='o';
	h_cmd_servomotor.speed=200;
	xTaskNotifyGive(h_servomotor);
	vTaskDelay(2000);

#if 0
	uint16_t s = 300;
	h_cmd_motor.cmd='d';
	h_cmd_motor.speed=s;
	xTaskNotifyGive(h_motor);
	//vTaskDelay(20);
	h_cmd_motor.cmd='a';
	h_cmd_motor.speed=s;
	xTaskNotifyGive(h_motor);
	//vTaskDelay(20);
#endif

	while(1){
		xTaskNotifyGive(h_tof);
		//xTaskNotifyGive(h_recherche);
		vTaskDelay(200);
	}
}


