//
// Created by diegopicazo on 14/1/24.
//

#include "../../../../include/graphics/renders/game/CallbacksGame.h"
#include "../../../../include/core/variables/Variables.h"

void callbackGameFunKey(GLFWwindow *window, int key, [[maybe_unused]] int scancode, int action,
                [[maybe_unused]] int mods) {

    switch (key) {
        case GLFW_KEY_UP:
            rotP += 5.0f;
            //Imprime las coordenadas del cubo
            //std::cout << "Tecla de flecha arriba - Coordenadas del cubo: (" << cubeX << ", " << cubeY << ", " << cubeZ << ")" << std::endl;
            break;
        case GLFW_KEY_R:
            if (action == GLFW_PRESS) {
                gameRunning = false;
                reset();
            }
            break;
        case GLFW_KEY_SPACE:
            if (action == GLFW_PRESS) {
                if (!gameRunning) {
                    reset();
                }
                isJumping = true;
                gameRunning = true;
                jump = 15.0f;
                //std::cout << "Tecla de salto Coordenadas del cubo: (" << cubeX << ", " << cubeY << ", " << cubeZ << ")" << std::endl;
            } else {
                jump = 0.0f;
                isJumping = false;
            }
            break;
        case GLFW_KEY_F:
            if (action == GLFW_PRESS) {
                fullscreen_mode ? fullscreen_mode = false : fullscreen_mode = true;
                screenMode(window);
            }
            break;
        case GLFW_KEY_M:
            if (action == GLFW_PRESS) {
                isSoundActive ? isSoundActive = false : isSoundActive = true;
            }
            break;
        case GLFW_KEY_ESCAPE:
            if (action == GLFW_PRESS) {
                inMainMenu = true;
                gameRunning = false;
            }
            break;
        default:
            break;
    }

}

void callbackGameFunScroll([[maybe_unused]] GLFWwindow *window, [[maybe_unused]] double xoffset,
                   double yoffset) {

    if (yoffset > 0) fovy -= fovy > 10.0f ? 5.0f : 0.0f;
    if (yoffset < 0) fovy += fovy < 90.0f ? 5.0f : 0.0f;

}

void callbackGameFunCursorPos(GLFWwindow *window, double xpos, double ypos) {

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) return;

    float limY = 89.0;
    alphaX = static_cast<float>(90.0 * (2.0 * xpos / static_cast<float>(w) - 1.0));
    alphaY = static_cast<float>(90.0 * (1.0 - 2.0 * ypos / (float) h));
    if (alphaY < -limY) alphaY = -limY;
    if (alphaY > limY) alphaY = limY;

}
