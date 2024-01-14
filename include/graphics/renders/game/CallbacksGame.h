//
// Created by diegopicazo on 14/1/24.
//

#ifndef CALLBACKSGAME_H
#define CALLBACKSGAME_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../../../core/features/ScreenMode.h"

void callbackGameFunKey(GLFWwindow* window, int key, int scancode, int action, int mods);

void callbackGameFunScroll(GLFWwindow* window, double xoffset, double yoffset);

void callbackGameFunCursorPos(GLFWwindow* window, double xpos, double ypos);

#endif //CALLBACKSGAME_H
