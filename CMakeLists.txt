cmake_minimum_required(VERSION 3.28)
project(TemplateOpenGL)

# add subdirectories for each dependency
add_subdirectory("thirdparty/glfw-3.4")
add_subdirectory("thirdparty/glad")

set(CMAKE_CXX_STANDARD 26)

# find all files
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(TemplateOpenGL "${MY_SOURCES}")

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_include_directories(${PROJECT_NAME} PUBLIC "thirdparty/glm")
target_link_libraries(${PROJECT_NAME} PRIVATE glfw glad)