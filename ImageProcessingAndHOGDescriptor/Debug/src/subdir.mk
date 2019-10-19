################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/HOG.cpp \
../src/ImageProcessingAndHOGDescriptor.cpp 

OBJS += \
./src/HOG.o \
./src/ImageProcessingAndHOGDescriptor.o 

CPP_DEPS += \
./src/HOG.d \
./src/ImageProcessingAndHOGDescriptor.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include/opencv -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


