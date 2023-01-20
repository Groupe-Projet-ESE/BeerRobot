/*
 * motor.c
 *
 *  Created on: Dec 7, 2022
 *      Author: Loicia
 */
#include "motor.h"
#include "main.h"
#include "tim.h"
#include "cmsis_os.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <stdio.h>
#include "encoder.h"
#include <stdlib.h>
#include <math.h>



TaskHandle_t h_motor = NULL;
h_motor_t h_cmd_motor;

TaskHandle_t h_bordure = NULL;
TaskHandle_t h_recherche = NULL;
TaskHandle_t h_attrape = NULL;
TaskHandle_t h_trouve = NULL;

extern TaskHandle_t h_tof;
extern TaskHandle_t h_servomotor;
extern h_motor_t h_cmd_servomotor;
extern h_asser_t asservissement_gauche;
extern h_asser_t asservissement_droit;

int moteurDroit(h_shell_t * pshell, int argc, char ** argv){
	if (argc == 2){
		if (atoi(argv[1])==1){
			HAL_TIMEx_PWMN_Stop(&htim16, TIM_CHANNEL_1);
			HAL_TIM_PWM_Start(&htim16, TIM_CHANNEL_1);
			//TIM16->CCR1=700;
			printf("Le moteur droit avance\r\n");
		}
		if(atoi(argv[1])==-1){
			HAL_TIM_PWM_Stop(&htim16, TIM_CHANNEL_1);
			HAL_TIMEx_PWMN_Start(&htim16, TIM_CHANNEL_1);
			//TIM16->CCR1=700;
			printf("Le moteur droit recule\r\n");
		}
		if(atoi(argv[1])==0){
			HAL_TIM_PWM_Stop(&htim16, TIM_CHANNEL_1);
			HAL_TIMEx_PWMN_Stop(&htim16, TIM_CHANNEL_1);
			//TIM16->CCR1=700;
			printf("Le moteur droit s'arrête\r\n");
		}
	}
	else{
		printf("Erreur, pas le bon nombre d'arguments\r\n");
		return -1;
	}
	return 0;
}

int moteurGauche(h_shell_t * pshell, int argc, char ** argv){
	if (argc == 2){
		if(atoi(argv[1])==1){
			HAL_TIM_PWM_Stop(&htim17, TIM_CHANNEL_1);
			HAL_TIMEx_PWMN_Start(&htim17, TIM_CHANNEL_1);
			//TIM16->CCR1=700;
			printf("Le moteur gauche avance\r\n");
		}
		if (atoi(argv[1])==-1){
			HAL_TIMEx_PWMN_Stop(&htim17, TIM_CHANNEL_1);
			HAL_TIM_PWM_Start(&htim17, TIM_CHANNEL_1);
			//TIM16->CCR1=700;
			printf("Le moteur gauche recule\r\n");
		}

		if(atoi(argv[1])==0){
			HAL_TIM_PWM_Stop(&htim17, TIM_CHANNEL_1);
			HAL_TIMEx_PWMN_Stop(&htim17, TIM_CHANNEL_1);
			//TIM16->CCR1=700;
			printf("Le moteur gauche s'arrête\r\n");
		}
	}
	else{
		printf("Erreur, pas le bon nombre d'arguments\r\n");
		return -1;
	}
	return 0;
}

int motor_shell(h_shell_t * pshell, int argc, char ** argv){
	if (argc == 3){
		if(*argv[1]=='a'){
			uint16_t s=atoi(argv[2]);
			printf("Le robot avance\r\n");
			h_cmd_motor.cmd='a';
			h_cmd_motor.speed=s;
			//vTaskResume(h_motor);
			printf("La commande moteur est mise à jour\r\n");
			xTaskNotifyGive(h_motor);
		}
		if(*argv[1]=='r'){
			uint16_t s=atoi(argv[2]);
			printf("Le robot recule\r\n");
			h_cmd_motor.cmd='r';
			h_cmd_motor.speed=s;
			vTaskResume(h_motor);
		}
		if(*argv[1]=='s'){
			uint16_t s=atoi(argv[2]);
			printf("Le robot s'arrête\r\n");
			h_cmd_motor.cmd='s';
			h_cmd_motor.speed=s;
			vTaskResume(h_motor);
		}
		if(*argv[1]=='g'){
			uint16_t s=atoi(argv[2]);
			printf("Le robot tourne à gauche\r\n");
			h_cmd_motor.cmd='g';
			h_cmd_motor.speed=s;
			vTaskResume(h_motor);
		}
		if(*argv[1]=='d'){
			uint16_t s=atoi(argv[2]);
			printf("Le robot tourne à droite\r\n");
			h_cmd_motor.cmd='d';
			h_cmd_motor.speed=s;
			vTaskResume(h_motor);
		}
		/*
			if(argv[1]=="r"){
				printf("Le robot recule\r\n");

				vTaskResume(h_motor);
			}
			if(argv[1]=="d"){
				printf("Le robot tourne à droite\r\n");

			}
			if(argv[1]=="g"){
				printf("Le robot tourne à gauche\r\n");

			}*/
	}
	else{
		printf("Erreur, pas le bon nombre d'arguments\r\n");
		return -1;
	}
	return 0;
}

/*

int motor_demo(h_demo_t * pdemo){
	if (argc == 3){
		if(*argv[1]=='a'){
			uint16_t s=atoi(argv[2]);
			printf("Le robot avance\r\n");
			h_cmd_motor.cmd='a';
			h_cmd_motor.speed=s;
			vTaskResume(h_motor);
		}
		if(*argv[1]=='r'){
			uint16_t s=atoi(argv[2]);
			printf("Le robot recule\r\n");
			h_cmd_motor.cmd='r';
			h_cmd_motor.speed=s;
			vTaskResume(h_motor);
		}
		if(*argv[1]=='s'){
			uint16_t s=atoi(argv[2]);
			printf("Le robot s'arrête\r\n");
			h_cmd_motor.cmd='s';
			h_cmd_motor.speed=s;
			vTaskResume(h_motor);
		}
		if(*argv[1]=='g'){
			uint16_t s=atoi(argv[2]);
			printf("Le robot tourne à gauche\r\n");
			h_cmd_motor.cmd='g';
			h_cmd_motor.speed=s;
			vTaskResume(h_motor);
		}
		if(*argv[1]=='d'){
			uint16_t s=atoi(argv[2]);
			printf("Le robot tourne à droite\r\n");
			h_cmd_motor.cmd='d';
			h_cmd_motor.speed=s;
			vTaskResume(h_motor);
		}

	}
	else{
		printf("Erreur, pas le bon nombre d'arguments\r\n");
		return -1;
	}
	return 0;
}
 */

int avance(int vitesse){

	HAL_TIMEx_PWMN_Stop(&htim16, TIM_CHANNEL_1);
	HAL_TIM_PWM_Stop(&htim17, TIM_CHANNEL_1);

	__HAL_TIM_SET_COMPARE(&htim16,TIM_CHANNEL_1,vitesse);
	__HAL_TIM_SET_COMPARE(&htim17,TIM_CHANNEL_1,vitesse);

	HAL_TIM_PWM_Start(&htim16, TIM_CHANNEL_1);
	HAL_TIMEx_PWMN_Start(&htim17, TIM_CHANNEL_1);
	//vTaskSuspend(h_motor);
	//ulTaskNotifyTake(pdTRUE,portMAX_DELAY);
	return 0;
}

int recule(int vitesse){

	HAL_TIM_PWM_Stop(&htim16, TIM_CHANNEL_1);
	HAL_TIMEx_PWMN_Stop(&htim17, TIM_CHANNEL_1);

	__HAL_TIM_SET_COMPARE(&htim16,TIM_CHANNEL_1,vitesse);
	__HAL_TIM_SET_COMPARE(&htim17,TIM_CHANNEL_1,vitesse);

	HAL_TIMEx_PWMN_Start(&htim16, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim17, TIM_CHANNEL_1);
	//vTaskSuspend(h_motor);
	//ulTaskNotifyTake(pdTRUE,portMAX_DELAY);
	return 0;
}

int stop(void){

	HAL_TIM_PWM_Stop(&htim16, TIM_CHANNEL_1);
	HAL_TIMEx_PWMN_Stop(&htim17, TIM_CHANNEL_1);

	HAL_TIMEx_PWMN_Stop(&htim16, TIM_CHANNEL_1);
	HAL_TIM_PWM_Stop(&htim17, TIM_CHANNEL_1);
	//vTaskSuspend(h_motor);
	//ulTaskNotifyTake(pdTRUE,portMAX_DELAY);
	return 0;
}

int gauche(int vitesse){
	//Le moteur droit avance
	HAL_TIMEx_PWMN_Stop(&htim16, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim16, TIM_CHANNEL_1);

	__HAL_TIM_SET_COMPARE(&htim16,TIM_CHANNEL_1,vitesse);
	__HAL_TIM_SET_COMPARE(&htim17,TIM_CHANNEL_1,vitesse);

	//Le moteur gauche recule (voir si on doit plutôt l'arrêter)
	HAL_TIMEx_PWMN_Stop(&htim17, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim17, TIM_CHANNEL_1);
	//vTaskSuspend(h_motor);
	//ulTaskNotifyTake(pdTRUE,portMAX_DELAY);
	return 0;
}

int droite(int vitesse){

	//Le moteur droit recule (voir si on doit plutôt l'arrêter)
	HAL_TIM_PWM_Stop(&htim16, TIM_CHANNEL_1);
	HAL_TIMEx_PWMN_Start(&htim16, TIM_CHANNEL_1);

	__HAL_TIM_SET_COMPARE(&htim16,TIM_CHANNEL_1,vitesse);
	__HAL_TIM_SET_COMPARE(&htim17,TIM_CHANNEL_1,vitesse);

	//Le moteur gauche avance
	HAL_TIM_PWM_Stop(&htim17, TIM_CHANNEL_1);
	HAL_TIMEx_PWMN_Start(&htim17, TIM_CHANNEL_1);

	//Appel taskMotor
	//vTaskSuspend(h_motor);
	//ulTaskNotifyTake(pdTRUE,portMAX_DELAY);
	return 0;
}


int avance_droit(int vitesse){
	HAL_TIMEx_PWMN_Stop(&htim16, TIM_CHANNEL_1);
	//HAL_TIM_PWM_Stop(&htim17, TIM_CHANNEL_1);

	uint32_t tim_per_droit=__HAL_TIM_GET_AUTORELOAD(&htim16);
	__HAL_TIM_SET_COMPARE(&htim16,TIM_CHANNEL_1,(uint32_t)((vitesse/100.0)*tim_per_droit));

	HAL_TIM_PWM_Start(&htim16, TIM_CHANNEL_1);
	//HAL_TIMEx_PWMN_Start(&htim17, TIM_CHANNEL_1);
	//vTaskSuspend(h_motor);
	return 0;
}

int avance_gauche(int vitesse){
	//HAL_TIMEx_PWMN_Stop(&htim16, TIM_CHANNEL_1);
	HAL_TIM_PWM_Stop(&htim17, TIM_CHANNEL_1);
	uint32_t tim_per_gauche=__HAL_TIM_GET_AUTORELOAD(&htim17);

	__HAL_TIM_SET_COMPARE(&htim17,TIM_CHANNEL_1,(uint32_t)((vitesse/100.0)*tim_per_gauche));

	HAL_TIMEx_PWMN_Start(&htim17, TIM_CHANNEL_1);

	//vTaskSuspend(h_motor);
	return 0;
}

void taskBordure(void *pMotor){
	printf("Tâche bordure créée\r\n");
	for(;;){
		ulTaskNotifyTake(pdTRUE,portMAX_DELAY);
		//vTaskSuspend(h_tof);
		vTaskSuspend(h_recherche);
		vTaskSuspend(h_trouve);
		//vTaskSuspend(h_attrape);
		printf("Je suis sur une bordure");
		//((h_motor_t *)pMotor)->cmd = 'r';
		//((h_motor_t *)pMotor)->speed = 300;
		//xTaskNotifyGive(h_motor);
		vTaskDelay(3);
		h_cmd_motor.cmd='r';
		xTaskNotifyGive(h_motor);
		vTaskDelay(400);
		h_cmd_motor.cmd='d';
		xTaskNotifyGive(h_motor);
		vTaskDelay(300);
		h_cmd_motor.cmd='a';
		xTaskNotifyGive(h_motor);
		vTaskDelay(200);
		//vTaskResume(h_tof);
		vTaskResume(h_recherche);
		vTaskResume(h_trouve);
		//vTaskResume(h_attrape);
	}

}


//La tache recherche fonctionne mal
void taskRecherche(void *pMotor){
	printf("Tâche recherche créée\r\n");
	for(;;){
		ulTaskNotifyTake(pdTRUE,portMAX_DELAY);
		vTaskSuspend(h_trouve);
		vTaskDelay(3);
		int angle_droit = round(rand()/6000000);
		int angle_gauche = round(rand()/6000000);
		h_cmd_motor.cmd='a';
		xTaskNotifyGive(h_motor);
		vTaskDelay(400);
		h_cmd_motor.cmd='d';
		xTaskNotifyGive(h_motor);
		vTaskDelay(angle_droit);
		h_cmd_motor.cmd='a';
		xTaskNotifyGive(h_motor);
		vTaskDelay(200);
		h_cmd_motor.cmd='g';
		xTaskNotifyGive(h_motor);
		vTaskDelay(angle_gauche);
		h_cmd_motor.cmd='s';
		xTaskNotifyGive(h_motor);
		vTaskDelay(200);
		vTaskResume(h_trouve);
	}
}


void taskTrouve(void *pMotor){
	printf("Tâche trouve créée\r\n");
	for(;;){
		ulTaskNotifyTake(pdTRUE,portMAX_DELAY);
		vTaskSuspend(h_recherche);
		h_cmd_servomotor.cmd='o';
		xTaskNotifyGive(h_servomotor);
		vTaskDelay(200);
		h_cmd_motor.cmd='s';
		xTaskNotifyGive(h_motor);
		vTaskDelay(200);
		h_cmd_motor.cmd='a';
		//h_cmd_motor.speed=300;
		xTaskNotifyGive(h_motor);
		vTaskDelay(200);
		vTaskResume(h_recherche);
	}
}

void taskAttrape(void *pMotor){
	printf("Tâche attrape créée\r\n");
	for(;;){
		ulTaskNotifyTake(pdTRUE,portMAX_DELAY);
		vTaskSuspend(h_recherche);
		h_cmd_servomotor.cmd='c';
		h_cmd_servomotor.speed=200;
		xTaskNotifyGive(h_servomotor);
		vTaskDelay(200);
		h_cmd_motor.cmd='s';
		xTaskNotifyGive(h_motor);
		vTaskDelay(200);
		//vTaskResume(h_recherche);
	}
}





void taskMotor(void *pMotor){
	printf("Tâche moteur créée\r\n");
	//ulTaskNotifyTake(pdTRUE,portMAX_DELAY);
	printf("Notif taken");
	//vTaskSuspend(0);
	for(;;){
		ulTaskNotifyTake(pdTRUE,portMAX_DELAY);
		if(((h_motor_t *)pMotor)->cmd=='a'){
			avance(((h_motor_t *)pMotor)->speed);
			//update_droite(((h_motor_t *)pMotor)->speed);
			//update_gauche(((h_motor_t *)pMotor)->speed);
		}
		if(((h_motor_t *)pMotor)->cmd=='r'){
			recule(((h_motor_t *)pMotor)->speed);
		}
		if(((h_motor_t *)pMotor)->cmd=='s'){
			stop();
		}
		if(((h_motor_t *)pMotor)->cmd=='g'){
			gauche(((h_motor_t *)pMotor)->speed);
		}
		if(((h_motor_t *)pMotor)->cmd=='d'){
			droite(((h_motor_t *)pMotor)->speed);
		}


	}
	/*
		uint16_t pwm16 = 0;
		uint16_t inc16 = 1;
		uint16_t pwm17 = 0;
		uint16_t inc17 = 1;
		if (pwm16 == 1023)
		{
			inc16 = -1;
		}
		if (pwm17 == 1023)
		{
			inc17 = -1;
		}
		if (pwm16 == 0)
		{
			inc16 = 1;
		}
		if (pwm17 == 0)
		{
			inc17 = 1;
		}
		pwm16 += inc16;
		pwm17 += inc17;
		__HAL_TIM_SET_COMPARE(&htim16,TIM_CHANNEL_1,pwm16);
		__HAL_TIM_SET_COMPARE(&htim17,TIM_CHANNEL_1,pwm17);
		vTaskDelay(1);
	}*/
}
