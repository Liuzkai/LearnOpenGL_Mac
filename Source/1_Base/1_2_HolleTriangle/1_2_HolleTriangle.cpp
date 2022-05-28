#include <glad.h>
#include <glfw3.h>
#include <iostream>

// vertex shader
const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";

// fragment shader
const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                   "}\n\0";


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

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

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


    // 材质设置的全部流程，这是一个基本过程，要想使用shader，这是基本步骤。
    // 顶点shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    {
        int success;
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\\n" << infoLog << std::endl;
        }
    }
    // 片shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    {
        int success;
        char infoLog[512];
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\\n" << infoLog << std::endl;
        }
    }
    // shader程序
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    {
        int success;
        char infoLog[512];
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if(!success)
        {
            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM_LINK::COMPILATION_FAILED\\n" << infoLog << std::endl;
        }
    }


    // 清除shader以及使用程序
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    //--- shader流程结束  ---



    float vertices[] = {
            0.5f, 0.5f, 0.0f,   // 右上角
            0.5f, -0.5f, 0.0f,  // 右下角
            -0.5f, -0.5f, 0.0f, // 左下角
            -0.5f, 0.5f, 0.0f   // 左上角
    };

    unsigned int indices[] = { // 注意索引从0开始!
            0, 1, 3, // 第一个三角形
            1, 2, 3  // 第二个三角形
    };



    // 配置顶点数组对象 VAO 的完整步骤，如果是多个模型，即有多个VAO重复一下步骤。

    unsigned int VAO;  // Vertex Array Object
    glGenVertexArrays(1, &VAO);

    unsigned int VBO; // vertex buffer objects id
    glGenBuffers(1, &VBO); // 创建一个buffer

    unsigned int EBO; // Element Buffer Object / Index Buffer Object
    glGenBuffers(1, &EBO); // 参数1，buffer个数，参数2，返回缓冲ID

    // 1. 绑定VAO
    glBindVertexArray(VAO);

    // 2. 把顶点数组复制到缓冲中供OpenGL使用
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // 指定buffer类型
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // 写入数据

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // 3. 设置顶点属性指针
    glVertexAttribPointer(0, // 对应顶点shader的layout(location = 0)属性位置
                          3, // 属性大小
                          GL_FLOAT,  // 数据类型
                          GL_FALSE,  // Normalize bool
                          3 * sizeof(float),  // 步长（Stride）
                          (void*)0); // 数据在缓冲中的起始位置的偏移量（Offset）
    glEnableVertexAttribArray(0);

    // 解绑VBO。由于调用了glVertexAttribPointer，将VBO注册为顶点属性绑定的顶点缓冲对象，因此可以安全解绑。
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // VAO激活状态时，EBO 不能解绑！
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    // 解绑VAO。非必要步骤，意味着手动解绑VAO，其实开始绑定其他VAO时，会自动解绑。
    glBindVertexArray(0);

    // --- VAO 的完整步骤结束---


    // 线框渲染模式
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while(!glfwWindowShouldClose(window))
    {
        // 输入
        processInput(window); // 自定义输入控制

        // 渲染指令
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //设定清空颜色
        glClear(GL_COLOR_BUFFER_BIT); //指定清空的buffer

        // 4. 绘制物体
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        // glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // 检查并调用事件，交换缓冲

        glfwSwapBuffers(window); // 双缓存机制
        glfwPollEvents(); // 触发事件
    }

    // 删除缓冲（可选）
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}

