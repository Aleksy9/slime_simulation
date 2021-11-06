cmake_minimum_required(VERSION 3.13.4)

project(slime_simulation_cmake)

# Makes executable
add_executable(${PROJECT_NAME} main.cpp glad.c EBO.cpp shaderClass.cpp VAO.cpp)

# Cmake can find subdirectory
#add_subdirectory(Classes)
#-ldl -lglfw -lm

# allows to include generated libraries using <> instead of "" which requires location
#target_include_directories(${PROJECT_NAME} PUBLIC Classes)

#target_link_directories(${PROJECT_NAME} PRIVATE Classes)

add_library(VBO VBO.cpp)
target_link_libraries(${PROJECT_NAME} VBO -ldl -lglfw)