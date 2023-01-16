/*
 * TOF.h
 *
 *  Created on: 6 janv. 2023
 *      Author: Loicia
 */

#ifndef TOF_H_
#define TOF_H_

#include <stdint.h>
#include "shell.h"
#include "main.h"

#define TAB_SIZE2 300 //5 mesures faites quand la tache TOF est appelée

void clignotage_led_stm32();
void capteur_mesure();
void initialisation_mesure_capteur();
void mesure_et_affichage();
void TOF_Enable(int,GPIO_PinState);

void taskTOF(void *pTOF);
int TOF_shell(h_shell_t * pshell, int argc, char ** argv);

#endif /* TOF_H_ */
