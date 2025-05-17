cmake_minimum_required(VERSION 3.14)
project(DataAnalyticsApp)

set(CMAKE_CXX_STANDARD 20)

# CLI11 con FetchContent
include(FetchContent)
FetchContent_Declare(
    cli11_proj
    GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
    GIT_TAG v2.3.2
)
FetchContent_MakeAvailable(cli11_proj)

add_executable(main main.cpp)

# 👉 Incluye Barkeep localmente (ajusta la ruta si no está en ~/barkeep)
target_include_directories(main PRIVATE /home/jgram/barkeep)

# Vincula CLI11
target_link_libraries(main PRIVATE CLI11::CLI11)
