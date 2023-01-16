/*
 * encoder.c
 *
 *  Created on: Dec 7, 2022
 *      Author: Loicia
 */

#include "encoder.h"
#include "main.h"
#include "tim.h"
#include "cmsis_os.h"
#include "stdio.h"

TaskHandle_t h_encoder = NULL;
TaskHandle_t h_encoder_print = NULL;

h_encoder_t encoder_left; //TIM1
h_encoder_t encoder_right; //TIM3

int encoder_shell(h_shell_t * pshell, int argc, char ** argv){
	if (argc == 1){
		if(*argv[0]=='e'){
			printf("L'encodeur est activé\r\n");
			vTaskResume(h_encoder);
		}
	}
	else{
		printf("Erreur, pas le bon nombre d'arguments\r\n");
		return -1;
	}
	return 0;
}

void taskEncoder(void *pEncoder){
	printf("Tâche encodeur créée\r\n");
	vTaskSuspend(0);

	encoder_left.Ts= 5;
	encoder_right.Ts = 5;

	encoder_left.position=0;
	encoder_right.position=0;


	HAL_TIM_Encoder_Start(&htim1, TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);
	int index = 0;
	for(;;){
		encoder_left.speed=0;
		encoder_right.speed=0;
		encoder_left.countTIM = __HAL_TIM_GET_COUNTER(&htim1);
		encoder_right.countTIM =__HAL_TIM_GET_COUNTER(&htim3);
		__HAL_TIM_SET_COUNTER(&htim1, 0);
		__HAL_TIM_SET_COUNTER(&htim3, 0);
		if (encoder_left.countTIM<((TIM1->ARR)/2)){//recule
			encoder_left.tab_pos[index]=-1*encoder_left.countTIM;
			encoder_right.tab_pos[index]=encoder_right.countTIM-(TIM1->ARR);

			encoder_left.position+=-1*(encoder_left.countTIM/REVOLUTION)*2*PI*R/1000;
			encoder_right.position+=(encoder_right.countTIM-(TIM1->ARR))/REVOLUTION*2*PI*R/1000;
		}
		else{//avance
			encoder_left.tab_pos[index]=(TIM1->ARR)-encoder_left.countTIM;
			encoder_right.tab_pos[index]=encoder_right.countTIM;

			encoder_left.position+=((TIM1->ARR)-encoder_left.countTIM)/REVOLUTION*2*PI*R/1000;
			encoder_right.position+=(encoder_right.countTIM/REVOLUTION)*2*PI*R/1000;

		}
		index++;
		if(index==TAB_SIZE){
			xTaskNotifyGive(h_encoder_print);
			vTaskSuspend(0);
			index=0;
		}
		vTaskDelay(encoder_left.Ts);
	}
}

void taskEncoderPrint(void *pPrint){
	printf("Tâche encodeur print créée\r\n");
	for(;;){
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
		for(int i=0;i<TAB_SIZE;i++){
			printf("l:%d  r:%d\r\n",encoder_left.tab_pos[i],encoder_right.tab_pos[i]);
		}
		printf("pos l:%d  pos r:%d\r\n",encoder_left.position,encoder_right.position);
		printf("%f  %d",encoder_left.speed,encoder_left.tab_pos[TAB_SIZE-1]);
		encoder_left.speed=((encoder_left.tab_pos[TAB_SIZE-1]*1000/REVOLUTION)*2*PI*R)/(encoder_left.Ts*1000); //speed en m/S
		encoder_right.speed=((encoder_right.tab_pos[TAB_SIZE-1]*1000/REVOLUTION)*2*PI*R)/(encoder_right.Ts*1000);
		printf("speed l:%f  speed r:%f\r\n",encoder_left.speed,encoder_right.speed);
		//vTaskResume(h_encoder);
	}
}
