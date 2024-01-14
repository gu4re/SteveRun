//
// Created by diegopicazo on 14/1/24.
//

#include "../../../include/core/destroy/Destroy.h"

void destroy(GLFWwindow* window) {
    glfwDestroyWindow(window);
    glfwTerminate();
}