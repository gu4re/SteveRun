//
// Created by diegopicazo on 14/1/24.
//

#include "../../../../include/graphics/renders/menu/CallbacksMenu.h"
#include "../../../../include/core/variables/Variables.h"

void callbackMenuFunKey(GLFWwindow *window, int key, [[maybe_unused]] int scancode, int action,
                [[maybe_unused]] int mods) {
    switch (key) {
        case GLFW_KEY_ENTER:
            if (action == GLFW_PRESS) {
                inMainMenu = false;
                reset();
            }
            break;
        case GLFW_KEY_F:
            if (action == GLFW_PRESS) {
                fullscreen_mode ? fullscreen_mode = false : fullscreen_mode = true;
                screenMode(window);
            }
            break;
        case GLFW_KEY_ESCAPE:
            if (action == GLFW_PRESS) {
                isAppActive = false;
            }
            break;
        case GLFW_KEY_M:
            if (action == GLFW_PRESS) {
                isSoundActive ? isSoundActive = false : isSoundActive = true;
            }
            break;
        default:
            break;
    }
}
