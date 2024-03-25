cmake_minimum_required(VERSION 3.27)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR ARM)
set(CMAKE_SYSTEM_VERSION 1)

set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
set(CMAKE_OBJDUMP arm-none-eabi-objdump)
set(SIZE arm-none-eabi-size)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

project(hello_world_arm C CXX ASM)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_C_STANDARD 17)

add_compile_options(-mcpu=cortex-m0plus -mthumb)
add_compile_options(-fomit-frame-pointer -Wall)

add_link_options(-Wl,--print-memory-usage,-Map=${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map)
add_link_options(-T${CMAKE_SOURCE_DIR}/stm32.ld)
add_link_options(--specs=nosys.specs -nostdlib)

add_executable(hello_world_arm.elf
        main.c
        startup.s
        stm32.ld)
