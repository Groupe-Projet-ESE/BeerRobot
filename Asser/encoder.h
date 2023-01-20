/*
 * encoder.h
 *
 *  Created on: 19 déc. 2022
 *      Author: chels
 */

#ifndef ENCODER_H_
#define ENCODER_H_

#include <stdint.h>
#include "shell.h"

#define TAB_SIZE 100
#define R 21 	//Rayon roue
#define PI 3.14159
#define REVOLUTION  44 //Count par résolution

typedef struct h_encoder_struct{

	int16_t countTIM;
	int16_t position;
	float speed;
	int16_t tab_pos[TAB_SIZE];
	uint8_t Ts;

}h_encoder_t;

typedef struct h_asser_struct{

	uint32_t integration;
	uint32_t speed_consigne;
	uint32_t erreur;
	uint32_t Kp;
	uint32_t Ki;
	uint16_t duty;

}h_asser_t;

int encoder_shell(h_shell_t * pshell, int argc, char ** argv);
void taskEncoder(void *pEncoder);
void taskEncoderPrint(void *pPrint);

int get_left_tick();
int get_right_tick();
void update_gauche(int vitesse );
void update_droite(int vitesse);

#endif /* ENCODER_H_ */
