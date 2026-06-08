cmake_minimum_required(VERSION 3.10.0)
project(test_sendinput VERSION 0.1.0 LANGUAGES C CXX)

add_executable(test_sendinput
    main.cpp
    SimulateKeyBoard.cpp
    Test.cpp
)

if(MSVC)
    target_compile_options(test_sendinput PRIVATE /utf-8)
endif()