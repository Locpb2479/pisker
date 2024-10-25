################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middleware/cbuffer.c \
../Middleware/frame.c 

OBJS += \
./Middleware/cbuffer.o \
./Middleware/frame.o 

C_DEPS += \
./Middleware/cbuffer.d \
./Middleware/frame.d 


# Each subdirectory must supply rules for building sources it contributes
Middleware/%.o Middleware/%.su Middleware/%.cyclo: ../Middleware/%.c Middleware/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/HK232/Thuc tap ngoai truon/ITR VN/Project/Pisker/BSP" -I"D:/HK232/Thuc tap ngoai truon/ITR VN/Project/Pisker/Driver" -I"D:/HK232/Thuc tap ngoai truon/ITR VN/Project/Pisker/System" -I"D:/HK232/Thuc tap ngoai truon/ITR VN/Project/Pisker/Middlewares" -I"D:/HK232/Thuc tap ngoai truon/ITR VN/Project/Pisker/Middleware" -I../Middlewares/ST/ARM/DSP/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middleware

clean-Middleware:
	-$(RM) ./Middleware/cbuffer.cyclo ./Middleware/cbuffer.d ./Middleware/cbuffer.o ./Middleware/cbuffer.su ./Middleware/frame.cyclo ./Middleware/frame.d ./Middleware/frame.o ./Middleware/frame.su

.PHONY: clean-Middleware

