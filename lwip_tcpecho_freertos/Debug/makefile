################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include lwip/src/netif/subdir.mk
-include lwip/src/core/ipv4/subdir.mk
-include lwip/src/core/subdir.mk
-include lwip/src/arch/subdir.mk
-include lwip/src/api/subdir.mk
-include freertos/src/subdir.mk
-include example/src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: lwip_tcpecho_freertos.axf

# Tool invocations
lwip_tcpecho_freertos.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"/home/jpatel/Downloads/freertos-pc/lpc_chip_175x_6x/Debug" -L"/home/jpatel/Downloads/freertos-pc/lpc_board_nxp_lpcxpresso_1769/Debug" -Xlinker -Map="lwip_tcpecho_freertos.map" -Xlinker --gc-sections -mcpu=cortex-m3 -mthumb -T "lwip_tcpecho_freertos_Debug.ld" -o "lwip_tcpecho_freertos.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) lwip_tcpecho_freertos.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "lwip_tcpecho_freertos.axf"; # arm-none-eabi-objcopy -v -O binary "lwip_tcpecho_freertos.axf" "lwip_tcpecho_freertos.bin" ; # checksum -p LPC1769 -d "lwip_tcpecho_freertos.bin";
	-@echo ' '

.PHONY: all clean dependents post-build

-include ../makefile.targets
