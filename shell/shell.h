/*
 * shell.h
 *
 *  Created on:
 *      Author:
 */

#ifndef INC_LIB_SHELL_SHELL_H_
#define INC_LIB_SHELL_SHELL_H_

#include <stdint.h>
#include <string.h>

#define UART_DEVICE huart1

#define ARGC_MAX 8
#define BUFFER_SIZE 40
#define SHELL_FUNC_LIST_MAX_SIZE 64

struct h_shell_struct;

typedef int (*shell_func_pointer_t)(struct h_shell_struct * h_shell, int argc, char ** argv);
typedef uint8_t (* drv_shell_transmit_t)(const char * pData, uint16_t size);
typedef uint8_t (* drv_shell_receive_t)(char * pData, uint16_t size);

typedef struct{
	char c;
	int (* func)(struct h_shell_struct *pshell,int argc, char ** argv);
	char * description;
} shell_func_t;

typedef struct h_shell_struct{
	int shell_func_list_size;
	shell_func_t shell_func_list[SHELL_FUNC_LIST_MAX_SIZE];
	char print_buffer[BUFFER_SIZE];
	char backspace[3];
	char prompt[2];
	char cmd_buffer[BUFFER_SIZE];
}h_shell_t;

typedef struct drv_shell_struct
{
	drv_shell_transmit_t drv_shell_transmit;
	drv_shell_receive_t drv_shell_receive;
} drv_shell_t;

void shell_init(h_shell_t *pshell);
int shell_add(h_shell_t *pshell, char c, int (* pfunc)(h_shell_t *pshell,int argc, char ** argv), char * description);
int shell_run(h_shell_t *pshell);
// commentaire documentation!
void shell_uart_receive_irq_cb(void);

#endif  /*INC_LIB_SHELL_SHELL_H_*/




