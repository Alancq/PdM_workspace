################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/BSP/stm32f7xx_nucleo_144.c 

OBJS += \
./Core/BSP/stm32f7xx_nucleo_144.o 

C_DEPS += \
./Core/BSP/stm32f7xx_nucleo_144.d 


# Each subdirectory must supply rules for building sources it contributes
Core/BSP/%.o Core/BSP/%.su: ../Core/BSP/%.c Core/BSP/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F767xx -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I"/home/alan/embebidos/PdM_workspace/nucleoF767_tp4/Drivers/API/Inc" -I"/home/alan/embebidos/PdM_workspace/nucleoF767_tp4/Drivers/API/Src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-BSP

clean-Core-2f-BSP:
	-$(RM) ./Core/BSP/stm32f7xx_nucleo_144.d ./Core/BSP/stm32f7xx_nucleo_144.o ./Core/BSP/stm32f7xx_nucleo_144.su

.PHONY: clean-Core-2f-BSP

