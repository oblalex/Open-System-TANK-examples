################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include LCD/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
tank-lcd.lss \

FLASH_IMAGE += \
tank-lcd.hex \

EEPROM_IMAGE += \
tank-lcd.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: tank-lcd.elf secondary-outputs

# Tool invocations
tank-lcd.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,tank-lcd.map -mmcu=atmega64 -o "tank-lcd.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

tank-lcd.lss: tank-lcd.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S tank-lcd.elf  >"tank-lcd.lss"
	@echo 'Finished building: $@'
	@echo ' '

tank-lcd.hex: tank-lcd.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -O ihex tank-lcd.elf  "tank-lcd.hex"
	@echo 'Finished building: $@'
	@echo ' '

tank-lcd.eep: tank-lcd.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex tank-lcd.elf  "tank-lcd.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: tank-lcd.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=berkeley -t tank-lcd.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(ASM_DEPS)$(EEPROM_IMAGE)$(FLASH_IMAGE)$(ELFS)$(LSS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS) tank-lcd.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
