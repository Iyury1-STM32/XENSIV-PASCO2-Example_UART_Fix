################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/ST/filex/common/drivers/fx_stm32_levelx_nor_driver.c 

C_DEPS += \
./Middlewares/ST/filex/common/drivers/fx_stm32_levelx_nor_driver.d 

OBJS += \
./Middlewares/ST/filex/common/drivers/fx_stm32_levelx_nor_driver.o 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/ST/filex/common/drivers/%.o Middlewares/ST/filex/common/drivers/%.su: ../Middlewares/ST/filex/common/drivers/%.c Middlewares/ST/filex/common/drivers/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DFX_INCLUDE_USER_DEFINE_FILE -DLX_INCLUDE_USER_DEFINE_FILE -DTX_INCLUDE_USER_DEFINE_FILE -DTX_SINGLE_MODE_NON_SECURE=1 -DUSE_HAL_DRIVER -DSTM32U585xx -c -I../FileX/App -I../FileX/Target -I../LevelX/App -I../Core/Inc -I../LevelX/Target -I../AZURE_RTOS/App -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/levelx/common/inc -I../Drivers/BSP/Components/mx25lm51245g -I../Middlewares/ST/threadx/common/inc -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Middlewares/ST/filex/common/inc -I../Middlewares/ST/filex/ports/generic/inc -I../Middlewares/ST/threadx/ports/cortex_m33/gnu/inc -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/ittia_db_iot/common/inc -I../Drivers/BSP/B-U585I-IOT02A -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-ST-2f-filex-2f-common-2f-drivers

clean-Middlewares-2f-ST-2f-filex-2f-common-2f-drivers:
	-$(RM) ./Middlewares/ST/filex/common/drivers/fx_stm32_levelx_nor_driver.d ./Middlewares/ST/filex/common/drivers/fx_stm32_levelx_nor_driver.o ./Middlewares/ST/filex/common/drivers/fx_stm32_levelx_nor_driver.su

.PHONY: clean-Middlewares-2f-ST-2f-filex-2f-common-2f-drivers

