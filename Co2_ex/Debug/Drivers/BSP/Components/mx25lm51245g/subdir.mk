################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/Components/mx25lm51245g/mx25lm51245g.c 

C_DEPS += \
./Drivers/BSP/Components/mx25lm51245g/mx25lm51245g.d 

OBJS += \
./Drivers/BSP/Components/mx25lm51245g/mx25lm51245g.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/Components/mx25lm51245g/%.o Drivers/BSP/Components/mx25lm51245g/%.su: ../Drivers/BSP/Components/mx25lm51245g/%.c Drivers/BSP/Components/mx25lm51245g/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DFX_INCLUDE_USER_DEFINE_FILE -DLX_INCLUDE_USER_DEFINE_FILE -DTX_INCLUDE_USER_DEFINE_FILE -DTX_SINGLE_MODE_NON_SECURE=1 -DUSE_HAL_DRIVER -DSTM32U585xx -c -I../FileX/App -I../FileX/Target -I../LevelX/App -I../Core/Inc -I../LevelX/Target -I../AZURE_RTOS/App -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/levelx/common/inc -I../Drivers/BSP/Components/mx25lm51245g -I../Middlewares/ST/threadx/common/inc -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Middlewares/ST/filex/common/inc -I../Middlewares/ST/filex/ports/generic/inc -I../Middlewares/ST/threadx/ports/cortex_m33/gnu/inc -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/ittia_db_iot/common/inc -I../Drivers/BSP/B-U585I-IOT02A -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-Components-2f-mx25lm51245g

clean-Drivers-2f-BSP-2f-Components-2f-mx25lm51245g:
	-$(RM) ./Drivers/BSP/Components/mx25lm51245g/mx25lm51245g.d ./Drivers/BSP/Components/mx25lm51245g/mx25lm51245g.o ./Drivers/BSP/Components/mx25lm51245g/mx25lm51245g.su

.PHONY: clean-Drivers-2f-BSP-2f-Components-2f-mx25lm51245g

