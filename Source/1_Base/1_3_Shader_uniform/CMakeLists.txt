cmake_minimum_required(VERSION 3.0.0)
project(1_3_Shader_uniform)

# 使用 C++ 11 标准
set(CMAKE_CXX_STANDARD 11)

# 添加头文件
set(GLEW_H /usr/local/Cellar/glew/2.2.0_1/include/GL)
set(GLFW_H /usr/local/Cellar/glfw/3.3.7/include/GLFW)
set(GLAD_H /usr/local/Cellar/glad)
set(KH_H /usr/local/Cellar/KHR)
include_directories(${GLEW_H} ${GLFW_H} ${GLAD_H} ${KH_H})
include_directories(.)

# 添加目标链接
set(GLFW_LINK /usr/local/lib/libglfw.3.dylib)
link_libraries(${GLFW_LINK})

# 执行编译命令
set(SOURCES ../../../include/glad.c 1_3_Shader.cpp)
add_executable(1_3_Shader_uniform ${SOURCES})


# 链接系统的 OpenGL 框架
if (APPLE)
    target_link_libraries(1_3_Shader_uniform "-framework OpenGL")
endif()

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)


