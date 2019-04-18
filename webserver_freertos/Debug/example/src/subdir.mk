################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../example/src/cr_redlib_heap_fix.c \
../example/src/cr_startup_lpc175x_6x.c \
../example/src/lwip_fs.c \
../example/src/netconn_fs.c \
../example/src/sysinit.c \
../example/src/webserver_freertos.c 

OBJS += \
./example/src/cr_redlib_heap_fix.o \
./example/src/cr_startup_lpc175x_6x.o \
./example/src/lwip_fs.o \
./example/src/netconn_fs.o \
./example/src/sysinit.o \
./example/src/webserver_freertos.o 

C_DEPS += \
./example/src/cr_redlib_heap_fix.d \
./example/src/cr_startup_lpc175x_6x.d \
./example/src/lwip_fs.d \
./example/src/netconn_fs.d \
./example/src/sysinit.d \
./example/src/webserver_freertos.d 


# Each subdirectory must supply rules for building sources it contributes
example/src/%.o: ../example/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_LPCOPEN -DCORE_M3 -I"/home/jpatel/Downloads/freertos-pc/lpc_chip_175x_6x/inc" -I"/home/jpatel/Downloads/freertos-pc/lpc_board_nxp_lpcxpresso_1769/inc" -I"/home/jpatel/Downloads/freertos-pc/webserver_freertos/example/inc" -I"/home/jpatel/Downloads/freertos-pc/webserver_freertos/lwip/inc" -I"/home/jpatel/Downloads/freertos-pc/webserver_freertos/lwip/inc/ipv4" -I"/home/jpatel/Downloads/freertos-pc/webserver_freertos/freertos/inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


