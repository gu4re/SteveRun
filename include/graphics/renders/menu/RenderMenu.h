//
// Created by diegopicazo on 14/1/24.
//

#ifndef RENDERMENU_H
#define RENDERMENU_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../../shaders/Shaders.h"
#include "../../models/Models.h"
#include "../../textures/Textures.h"
#include "../../lights/Lights.h"
#include <AL/al.h>
#include <AL/alc.h>
#include <sndfile.h>
#include "../../../core/features/ToggleSound.h"

extern void callbackMenuFunKey(GLFWwindow* window, int key, [[maybe_unused]] int scancode, int action,
                               [[maybe_unused]] int mods);

void renderMenu(GLFWwindow* window, ALCdevice* SoundDevice, ALCcontext* SoundContext, ALuint SoundSource, ALuint SoundBuffer);

#endif //RENDERMENU_H
