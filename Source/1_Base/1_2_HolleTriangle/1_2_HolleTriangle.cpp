#include <glad.h>
#include <glfw3.h>
#include <iostream>

float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main()
{
    glfwInit();

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if(window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    while(!glfwWindowShouldClose(window))
    {
        // 输入
        processInput(window); // 自定义输入控制
        // 渲染指令

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //设定清空颜色
        glClear(GL_COLOR_BUFFER_BIT); //指定清空的buffer

        // 检查并调用事件，交换缓冲
        glfwPollEvents(); // 触发事件
        glfwSwapBuffers(window); // 双缓存机制

    }

    glfwTerminate();
    return 0;
}

