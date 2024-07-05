cmake_minimum_required(VERSION 3.28)
project(TemplateOpenGL)

# add subdirectories for each dependency
add_subdirectory("thirdparty/glfw-3.4")
add_subdirectory("thirdparty/glad")

set(CMAKE_CXX_STANDARD 26)

add_executable(TemplateOpenGL src/main.cpp
        src/graphics/OpenGLPlatform.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_include_directories(${PROJECT_NAME} PUBLIC "thirdparty/glm")
target_link_libraries(${PROJECT_NAME} PRIVATE glfw glad)