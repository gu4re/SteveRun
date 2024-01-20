//
// Created by diegopicazo on 14/1/24.
//

#ifndef RENDERGAME_H
#define RENDERGAME_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../../shaders/Shaders.h"
#include "../../models/Models.h"
#include "../../textures/Textures.h"
#include "../enemy/RenderEnemy.h"
#include <set>
#include "../../lights/Lights.h"
#include <random>
#include <AL/al.h>
#include <AL/alc.h>
#include "../../../core/features/ToggleSound.h"

extern void callbackGameFunKey(GLFWwindow* window, int key, int scancode, int action, int mods);
extern void callbackGameFunScroll(GLFWwindow* window, double xoffset, double yoffset);
extern void callbackGameFunCursorPos(GLFWwindow* window, double xpos, double ypos);

extern bool renderedEnemy[8];

void renderGame(GLFWwindow *window, ALuint SoundSource);

#endif //RENDERGAME_H
