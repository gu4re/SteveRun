#include "../include/core/init/Init.h"
#include "../include/core/features/FrameBuffer.h"
#include "../include/graphics/renders/menu/RenderMenu.h"
#include "../include/graphics/renders/game/RenderGame.h"
#include "../include/core/destroy/Destroy.h"
#include "../include/core/variables/Variables.h"

int main() {

    // Inicializa lo necesario
    auto [window, FTLibrary, FTFace, SoundDevice, SoundContext, SoundSource, SoundBuffer] = init();

    // Callbacks globales para todas las capas de renderizado
    glfwSetFramebufferSizeCallback(window, frameBuffer);

    while (!glfwWindowShouldClose(window) && isAppActive) {
        if (inMainMenu) {
            renderMenu(window, SoundSource);
        } else {
            renderGame(window, SoundSource);
        }
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    // Llama a tu función destroy con los parámetros necesarios
    destroy(window, FTLibrary, FTFace, SoundDevice, SoundContext, SoundSource, SoundBuffer);

    return 0;
}