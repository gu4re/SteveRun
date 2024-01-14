//
// Created by diegopicazo on 14/1/24.
//

#include "../../../include/core/features/FrameBuffer.h"

void frameBuffer([[maybe_unused]] GLFWwindow *window, int width, int height) {

    // Configuracion del Viewport
    glViewport(0, 0, width, height);

    // Actualizacion de w y h
    w = width;
    h = height;

}
