/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include "adc.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "XL320.h"
#include "stdio.h"
#include <stdlib.h>
#include "shell.h"
#include "drv_uart1.h"
#include "motor.h"
#include "encoder.h"
#include "vl53l0x_api.h"
#include "TOF.h"
#include "servomotor.h"
#include "demo.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define DEMO_STACK_SIZE 500
//#define TASK_SHELL_STACK_DEPTH 500
#define MOTOR_STACK_SIZE 500
#define ENCODER_STACK_SIZE 500
#define ENCODER_PRINT_STACK_SIZE 500
#define TOF_STACK_SIZE 500
#define SERVO_STACK_SIZE 500
#define BORDURE_STACK_SIZE 500
#define RECHERCHE_STACK_SIZE 500
#define TROUVE_STACK_SIZE 500
#define ATTRAPE_STACK_SIZE 500

#define DEMO_PRIORITY 1 //Mettre la priorité au plus bas si on veut utiliser le shell
//#define TASK_SHELL_PRIORITY 2
#define MOTOR_PRIORITY 10
#define ENCODER_PRIORITY 4
#define ENCODER_PRINT_PRIORITY 3
#define TOF_PRIORITY 8
#define SERVO_PRIORITY 7
#define BORDURE_PRIORITY 9
#define RECHERCHE_PRIORITY 6
#define TROUVE_PRIORITY 6
#define ATTRAPE_PRIORITY 6

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
extern TaskHandle_t h_motor;
//extern TaskHandle_t h_task_shell;
extern TaskHandle_t h_encoder;
extern TaskHandle_t h_encoder_print;
extern TaskHandle_t h_tof;
extern TaskHandle_t h_servomotor;
extern TaskHandle_t h_bordure;
extern TaskHandle_t h_recherche;
extern TaskHandle_t h_trouve;
extern TaskHandle_t h_attrape;

TaskHandle_t h_notif;
extern TaskHandle_t h_task_demo;

extern h_motor_t h_cmd_motor;
extern h_servomotor_t h_cmd_servomotor;
//static h_shell_t shell_funct1;
static h_demo_t demo_funct1;

extern h_asser_t asservissement_gauche;
extern h_asser_t asservissement_droit;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void MX_FREERTOS_Init(void);
/* USER CODE BEGIN PFP */
void servo();
void clignote();
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int __io_putchar(int ch){
	HAL_UART_Transmit(&huart1, (uint8_t*)&ch, 1, HAL_MAX_DELAY);
	return ch;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart->Instance == USART1)
	{
		shell_uart_receive_irq_cb();
	}
}

int fonction(h_shell_t * pshell, int argc, char ** argv)
{
	printf("Je suis une fonction bidon\r\n");

	printf("argc = %d\r\n", argc);

	for (int i = 0 ; i < argc ; i++)
	{
		printf("arg %d = %s\r\n", i, argv[i]);
	}

	return 0;
}

int addition(h_shell_t *pshell, int argc, char ** argv)
{
	if (argc == 3)
	{
		int a, b;
		a = atoi(argv[1]);
		b = atoi(argv[2]);
		printf("%d + %d = %d\r\n", a, b, a+b);
		return 0;
	}
	else
	{
		printf("Erreur, pas le bon nombre d'arguments\r\n");
		return -1;
	}
}
/*
int servo_open(h_shell_t *pshell,int argc, char ** argv){
	open();
	return 0;
}
int servo_close(h_shell_t *pshell,int argc, char ** argv){
	close();
	return 0;
}
int servo_work(h_shell_t *pshell,int argc, char ** argv){
	servo();
	return 0;
}
int servo_speed(h_shell_t *pshell,int argc, char ** argv){
	int value=atoi(argv[1]);
	printf("La vitesse est de: %d sur 1023\r\n",value);
	speed(value);
	return 0;
}
 */

#if 0
void task_shell(void * unused)
{
	shell_init(&shell_funct1);
	shell_add(&shell_funct1,'f', fonction, "Une fonction inutile");
	shell_add(&shell_funct1,'a', addition, "Effectue une somme");

	shell_add(&shell_funct1,'d', moteurDroit, "Moteur droit");
	shell_add(&shell_funct1,'g', moteurGauche, "Moteur gauche");
	shell_add(&shell_funct1,'m', motor_shell, "Commande moteur");

	shell_add(&shell_funct1,'e', encoder_shell, "Active encodeur");

	//shell_add(&shell_funct1,'o',servo_open,"j'ouvre pince");
	//shell_add(&shell_funct1,'c',servo_close,"je ferme la pince");
	//shell_add(&shell_funct1,'w',servo_work,"ouvre_ferme");
	//shell_add(&shell_funct1,'s',servo_speed,"Speed");
	shell_add(&shell_funct1,'s',servo_shell,"Commande servomoteur");

	shell_add(&shell_funct1,'t',TOF_shell,"Active TOF");


	//shell_add(&shell_funct1,'l',led,"set la vitesse de clignotement");
	for(;;){
		shell_run(&shell_funct1); // boucle infinie
	}
}
#endif

void task_demo(void * unused)
{
	for(;;){
		demo_run(&demo_funct1); //boucle infinie
	}
}
/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
	/* USER CODE BEGIN 1 */

	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_I2C2_Init();
	MX_TIM1_Init();
	MX_TIM3_Init();
	MX_TIM14_Init();
	MX_USART1_UART_Init();
	MX_TIM16_Init();
	MX_I2C1_Init();
	MX_TIM17_Init();
	MX_USART2_UART_Init();
	MX_ADC1_Init();
	/* USER CODE BEGIN 2 */

	/*
	printf("coucou\r\n");
	if (xTaskCreate(task_shell, "Shell", TASK_SHELL_STACK_DEPTH, NULL, TASK_SHELL_PRIORITY, &h_task_shell) != pdPASS)
	{
		printf("Error creating task shell\r\n");
		//Error_Handler();
	}
	else{
		printf("C'est bon\r\n");
	}*/

	BaseType_t ret;
	ret = xTaskCreate(task_demo, "Demo", DEMO_STACK_SIZE,NULL, DEMO_PRIORITY,&h_task_demo);
	if (ret == errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY){
		printf("Error creating task demo\r\n");
		Error_Handler();
	}
	printf("coucou task motor\r\n");
	ret = xTaskCreate(taskMotor,"Motor",MOTOR_STACK_SIZE,(void*)&h_cmd_motor, MOTOR_PRIORITY, &h_motor);
	if (ret == errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY){
		printf("Error Task Motor\r\n");
		Error_Handler();
	}
	printf("bye bye task motor\r\n");
	printf("coucou task encoder\r\n");
	ret = xTaskCreate(taskEncoder,"Encoder",ENCODER_STACK_SIZE,NULL, ENCODER_PRIORITY, &h_encoder);
	if (ret == errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY){
		printf("Error Task Encoder\r\n");
		Error_Handler();
	}
	printf("coucou task encoder\r\n");
	ret = xTaskCreate(taskEncoderPrint,"Encoder Print",ENCODER_PRINT_STACK_SIZE,NULL, ENCODER_PRINT_PRIORITY, &h_encoder_print);
	if (ret == errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY){
		printf("Error Task Encoder Print\r\n");
		Error_Handler();
	}
	printf("coucou task TOF\r\n");
	ret = xTaskCreate(taskTOF,"TOF",TOF_STACK_SIZE,NULL,TOF_PRIORITY,&h_tof);
	if (ret == errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY){
		printf("Error Task TOF\r\n");
		Error_Handler();
	}
	printf("bye bye task TOF\r\n");
	printf("coucou task servo\r\n");
	ret = xTaskCreate(taskServoMotor,"Servomoteur",SERVO_STACK_SIZE,(void*)&h_cmd_servomotor,SERVO_PRIORITY,&h_servomotor);
	if (ret == errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY){
		printf("Error Task Servomotor\r\n");
		Error_Handler();
	}
	printf("bye bye task servo\r\n");
	printf("coucou task bordure\r\n");
	ret = xTaskCreate(taskBordure,"Bordure",BORDURE_STACK_SIZE,(void*)&h_cmd_motor,BORDURE_PRIORITY,&h_bordure);
	if (ret == errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY){
		printf("Error Task Bordure\r\n");
		Error_Handler();
	}
	printf("bye bye task bordure\r\n");
	ret = xTaskCreate(taskRecherche,"Recherche",RECHERCHE_STACK_SIZE,(void*)&h_cmd_motor,RECHERCHE_PRIORITY,&h_recherche);
	if (ret == errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY){
		printf("Error Task Recherche\r\n");
		Error_Handler();
	}
	printf("bye bye task Recherche\r\n");

	ret = xTaskCreate(taskTrouve,"Trouve",TROUVE_STACK_SIZE,(void*)&h_cmd_motor,TROUVE_PRIORITY,&h_trouve);
	if (ret == errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY){
		printf("Error Task Trouve\r\n");
		Error_Handler();
	}
	printf("bye bye task Trouve\r\n");

	ret = xTaskCreate(taskAttrape,"Attrape",ATTRAPE_STACK_SIZE,(void*)&h_cmd_motor,ATTRAPE_PRIORITY,&h_attrape);
	if (ret == errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY){
		printf("Error Task Attrape\r\n");
		Error_Handler();
	}
	printf("bye bye task Attrape\r\n");
	/* USER CODE END 2 */

	/* Call init function for freertos objects (in freertos.c) */
	MX_FREERTOS_Init();

	/* Start scheduler */
	osKernelStart();

	/* We should never get here as control is now taken by the scheduler */
	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1)
	{
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

	/** Configure the main internal regulator output voltage
	 */
	HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV1;
	RCC_OscInitStruct.PLL.PLLN = 8;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
			|RCC_CLOCKTYPE_PCLK1;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
	{
		Error_Handler();
	}
}

/* USER CODE BEGIN 4 */
void HAL_GPIO_EXTI_Rising_Callback(uint16_t GPIO_Pin){
	//HAL_UART_Transmit(&huart1, "Stop\r\n", 8, HAL_MAX_DELAY);
	xTaskNotifyGive(h_bordure);
	//vTaskResume(h_motor);
}
/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1)
	{
	}
	/* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
	/* USER CODE BEGIN 6 */
	/* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	/* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
