################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Src/stm3f407xx_gpio_drivers.c \
../Drivers/Src/stm3f407xx_spi_drivers.c 

OBJS += \
./Drivers/Src/stm3f407xx_gpio_drivers.o \
./Drivers/Src/stm3f407xx_spi_drivers.o 

C_DEPS += \
./Drivers/Src/stm3f407xx_gpio_drivers.d \
./Drivers/Src/stm3f407xx_spi_drivers.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Src/%.o Drivers/Src/%.su Drivers/Src/%.cyclo: ../Drivers/Src/%.c Drivers/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F407G_DISC1 -DSTM32F4 -DSTM32F407VGTx -c -I"D:/Embedded-C/My_Workspace/target/Driver_devlopment/Drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-Src

clean-Drivers-2f-Src:
	-$(RM) ./Drivers/Src/stm3f407xx_gpio_drivers.cyclo ./Drivers/Src/stm3f407xx_gpio_drivers.d ./Drivers/Src/stm3f407xx_gpio_drivers.o ./Drivers/Src/stm3f407xx_gpio_drivers.su ./Drivers/Src/stm3f407xx_spi_drivers.cyclo ./Drivers/Src/stm3f407xx_spi_drivers.d ./Drivers/Src/stm3f407xx_spi_drivers.o ./Drivers/Src/stm3f407xx_spi_drivers.su

.PHONY: clean-Drivers-2f-Src

