################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Asser/encoder.c \
../Asser/motor.c \
../Asser/servomotor.c 

OBJS += \
./Asser/encoder.o \
./Asser/motor.o \
./Asser/servomotor.o 

C_DEPS += \
./Asser/encoder.d \
./Asser/motor.d \
./Asser/servomotor.d 


# Each subdirectory must supply rules for building sources it contributes
Asser/%.o Asser/%.su: ../Asser/%.c Asser/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G070xx -c -I../Core/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0 -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -I"C:/CubeIDEv101/ESE_Projet/Asser" -I"C:/CubeIDEv101/ESE_Projet/Sensors" -I"C:/CubeIDEv101/ESE_Projet/shell" -I"C:/CubeIDEv101/ESE_Projet/Drivers/VL53L0X/core/inc" -I"C:/CubeIDEv101/ESE_Projet/Drivers/VL53L0X/core/src" -I"C:/CubeIDEv101/ESE_Projet/Drivers/VL53L0X/platform/inc" -I"C:/CubeIDEv101/ESE_Projet/Drivers/VL53L0X/platform/src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Asser

clean-Asser:
	-$(RM) ./Asser/encoder.d ./Asser/encoder.o ./Asser/encoder.su ./Asser/motor.d ./Asser/motor.o ./Asser/motor.su ./Asser/servomotor.d ./Asser/servomotor.o ./Asser/servomotor.su

.PHONY: clean-Asser

