################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/autumn_security.c \
../Core/Src/gpio.c \
../Core/Src/main.c \
../Core/Src/simple_io.c \
../Core/Src/stm32f4xx_hal_msp.c \
../Core/Src/stm32f4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/system_stm32f4xx.c \
../Core/Src/usart.c 

OBJS += \
./Core/Src/autumn_security.o \
./Core/Src/gpio.o \
./Core/Src/main.o \
./Core/Src/simple_io.o \
./Core/Src/stm32f4xx_hal_msp.o \
./Core/Src/stm32f4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/system_stm32f4xx.o \
./Core/Src/usart.o 

C_DEPS += \
./Core/Src/autumn_security.d \
./Core/Src/gpio.d \
./Core/Src/main.d \
./Core/Src/simple_io.d \
./Core/Src/stm32f4xx_hal_msp.d \
./Core/Src/stm32f4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/system_stm32f4xx.d \
./Core/Src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o: ../Core/Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32F407xx -I"/home/semitro/Рабочий стол/itmo/EMBEDDED/EmbeddedSystemsLabWorks/lab1_LEDS_GO/Core/Inc" -I"/home/semitro/Рабочий стол/itmo/EMBEDDED/EmbeddedSystemsLabWorks/lab1_LEDS_GO/Drivers/STM32F4xx_HAL_Driver/Inc" -I"/home/semitro/Рабочий стол/itmo/EMBEDDED/EmbeddedSystemsLabWorks/lab1_LEDS_GO/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"/home/semitro/Рабочий стол/itmo/EMBEDDED/EmbeddedSystemsLabWorks/lab1_LEDS_GO/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"/home/semitro/Рабочий стол/itmo/EMBEDDED/EmbeddedSystemsLabWorks/lab1_LEDS_GO/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


