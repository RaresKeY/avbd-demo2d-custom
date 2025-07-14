cmake_minimum_required(VERSION 3.13)
project(avbd_pybind)
find_package(pybind11 REQUIRED)
file(GLOB SRC "../source/*.cpp" "../source/*.h" "avbd_pybind.cpp")
add_library(avbd MODULE ${SRC})
set_target_properties(avbd PROPERTIES
    PREFIX ""
    OUTPUT_NAME "avbd"
)
set_target_properties(avbd PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

