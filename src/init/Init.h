//
// Created by diegopicazo on 13/1/24.
//

#ifndef INIT_H
#define INIT_H

#include <tuple>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <freetype/freetype.h>

std::tuple<GLFWwindow *, FT_Library, FT_Face>init();

#endif //INIT_H
