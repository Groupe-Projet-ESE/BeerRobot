/*
 * servomotor.h
 *
 *  Created on: Jan 10, 2023
 *      Author: Loicia
 */


#ifndef SERVOMOTOR_H_
#define SERVOMOTOR_H_

#include <stdint.h>
#include "shell.h"
#include "servomotor.h"
#include "main.h"
#include "tim.h"
#include "cmsis_os.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "XL320.h"

typedef struct h_servomotor_struct{
	char cmd;
	uint16_t speed;
}h_servomotor_t;


int servo_shell(h_shell_t * pshell, int argc, char ** argv);

void taskServoMotor(void *pServoMotor);


#endif /* SERVOMOTOR_H_ */
