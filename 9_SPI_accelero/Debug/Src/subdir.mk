################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/acc.c \
../Src/gyro.c \
../Src/i2c.c \
../Src/main.c \
../Src/spi.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/usart.c 

OBJS += \
./Src/acc.o \
./Src/gyro.o \
./Src/i2c.o \
./Src/main.o \
./Src/spi.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/usart.o 

C_DEPS += \
./Src/acc.d \
./Src/gyro.d \
./Src/i2c.d \
./Src/main.d \
./Src/spi.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F303VCTx -DSTM32 -DSTM32F3 -DSTM32F3DISCOVERY -DSTM32F303xC -c -I../Inc -I/home/rohiths/STraining/STM32/chip_headers/CMSIS/Device/ST/STM32F3xx/Include -I/home/rohiths/STraining/STM32/chip_headers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/acc.cyclo ./Src/acc.d ./Src/acc.o ./Src/acc.su ./Src/gyro.cyclo ./Src/gyro.d ./Src/gyro.o ./Src/gyro.su ./Src/i2c.cyclo ./Src/i2c.d ./Src/i2c.o ./Src/i2c.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/spi.cyclo ./Src/spi.d ./Src/spi.o ./Src/spi.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su ./Src/usart.cyclo ./Src/usart.d ./Src/usart.o ./Src/usart.su

.PHONY: clean-Src

