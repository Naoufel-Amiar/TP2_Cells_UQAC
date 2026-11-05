
cmake_minimum_required(VERSION 3.10)

project(TP2_Cells_UQAC LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(TP2_Cells
    main.cpp
    source/ColorCell.cpp
    source/ChromoCell.cpp
    source/TransTerminal.cpp
)

target_include_directories(TP2_Cells PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(
        TP2_Cells PRIVATE
        -Wall -Wextra -Wpedantic
    )
endif()
