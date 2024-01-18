//
// Created by diegopicazo on 14/1/24.
//

#include "../../../include/core/destroy/Destroy.h"
#include "../../../include/core/features/ToggleSound.h"

void destroy(GLFWwindow* window, FT_Library FTLibrary, FT_Face FTFace, ALCdevice* SoundDevice, ALCcontext* SoundContext, ALuint SoundSource, ALuint SoundBuffer) {
    isSoundActive = false;
    toggleSound(SoundSource);
    glfwDestroyWindow(window);
    glfwTerminate();
    // Limpieza de recursos de OpenAL
    alDeleteSources(1, &SoundSource);
    alDeleteBuffers(1, &SoundBuffer);
    alcMakeContextCurrent(nullptr);
    alcDestroyContext(SoundContext);
    alcCloseDevice(SoundDevice);
}