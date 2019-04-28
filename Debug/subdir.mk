################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../8led.c \
../button.c \
../gameLogic.c \
../keyboard.c \
../lcd.c \
../led.c \
../main.c \
../uart.c \
../visualizacion.c 

OBJS += \
./8led.o \
./button.o \
./gameLogic.o \
./keyboard.o \
./lcd.o \
./led.o \
./main.o \
./uart.o \
./visualizacion.o 

C_DEPS += \
./8led.d \
./button.d \
./gameLogic.d \
./keyboard.d \
./lcd.d \
./led.d \
./main.d \
./uart.d \
./visualizacion.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -I"C:\hlocal\workspace\proyecto\commonUart" -O0 -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -mapcs-frame -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm7tdmi -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


