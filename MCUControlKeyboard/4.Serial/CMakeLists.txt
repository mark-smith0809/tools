cmake_minimum_required(VERSION 3.10.0)
project(test_serial VERSION 0.1.0 LANGUAGES C CXX)

# 默认使用 Debug 构建类型
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug
        CACHE STRING "Build type" FORCE)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(test_serial
    main.cpp
)

if(MSVC)
    target_compile_options(test_serial PRIVATE /utf-8)
else()
    # GCC/MinGW: Debug 模式显式添加调试信息
    target_compile_options(test_serial PRIVATE
        $<$<CONFIG:Debug>:-g3 -O0>
    )
endif()