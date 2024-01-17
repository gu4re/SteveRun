//
// Created by diegopicazo on 13/1/24.
//

#ifndef INIT_H
#define INIT_H

#include <tuple>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <freetype/freetype.h>
#include <iostream>
#include "../../../include/graphics/shaders/Shaders.h"
#include "../../../include/graphics/textures/TexturesResources.h"
#include "../../../include/graphics/textures/Textures.h"
#include <ft2build.h>
#include FT_FREETYPE_H
#include "../../../include/graphics/models/Models.h"
#include "../../../include/graphics/lights/Lights.h"
#include "../features/ToggleSound.h"
#include <AL/al.h>
#include <AL/alc.h>
#include <sndfile.h>

std::tuple<GLFWwindow *, FT_Library, FT_Face>init();

#endif //INIT_H
