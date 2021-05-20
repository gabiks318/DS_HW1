cmake_minimum_required(VERSION 3.17)
project(DS_HW1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(DS_HW1
        "Tests/AVLTreeTest.cpp" "Submission/car_dealership.cpp" "Submission/library.cpp" "Submission/car_best_sells.cpp" "Submission/car_points.cpp" "Submission/car_sells.cpp" "Submission/car_zero_points.cpp")

add_subdirectory("./Tests")
add_subdirectory("./Car Classes")
add_subdirectory("./Car manager")
add_subdirectory("./AVL Tree")
add_subdirectory("./Submission")
add_subdirectory("./Main and Tests")