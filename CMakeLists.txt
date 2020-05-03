cmake_minimum_required(VERSION 3.9)

project(BitsyLabs CXX C)

# Set the C/C++ standards
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 14)

#include_directories(libs)
#add_subdirectory(libs)

if (HARDWARE MATCHES true)
    IF(NOT CMAKE_CROSSCOMPILING)
        message(FATAL_ERROR "Cross compiling only. Please use -DCMAKE_TOOLCHAIN_FILE=/PATH/TO/TOOLCHAIN_FILE .")
    ENDIF(NOT CMAKE_CROSSCOMPILING)

    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)

    # Choose target device here
    set(DEVICE STM32F415RGT6)
    set(PLATFORM_ARCH STM32F4)

    # Set STM32 SoC specific variables
    set(STM32_DEFINES "-DSTM32F4")

    # Choose target mainboard pin configuration here
    add_definitions(-D${PLATFORM_ARCH}})

    # Compiler
    include(cmake/toolchain.cmake)

    # Compiler
    include(cmake/project.cmake)

    # Include additional compilation flags
    include(cmake/warnings.cmake)

    # Include libopencm3
    include(cmake/libopencm3.cmake)

    include_directories(
            ${LIBOPENCM3_DIR}/include)

    add_subdirectory(labs)
else()
    #add_subdirectory(tests)
endif()
