/*
 * TOF.c
 *
 *  Created on: 6 janv. 2023
 *      Author: Loicia
 */


#include "TOF.h"

#include "vl53l0x_api.h"
#include "main.h"
#include "math.h"
#include "i2c.h"
#include "usart.h"
#include "gpio.h"
#include <stdio.h>
#include "tim.h"
#include "cmsis_os.h"
#include "stdio.h"
#include "motor.h"
#include "servomotor.h"

extern TaskHandle_t h_motor;
extern TaskHandle_t h_notif;
extern TaskHandle_t h_servomotor;
extern TaskHandle_t h_recherche;

extern TaskHandle_t h_trouve;
extern TaskHandle_t h_attrape;

extern h_motor_t h_cmd_motor;
extern h_servomotor_t h_cmd_servomotor;


uint32_t refSpadCount;
uint8_t isApertureSpads;
uint8_t VhvSettings;
uint8_t PhaseCal;


uint8_t Message[64];
uint8_t Message_resultat[64];
uint8_t resultat2[64];
uint8_t resultat_ranging[64];



uint8_t Message_resultat_Size;
uint8_t Message_Size;
uint8_t DMaxMillimeter_size;

uint8_t resultat_ranging_size;

uint8_t intro[]="intro capteur de distance\n\r";


VL53L0X_RangingMeasurementData_t RangingData;
VL53L0X_Dev_t  vl53l0x_c; // vl53l0x_c est un pointeur de structure que l'on utilisera tout au long du code
//Structure privée L53L0X_DevData_t permettant d'avoir accès à des données
//
VL53L0X_DEV Dev = &vl53l0x_c;//Dev prend comme valeur l'adresse du pointeur (raccourcir tout au long du code)

TaskHandle_t h_tof;


int last_distance;

void clignotage_led_stm32(){
	HAL_GPIO_WritePin(GPIOC, LED_GREEN_Pin, GPIO_PIN_RESET); // Disable XSHUT
	HAL_Delay(200);
	HAL_GPIO_WritePin(GPIOC, LED_GREEN_Pin, GPIO_PIN_SET); // Enable XSHUT
	HAL_Delay(200);
}

/*
void test_UART(){
	HAL_UART_Transmit(&huart1, "TEST2 ",6,100);
	HAL_Delay(500);
}
 */


void TOF_Enable(int nb,GPIO_PinState state)
{
	uint16_t GPIO1_Pin;
	uint16_t XSHUT_Pin;
	if(nb = 1){
		GPIO1_Pin = GPIO1_C1_Pin;
		XSHUT_Pin = XSHUT_C1_Pin;
	}
	else{
		GPIO1_Pin = GPIO1_C2_Pin;
		XSHUT_Pin = XSHUT_C2_Pin;
	}
	HAL_GPIO_WritePin(GPIOB, GPIO1_Pin, state);
	HAL_GPIO_WritePin(GPIOB, XSHUT_Pin, state);
}

void initialisation_mesure_capteur(){

	/* USER CODE BEGIN 2 */
	//HAL_UART_Transmit(&huart1, "TEST2 ",6,100);
	//HAL_Delay(500);

	Message_Size = sizeof(intro);
	HAL_UART_Transmit(&huart1, intro, Message_Size, 100);

	Dev->I2cHandle = &hi2c2;
	Dev->I2cDevAddr = 0x52; //adresse de l'I2C dans la datasheet du VL530X

	//HAL_GPIO_WritePin(GPIOB, XSHUT_C1_Pin, GPIO_PIN_RESET); // Disable XSHUT
	//vTaskDelay(20);
	//On active Le port KSHUT qui est le port permettant de recevoir les valeurs
	//HAL_GPIO_WritePin(GPIOB, XSHUT_C1_Pin, GPIO_PIN_SET); // Enable XSHUT
	//vTaskDelay(20);

	//TOF_Enable(1, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO1_C2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, XSHUT_C2_Pin, GPIO_PIN_SET);


	//Simple mesure pour Capteur
	VL53L0X_WaitDeviceBooted(Dev);
	VL53L0X_DataInit(Dev);
	VL53L0X_StaticInit(Dev);
	VL53L0X_PerformRefCalibration(Dev, &VhvSettings, &PhaseCal);
	VL53L0X_PerformRefSpadManagement(Dev, &refSpadCount, &isApertureSpads);
	VL53L0X_SetDeviceMode(Dev, VL53L0X_DEVICEMODE_SINGLE_RANGING);

	// Enable/Disable Sigma and Signal check
	VL53L0X_SetLimitCheckEnable(Dev, VL53L0X_CHECKENABLE_SIGMA_FINAL_RANGE, 1);
	VL53L0X_SetLimitCheckEnable(Dev, VL53L0X_CHECKENABLE_SIGNAL_RATE_FINAL_RANGE, 1);
	VL53L0X_SetLimitCheckValue(Dev, VL53L0X_CHECKENABLE_SIGNAL_RATE_FINAL_RANGE, (FixPoint1616_t)(0.1*65536));
	VL53L0X_SetLimitCheckValue(Dev, VL53L0X_CHECKENABLE_SIGMA_FINAL_RANGE, (FixPoint1616_t)(60*65536));
	//VL53L0X_SetMeasurementTimingBudgetMicroSeconds(Dev, 1910);
	VL53L0X_SetVcselPulsePeriod(Dev, VL53L0X_VCSEL_PERIOD_PRE_RANGE, 18);
	VL53L0X_SetVcselPulsePeriod(Dev, VL53L0X_VCSEL_PERIOD_FINAL_RANGE, 14);

	/* USER CODE END 2 */

}

void mesure_et_affichage(){
	VL53L0X_PerformSingleRangingMeasurement(Dev, &RangingData);

	/*if(RangingData.RangeStatus == 0){
		Message_resultat_Size = sprintf((char*)Message_resultat, "Distance en millimetre: %i\n\r", RangingData.RangeMilliMeter);
		DMaxMillimeter_size = sprintf((char*)resultat2, "RangeDMaxMillimeter: %i\n\r", RangingData.RangeDMaxMilliMeter );

		HAL_UART_Transmit(&huart1, Message_resultat, Message_resultat_Size, 100);
		HAL_UART_Transmit(&huart1, resultat2, DMaxMillimeter_size, 100);
	}*/
	if(RangingData.RangeStatus == 0){
		//Value = 0 means value is valid.
		int distance =RangingData.RangeMilliMeter;

		Message_resultat_Size = sprintf((char*)Message_resultat, "Distance en millimetre: %i\n\r", distance);
		HAL_UART_Transmit(&huart1, Message_resultat, Message_resultat_Size, 100);

		//on a rajoute 500 pour capter la canette de plus loin
		if(distance<500){
			HAL_GPIO_WritePin(GPIOC, LED_RED_Pin, GPIO_PIN_SET);
			if(distance<125){
				HAL_GPIO_WritePin(GPIOC, LED_GREEN_Pin, GPIO_PIN_SET);
				xTaskNotifyGive(h_attrape);
			}
			else{
				xTaskNotifyGive(h_trouve);
			}
			//HAL_GPIO_WritePin(GPIOC, LED_RED_Pin, GPIO_PIN_SET);
			//vTaskSuspend(h_recherche);
			/*
			h_cmd_motor.cmd='s';
			h_cmd_motor.speed=300;
			xTaskNotifyGive(h_motor);
			vTaskDelay(200);
			h_cmd_motor.cmd='a';
			h_cmd_motor.speed=300;
			xTaskNotifyGive(h_motor);
			vTaskDelay(200);*/

			//Ca doit marcher si on enlève la boucle autour
		}
#if 0
		if(distance<200){
			HAL_GPIO_WritePin(GPIOC, LED_GREEN_Pin, GPIO_PIN_SET); // Enable XSHUT
			//HAL_UART_Transmit(&huart1, Message_resultat, Message_resultat_Size, 100);
			//HAL_Delay(200);

			//Activer le TOF2 quand le TOF 1 a capté une distance à la canette inférieure à 6cm
			//TOF_Enable(1, GPIO_PIN_RESET);
			//TOF_Enable(2, GPIO_PIN_SET);
			h_cmd_motor.cmd='s';
			h_cmd_motor.speed=300;
			xTaskNotifyGive(h_motor);
			vTaskDelay(700);
			//mettre le code de recherche
			//h_cmd_motor.cmd='a';
			//h_cmd_motor.speed=300;
			//xTaskNotifyGive(h_motor);
			if(distance<125){
				//Code la tache pour attraper la canette				}
				h_cmd_servomotor.cmd='c';
				h_cmd_servomotor.speed=300;
				h_cmd_motor.cmd='s';
				xTaskNotifyGive(h_motor);
				xTaskNotifyGive(h_servomotor);
				vTaskDelay(200);
			}
			else{
				h_cmd_motor.cmd='a';
				h_cmd_motor.speed=300;
				xTaskNotifyGive(h_motor);
				vTaskDelay(200);
			}
		}
#endif
		//LED OFF > 200
		else{

			HAL_GPIO_WritePin(GPIOC, LED_GREEN_Pin, GPIO_PIN_RESET);
			HAL_UART_Transmit(&huart1, Message_resultat, Message_resultat_Size, 100);

			//On enlève cette partie pour faire fonctionner le robot avec les bordures assez rapides
			//xTaskNotifyGive(h_recherche);
			//vTaskDelay(200);
			xTaskNotifyGive(h_recherche);

		}


	}

	//HAL_UART_Transmit(&huart1, Message_resultat, Message_resultat_Size, 100);
}


int TOF_shell(h_shell_t * pshell, int argc, char ** argv){
	if (argc == 1){
		if(*argv[0]=='t'){
			printf("Le capteur TOF est activé\r\n");
			vTaskResume(h_tof);
		}
	}
	else{
		printf("Erreur, pas le bon nombre d'arguments\r\n");
		return -1;
	}
	return 0;
}

//task TOF
void taskTOF(void *pTOF){
	printf("Tâche TOF créée\r\n");

	//Init TOF
	initialisation_mesure_capteur();

	int index = 0;
	for(;;){
		ulTaskNotifyTake(pdTRUE,portMAX_DELAY);
		index++;
		mesure_et_affichage();
		vTaskDelay(200);
		if(index==TAB_SIZE2){
			index=0;
			//ulTaskNotifyTake(pdTRUE,portMAX_DELAY);
		}
	}
}

