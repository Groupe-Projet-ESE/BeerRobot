/*
 * servomotor.c
 *
 *  Created on: Jan 10, 2023
 *      Author: Loicia
 */

#include <stdint.h>
#include "shell.h"
#include "servomotor.h"
#include "XL320.h"
#include "main.h"
#include "tim.h"
#include "cmsis_os.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "motor.h"

TaskHandle_t h_servomotor = NULL;
extern TaskHandle_t h_motor;
h_servomotor_t h_cmd_servomotor;
extern h_motor_t h_cmd_motor;
extern TaskHandle_t h_tof;


extern TaskHandle_t h_recherche;



int servo_shell(h_shell_t * pshell, int argc, char ** argv){
	if(argc == 3){
		if(*argv[1]=='o'){
			uint16_t s=atoi(argv[2]);
			printf("La pince s'ouvre\r\n");
			h_cmd_servomotor.cmd='o';
			h_cmd_servomotor.speed=s;
			vTaskResume(h_servomotor);
		}
		if(*argv[1]=='c'){
			uint16_t s=atoi(argv[2]);
			printf("La pince se ferme\r\n");
			h_cmd_servomotor.cmd='c';
			h_cmd_servomotor.speed=s;
			printf("La vitesse est de %d sur 1023\r\n",h_cmd_servomotor.speed);
			vTaskResume(h_servomotor);
		}
	}

	else{
		printf("Erreur, pas le bon nombre d'arguments\r\n");
		return -1;
	}

	return 0;
}

void taskServoMotor(void *pServoMotor){
	printf("Tâche servomoteur créée\r\n");
	//speed(200);
	for(;;){
		ulTaskNotifyTake(pdTRUE,portMAX_DELAY);
		speed(200);
		if(((h_servomotor_t *)pServoMotor)->cmd=='o'){
			//speed(((h_servomotor_t *)pServoMotor)->speed);
			//vTaskDelay(10);
			open();
		}
		if(((h_servomotor_t *)pServoMotor)->cmd=='c'){
			//speed(((h_servomotor_t *)pServoMotor)->speed);
			//vTaskDelay(10);
			//vTaskSuspend(h_recherche);
			//vTaskSuspend(h_tof);
			close();
		}
	}
}
