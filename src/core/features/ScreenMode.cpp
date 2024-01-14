//
// Created by diegopicazo on 14/1/24.
//

#include "../../../include/core/features/ScreenMode.h"

void screenMode(GLFWwindow *window) {
    // Gets the current monitor where is running the game
    GLFWmonitor *primaryMonitor = glfwGetPrimaryMonitor();
    int xpos, ypos;
    glfwGetWindowPos(window, &xpos, &ypos);
    // Gets the video mode to obtain screen specs
    const GLFWvidmode *videoMode = glfwGetVideoMode(primaryMonitor);
    if (fullscreen_mode) {
        glfwSetWindowMonitor(window, primaryMonitor, 0, 0,
                             videoMode->width, videoMode->height, videoMode->refreshRate);
    } else {
        glfwSetWindowMonitor(window, nullptr, (videoMode->width / 2) - 700,
                             (videoMode->height / 2) - 700, 700, 700,
                             videoMode->refreshRate);
    }
}
