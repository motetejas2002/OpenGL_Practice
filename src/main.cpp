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

    /* Creating window */
    GLFWwindow *window = glfwCreateWindow(800, 600, "Learn OpenGL", NULL, NULL);

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

    /* Frame buffer size callback function */
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    /* The Display loop (The Game Loop)*/
    while (!glfwWindowShouldClose(window)) {
        glfwSwapBuffers(window);
        /* function checks if any events are triggered
         * (like keyboard input or mouse movement events) */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}