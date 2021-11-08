

add_library(VBO VBO.cpp)
target_link_libraries(${PROJECT_NAME} VBO -ldl -lglfw)

add_library(VAO VAO.cpp)
target_link_libraries(${PROJECT_NAME} VAO)

add_library(EBO EBO.cpp)
target_link_libraries(${PROJECT_NAME} EBO)

add_library(shaderClass shaderClass.cpp)
target_link_libraries(${PROJECT_NAME} shaderClass)