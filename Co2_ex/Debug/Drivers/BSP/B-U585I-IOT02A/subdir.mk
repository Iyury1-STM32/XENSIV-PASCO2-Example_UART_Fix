################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/B-U585I-IOT02A/b_u585i_iot02a.c \
../Drivers/BSP/B-U585I-IOT02A/b_u585i_iot02a_bus.c \
../Drivers/BSP/B-U585I-IOT02A/b_u585i_iot02a_env_sensors.c \
../Drivers/BSP/B-U585I-IOT02A/b_u585i_iot02a_light_sensor.c \
../Drivers/BSP/B-U585I-IOT02A/b_u585i_iot02a_motion_sensors.c 

C_DEPS += \
./Drivers/BSP/B-U585I-IOT02A/b_u585i_iot02a.d \
./Drivers/BSP/B-U585I-IOT02A/b_u585i_iot02a_bus.d \
./Drivers/BSP/B-U585I-IOT02A/b_u585i_iot02a_env_sensors.d \
./Drivers/BSP/B-U585I-IOT02A/b_u585i_iot02a_light_sensor.d \
./Drivers/BSP/B-U585I-IOT02A/b_u585i_iot02a_motion_sensors.d 

OBJS += \
./Drivers/BSP/B-U585I-IOT02A/b_u585i_iot02a.o \
./Drivers/BSP/B-U585I-IOT02A/b_u585i_iot02a_bus.o \
./Drivers/BSP/B-U585I-IOT02A/b_u585i_iot02a_env_sensors.o \
./Drivers/BSP/B-U585I-IOT02A/b_u585i_iot02a_light_sensor.o \
./Drivers/BSP/B-U585I-IOT02A/b_u585i_iot02a_motion_sensors.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/B-U585I-IOT02A/%.o Drivers/BSP/B-U585I-IOT02A/%.su: ../Drivers/BSP/B-U585I-IOT02A/%.c Drivers/BSP/B-U585I-IOT02A/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DFX_INCLUDE_USER_DEFINE_FILE -DLX_INCLUDE_USER_DEFINE_FILE -DTX_INCLUDE_USER_DEFINE_FILE -DTX_SINGLE_MODE_NON_SECURE=1 -DUSE_HAL_DRIVER -DSTM32U585xx -c -I../FileX/App -I../FileX/Target -I../LevelX/App -I../Core/Inc -I../LevelX/Target -I../AZURE_RTOS/App -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/levelx/common/inc -I../Drivers/BSP/Components/mx25lm51245g -I../Middlewares/ST/threadx/common/inc -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Middlewares/ST/filex/common/inc -I../Middlewares/ST/filex/ports/generic/inc -I../Middlewares/ST/threadx/ports/cortex_m33/gnu/inc -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/ittia_db_iot/common/inc -I../Drivers/BSP/B-U585I-IOT02A -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-B-2d-U585I-2d-IOT02A

clean-Drivers-2f-BSP-2f-B-2d-U585I-2d-IOT02A:
	-$(RM) ./Drivers/BSP/B-U585I-IOT02A/b_u585i_iot02a.d ./Drivers/BSP/B-U585I-IOT02A/b_u585i_iot02a.o ./Drivers/BSP/B-U585I-IOT02A/b_u585i_iot02a.su ./Drivers/BSP/B-U585I-IOT02A/b_u585i_iot02a_bus.d ./Drivers/BSP/B-U585I-IOT02A/b_u585i_iot02a_bus.o ./Drivers/BSP/B-U585I-IOT02A/b_u585i_iot02a_bus.su ./Drivers/BSP/B-U585I-IOT02A/b_u585i_iot02a_env_sensors.d ./Drivers/BSP/B-U585I-IOT02A/b_u585i_iot02a_env_sensors.o ./Drivers/BSP/B-U585I-IOT02A/b_u585i_iot02a_env_sensors.su ./Drivers/BSP/B-U585I-IOT02A/b_u585i_iot02a_light_sensor.d ./Drivers/BSP/B-U585I-IOT02A/b_u585i_iot02a_light_sensor.o ./Drivers/BSP/B-U585I-IOT02A/b_u585i_iot02a_light_sensor.su ./Drivers/BSP/B-U585I-IOT02A/b_u585i_iot02a_motion_sensors.d ./Drivers/BSP/B-U585I-IOT02A/b_u585i_iot02a_motion_sensors.o ./Drivers/BSP/B-U585I-IOT02A/b_u585i_iot02a_motion_sensors.su

.PHONY: clean-Drivers-2f-BSP-2f-B-2d-U585I-2d-IOT02A

