cmake_minimum_required(VERSION 3.17)
project(DS_HW1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(DS_HW1
        tests/car_dealership_tests.cpp "Car manager/car_dealership.cpp" "Car manager/library.cpp" "Car Classes/car_best_sells.cpp" "Car Classes/car_points.cpp" "Car Classes/car_sells.cpp" "Car Classes/car_zero_points.cpp")

add_subdirectory("./Tests")
add_subdirectory("./Car Classes")
add_subdirectory("./Car manager")
add_subdirectory("./AVL Tree")
add_subdirectory("./Main and Tests")