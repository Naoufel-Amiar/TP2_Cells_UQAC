cmake_minimum_required(VERSION 3.10)

project(TP2_Cells_UQAC)

# ==========================================
# CONFIGURATION C++
# ==========================================

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ==========================================
# FICHIERS SOURCES
# ==========================================

set(SOURCES
    main.cpp
    source/ColorCell.cpp
    source/ChromoCell.cpp
    source/TransTerminal.cpp
)

# ==========================================
# CREATION DE L'EXECUTABLE
# ==========================================

add_executable(TP2_Cells ${SOURCES})

# ==========================================
# FICHIERS D'EN-TETE
# ==========================================

target_include_directories(TP2_Cells PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)