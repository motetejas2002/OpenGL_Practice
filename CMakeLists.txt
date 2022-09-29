cmake_minimum_required(VERSION 3.22)
project(OpenGL_Learning)

set(CMAKE_CXX_STANDARD 17)

link_directories(/usr/local/lib/)
link_directories(/opt/homebrew/lib/)
include_directories(OpenGL_Learning PUBLIC /usr/local/include)
include_directories(OpenGL_Learning PUBLIC /opt/homebrew/include)
include_directories(OpenGL_Learning PUBLIC include/)

add_executable(OpenGL_Learning src/main.cpp src/special_function.cpp include/special_function.hpp)
target_link_libraries(OpenGL_Learning GLEW glfw)

target_link_libraries(OpenGL_Learning "-framework OpenGL")
target_link_libraries(OpenGL_Learning "-framework Cocoa")
target_link_libraries(OpenGL_Learning "-framework IOKit")
