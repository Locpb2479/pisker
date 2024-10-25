################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/fatfs_sd.c \
../Middlewares/frame.c 

OBJS += \
./Middlewares/fatfs_sd.o \
./Middlewares/frame.o 

C_DEPS += \
./Middlewares/fatfs_sd.d \
./Middlewares/frame.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/%.o Middlewares/%.su Middlewares/%.cyclo: ../Middlewares/%.c Middlewares/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../FATFS/Target -I../FATFS/App -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FatFs/src -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/HK232/Thuc tap ngoai truon/ITR VN/Project/Pisker/BSP" -I"D:/HK232/Thuc tap ngoai truon/ITR VN/Project/Pisker/Driver" -I"D:/HK232/Thuc tap ngoai truon/ITR VN/Project/Pisker/System" -I"D:/HK232/Thuc tap ngoai truon/ITR VN/Project/Pisker/Middlewares" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares

clean-Middlewares:
	-$(RM) ./Middlewares/fatfs_sd.cyclo ./Middlewares/fatfs_sd.d ./Middlewares/fatfs_sd.o ./Middlewares/fatfs_sd.su ./Middlewares/frame.cyclo ./Middlewares/frame.d ./Middlewares/frame.o ./Middlewares/frame.su

.PHONY: clean-Middlewares

