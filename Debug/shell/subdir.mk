################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../shell/demo.c \
../shell/drv_uart1.c \
../shell/shell.c 

OBJS += \
./shell/demo.o \
./shell/drv_uart1.o \
./shell/shell.o 

C_DEPS += \
./shell/demo.d \
./shell/drv_uart1.d \
./shell/shell.d 


# Each subdirectory must supply rules for building sources it contributes
shell/%.o shell/%.su: ../shell/%.c shell/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G070xx -c -I../Core/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0 -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -I"C:/CubeIDEv101/ESE_Projet/Asser" -I"C:/CubeIDEv101/ESE_Projet/Sensors" -I"C:/CubeIDEv101/ESE_Projet/shell" -I"C:/CubeIDEv101/ESE_Projet/Drivers/VL53L0X/core/inc" -I"C:/CubeIDEv101/ESE_Projet/Drivers/VL53L0X/core/src" -I"C:/CubeIDEv101/ESE_Projet/Drivers/VL53L0X/platform/inc" -I"C:/CubeIDEv101/ESE_Projet/Drivers/VL53L0X/platform/src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-shell

clean-shell:
	-$(RM) ./shell/demo.d ./shell/demo.o ./shell/demo.su ./shell/drv_uart1.d ./shell/drv_uart1.o ./shell/drv_uart1.su ./shell/shell.d ./shell/shell.o ./shell/shell.su

.PHONY: clean-shell

