################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Generated_Code/AS1.c \
../Generated_Code/AS2.c \
../Generated_Code/AS3.c \
../Generated_Code/ASerialLdd1.c \
../Generated_Code/ASerialLdd2.c \
../Generated_Code/ASerialLdd3.c \
../Generated_Code/Cpu.c \
../Generated_Code/LED_AZUL.c \
../Generated_Code/LED_ROJO.c \
../Generated_Code/LED_VERDE.c \
../Generated_Code/PE_LDD.c \
../Generated_Code/Pins1.c \
../Generated_Code/TI1.c \
../Generated_Code/TU1.c \
../Generated_Code/TimerIntLdd1.c 

OBJS += \
./Generated_Code/AS1.o \
./Generated_Code/AS2.o \
./Generated_Code/AS3.o \
./Generated_Code/ASerialLdd1.o \
./Generated_Code/ASerialLdd2.o \
./Generated_Code/ASerialLdd3.o \
./Generated_Code/Cpu.o \
./Generated_Code/LED_AZUL.o \
./Generated_Code/LED_ROJO.o \
./Generated_Code/LED_VERDE.o \
./Generated_Code/PE_LDD.o \
./Generated_Code/Pins1.o \
./Generated_Code/TI1.o \
./Generated_Code/TU1.o \
./Generated_Code/TimerIntLdd1.o 

C_DEPS += \
./Generated_Code/AS1.d \
./Generated_Code/AS2.d \
./Generated_Code/AS3.d \
./Generated_Code/ASerialLdd1.d \
./Generated_Code/ASerialLdd2.d \
./Generated_Code/ASerialLdd3.d \
./Generated_Code/Cpu.d \
./Generated_Code/LED_AZUL.d \
./Generated_Code/LED_ROJO.d \
./Generated_Code/LED_VERDE.d \
./Generated_Code/PE_LDD.d \
./Generated_Code/Pins1.d \
./Generated_Code/TI1.d \
./Generated_Code/TU1.d \
./Generated_Code/TimerIntLdd1.d 


# Each subdirectory must supply rules for building sources it contributes
Generated_Code/%.o: ../Generated_Code/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"C:\Freescale\KDS_2.0.0\eclipse\ProcessorExpert/lib/Kinetis/pdd2/MK64FN1M0LQ12/system" -I"C:\Freescale\KDS_2.0.0\eclipse\ProcessorExpert/lib/Kinetis/pdd/inc" -I"C:\Freescale\KDS_2.0.0\eclipse\ProcessorExpert/lib/Kinetis/iofiles" -I"C:/Users/Sandra/GitHubKinetis/ControlMotor/ControlMotor/Sources" -I"C:/Users/Sandra/GitHubKinetis/ControlMotor/ControlMotor/Generated_Code" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


