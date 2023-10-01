# ModelLibrary/CMakeLists.txt

#define minimum CMake version
cmake_minimum_required( VERSION 2.8.11 )

PROJECT( AlgorithmPresenter )

#include CTest to allow test creation
include(CTest)

#include relevant CMakeLists files
include(Src/CMakeLists.txt)
include(Inc/CMakeLists.txt)
include(Support/CMakeLists.txt)

# Lingk openGL
find_package(OpenGL REQUIRED)
message(STATUS "Found OpenGL in ${OpenGL_INCLUDE_DIR}")

add_subdirectory(glfw)
add_subdirectory(glm)
add_subdirectory(freetype)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Inc/helpers/RootDir.h.in ${CMAKE_CURRENT_SOURCE_DIR}/Inc/helpers/RootDir.h)
include_directories(${CMAKE_BINARY_DIR}/Resources)

add_library(gladLib ${CMAKE_CURRENT_SOURCE_DIR}/glad/glad.c ${CMAKE_CURRENT_SOURCE_DIR}/glad/glad/glad.h)
target_include_directories (gladLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glad)
		 
#define minimum C++ version
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#include everything from current directory
set( CMAKE_INCLUDE_CURRENT_DIR ON )

# Make an executable
add_executable(AlgorithmPresenter MACOSX_BUNDLE 
main.cpp
${main_includes}
${main_sources}
${support_sources})

target_link_libraries( AlgorithmPresenter opengl32)
target_link_libraries( AlgorithmPresenter gladLib)
target_link_libraries( AlgorithmPresenter glfw)
target_link_libraries( AlgorithmPresenter glm)
target_link_libraries( AlgorithmPresenter freetype)

target_include_directories (AlgorithmPresenter PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glfw-/include)
target_include_directories (AlgorithmPresenter PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glad)
target_include_directories (AlgorithmPresenter PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glm/glm)
target_include_directories (AlgorithmPresenter PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/freetype/include)
target_include_directories (AlgorithmPresenter PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Inc)
target_include_directories (AlgorithmPresenter PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Support)







