cmake_minimum_required(VERSION 3.10)
project(wrapper)
set(CMAKE_CXX_STANDARD 20)
set(PYTHON_VERSION 3.12)
set(PYBIND11_PYTHON_VERSION ${PYTHON_VERSION})
set(PYTHON_VENV_PATH $ENV{VIRTUAL_ENV})
set(SGS_INCLUDE_PATH ${PYTHON_VENV_PATH}/include/python${PYTHON_VERSION}/sgs)
set(SGS_LIB_PATH ${PYTHON_VENV_PATH}/lib/python${PYTHON_VERSION}/sgs)
set(pybind11_DIR ${PYTHON_VENV_PATH}/lib/python${PYBIND11_PYTHON_VERSION}/site-packages/pybind11/share/cmake/pybind11)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -fPIC -march=native -flto=auto -D_FORTIFY_SOURCE=0")
find_package(pybind11 REQUIRED)
pybind11_add_module(${PROJECT_NAME}
    wrapper.cpp
)
target_link_directories(${PROJECT_NAME} PRIVATE ${SGS_LIB_PATH})
target_link_directories(${PROJECT_NAME} PRIVATE $ENV{BUILD_TMP_DATA_LIB_DIR})

target_include_directories(${PROJECT_NAME} PRIVATE ${SGS_INCLUDE_PATH})
target_include_directories(${PROJECT_NAME} PRIVATE ../lib/include)
target_compile_definitions(${PROJECT_NAME} PRIVATE VERSION_INFO=${EXAMPLE_VERSION_INFO})
target_include_directories(${PROJECT_NAME} PRIVATE ${PYBIND11_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} PRIVATE core_types)
