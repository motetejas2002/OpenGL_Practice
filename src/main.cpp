/**
 * Programmer: Mr. Tejas Dattatray Mote
 * Date of Creation: 23 September 2022
 */
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "special_functions.h"

int main() {
    /* Initializing the glfw3 library */
    if (!glfwInit()) {
        std::cout << "glfw3 can't be initialized" << std::endl;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    /* Creating window */
    GLFWwindow *window = glfwCreateWindow(800, 600, "Learn OpenGL", nullptr, nullptr);

    /* Verification of created window */
    if (window == nullptr) {
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }

    /* Creating valid OpenGL context */
    glfwMakeContextCurrent(window);

    /* Initialize the glad after valid OpenGL */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize glad" << std::endl;
        return -1;
    }

    /* Setting initial view port */
    glViewport(0, 0, 800, 600);

    float vertices[9] = {
            -0.5f, -0.5f, 0.0f,
             0.0f,  0.5f, 0.0f,
             0.5f,  0.5f, 0.0f
    };

    /* Creating vertex buffer */
    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    /* Vertex shader source code */
    const char* vertexShaderSource = "#version 330 core\n"
                                     "layout (location = 0) in vec3 aPos;\n"
                                     "void main()\n"
                                     "{\n"
                                     "  gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                     "}\0";

    /* Creating vertex shader */
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);

    /* Compiling vertex shader */
    glCompileShader(vertexShader);

    /* checking shader compiled successfully or not */
    int success_vertex;
    char infoLog_vertex[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success_vertex);

    if (!success_vertex) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog_vertex);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED" << std::endl << infoLog_vertex << std::endl;
    }

    /* Source code for fragment shader */
    const char* fragmentShaderSource = "#version 330 core\n"
                                       "out vec4 FragColor;\n"
                                       "\n"
                                       "void main(){\n"
                                       "    FragColor = vec4(1.0f, 0.5f, 0.5f, 1.0f);\n"
                                       "}\0";

    /* Creating Fragment shader */
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);

    /* Compile fragment shader */
    glCompileShader(vertexShader);

    /* checking shader compiled successfully or not */
    int success_fragment;
    char infoLog_fragment[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success_fragment);

    if (!success_vertex) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog_fragment);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED" << std::endl << infoLog_fragment << std::endl;
    }

    /* shader program */
    unsigned int shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glValidateProgram(shaderProgram);

    int success_link;
    char infoLog_link[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success_link);

    if(!success_link) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog_link);
        std::cout << "ERROR::SHADER::LINK::FAILED" << std::endl << infoLog_link << std::endl;
    }

    glUseProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    /* The Display loop (The Game Loop)*/
    while (!glfwWindowShouldClose(window)) {
        glfwSwapBuffers(window);

        //glUseProgram(shaderProgram);
        glBindVertexArray(buffer);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* function checks if any events are triggered
         * (like keyboard input or mouse movement events) */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}