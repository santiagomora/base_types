cmake_minimum_required(VERSION 3.10)
project(core_types)
set(CMAKE_CXX_STANDARD 20)
set(PYBIND11_PYTHON_VERSION 3.12)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -fPIC -O2 -march=native -flto=auto")
set(pybind11_DIR /home/smora/sgs/dev/python/core/venv/lib/python3.12/site-packages/pybind11/share/cmake/pybind11)
find_package(pybind11 REQUIRED)
add_library(${PROJECT_NAME} SHARED 
    ./src/init.cpp
    ./src/compare.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE pybind11::module)
target_include_directories(${PROJECT_NAME} PRIVATE ./include)
target_compile_definitions(${PROJECT_NAME} PRIVATE VERSION_INFO=${EXAMPLE_VERSION_INFO})
target_include_directories(${PROJECT_NAME} PRIVATE ${PYBIND11_INCLUDE_DIRS})
