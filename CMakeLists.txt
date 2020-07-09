cmake_minimum_required(VERSION 3.16.3)
project(cl-ray-tracing)

add_definitions(-DPROGRAM_NAME="${CMAKE_PROJECT_NAME}" -DROOT_DIR="${CMAKE_SOURCE_DIR}")

set(CMAKE_BUILD_TYPE "Debug")

set(ROCM_OPENCL "/opt/rocm/opencl/")

find_library(CL OpenCL PATHS "${ROCM_OPENCL}lib/" REQUIRED)

include_directories(include "${ROCM_OPENCL}include/")

add_executable(${CMAKE_PROJECT_NAME} src/main.c
        src/engine.c
        src/util.c)

target_link_libraries(${CMAKE_PROJECT_NAME} GL
        glfw
        GLEW
        ${CL})
