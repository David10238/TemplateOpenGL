cmake_minimum_required(VERSION 3.28)
project(TemplateOpenGL)

# add subdirectories for each dependency
add_subdirectory("thirdparty/glfw-3.4")
add_subdirectory("thirdparty/glad")

set(CMAKE_CXX_STANDARD 26)

add_executable(TemplateOpenGL src/main.cpp
        src/graphics/OpenGLPlatform.cpp
        src/graphics/Shader.cpp
        src/graphics/Triangle.cpp)

target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/") # This is useful to get an ASSETS_PATH in your IDE during development but you should comment this if you compile a release version and uncomment the next line
#target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="./resources/") # Uncomment this line to setup the ASSETS_PATH macro to the final assets directory when you share the game

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_include_directories(${PROJECT_NAME} PUBLIC "thirdparty/glm")
target_include_directories(${PROJECT_NAME} PUBLIC "thirdparty/stb_image")

target_link_libraries(${PROJECT_NAME} PRIVATE glfw glad)