/*
 * shell.c
 *
 *  Created on:
 *      Author:
 */

#include "shell.h"

#include "cmsis_os.h"

#include <stdio.h>

#include "usart.h"
#include "gpio.h"


TaskHandle_t h_task_shell = NULL;

static SemaphoreHandle_t sem_uart_read = NULL;

void shell_uart_receive_irq_cb(void)
{
	BaseType_t pxHigherPriorityTaskWoken = pdFALSE;

	xSemaphoreGiveFromISR(sem_uart_read, &pxHigherPriorityTaskWoken);

	portYIELD_FROM_ISR(pxHigherPriorityTaskWoken);
}

static char uart_read() {
	char c;

	HAL_UART_Receive_IT(&UART_DEVICE, (uint8_t*)(&c), 1);
	// il faut mettre la tâche shell dans l'état bloqué, jusqu'à l'interruption de réception de caractère
	// prendre un sémaphore vide par exemple
	xSemaphoreTake(sem_uart_read, portMAX_DELAY);

	return c;
}

static int uart_write(char * s, uint16_t size) {
	HAL_UART_Transmit(&UART_DEVICE, (uint8_t*)s, size, HAL_MAX_DELAY);
	return size;
}

static int sh_help(h_shell_t *pshell, int argc, char ** argv) {
	int i;
	for(i = 0 ; i < pshell->shell_func_list_size ; i++) {
		int size;
		size = snprintf (pshell->print_buffer, BUFFER_SIZE, "%c: %s\r\n", pshell->shell_func_list[i].c, pshell->shell_func_list[i].description);
		uart_write(pshell->print_buffer, size);
	}

	return 0;
}

void shell_init(h_shell_t *pshell) {
	int size = 0;
	pshell->shell_func_list_size = 0;
	sprintf(pshell->backspace,"\b \b");
	sprintf(pshell->prompt,"> ");
	size = snprintf (pshell->print_buffer, BUFFER_SIZE, "\r\n\r\n===== Robot beer shell =====\r\n");
	uart_write(pshell->print_buffer, size);

	sem_uart_read = xSemaphoreCreateBinary();
	if (sem_uart_read == NULL)
	{
		printf("Error semaphore shell\r\n");
		while(1);
	}

	shell_add(pshell,'h', sh_help, "Help");

}

int shell_add(h_shell_t *pshell, char c, int (* pfunc)(h_shell_t *pshell,int argc, char ** argv), char * description) {
	if (pshell->shell_func_list_size < SHELL_FUNC_LIST_MAX_SIZE) {
		pshell->shell_func_list[pshell->shell_func_list_size].c = c;
		pshell->shell_func_list[pshell->shell_func_list_size].func = pfunc;
		pshell->shell_func_list[pshell->shell_func_list_size].description = description;
		pshell->shell_func_list_size++;
		return 0;
	}

	return -1;
}

static int shell_exec( h_shell_t *pshell, char * buf) {
	int i;

	char c = buf[0];

	int argc;
	char * argv[ARGC_MAX];
	char *p;

	for(i = 0 ; i < pshell->shell_func_list_size ; i++) {
		if (pshell->shell_func_list[i].c == c) {
			argc = 1;
			argv[0] = buf;

			for(p = buf ; *p != '\0' && argc < ARGC_MAX ; p++){
				if(*p == ' ') {
					*p = '\0';
					argv[argc++] = p+1;
				}
			}

			return pshell->shell_func_list[i].func(pshell,argc, argv);
		}
	}

	int size;
	size = snprintf (pshell->print_buffer, BUFFER_SIZE, "%c: no such command\r\n", c);
	uart_write(pshell->print_buffer, size);
	return -1;
}


int shell_run(h_shell_t *pshell) {
	int reading = 0;
	int pos = 0;


	while (1) {
		uart_write(pshell->prompt, 2);
		reading = 1;

		while(reading) {
			char c = uart_read();
			int size;

			switch (c) {
			//process RETURN key
			case '\r':
				//case '\n':
				size = snprintf (pshell->print_buffer, BUFFER_SIZE, "\r\n");
				uart_write(pshell->print_buffer, size);
				pshell->cmd_buffer[pos++] = 0;     //add \0 char at end of string
				size = snprintf (pshell->print_buffer, BUFFER_SIZE, ":%s\r\n", pshell->cmd_buffer);
				uart_write(pshell->print_buffer, size);
				reading = 0;        //exit read loop
				pos = 0;            //reset buffer
				break;
				//backspace
			case '\b':
				if (pos > 0) {      //is there a char to delete?
					pos--;          //remove it in buffer

					uart_write(pshell->backspace, 3);	// delete the char on the terminal
				}
				break;
				//other characters
			default:
				//only store characters if buffer has space
				if (pos < BUFFER_SIZE) {
					uart_write(&c, 1);
					pshell->cmd_buffer[pos++] = c; //store
				}
			}
		}
		shell_exec(pshell,pshell->cmd_buffer);
	}
	return 0;
}



