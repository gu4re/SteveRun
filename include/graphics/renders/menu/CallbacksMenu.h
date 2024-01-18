//
// Created by diegopicazo on 14/1/24.
//

#ifndef CALLBACKSMENU_H
#define CALLBACKSMENU_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../../../core/features/ScreenMode.h"
#include "../../../core/features/ToggleSound.h"

void callbackMenuFunKey(GLFWwindow* window, int key, [[maybe_unused]] int scancode, int action,
                [[maybe_unused]] int mods);

#endif //CALLBACKSMENU_H
