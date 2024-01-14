#include "../include/core/init/Init.h"
#include "../include/core/features/FrameBuffer.h"
#include "../include/graphics/renders/menu/RenderMenu.h"
#include "../include/graphics/renders/game/RenderGame.h"
#include "../include/core/destroy/Destroy.h"
#include "../include/core/variables/Variables.h"

int main() {

    // Inicializa lo necesario
    auto [window, ft, face] = init();

    // Callbacks globales para todas las capas de renderizado
    glfwSetFramebufferSizeCallback(window, frameBuffer);

    while (!glfwWindowShouldClose(window)) {
        if (inMainMenu) {
            renderMenu(window);
        } else {
            renderGame(window);
        }
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Destroy everything initialized before
    destroy(window);

    return 0;
}