//
// Created by diegopicazo on 14/1/24.
//

#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

extern int w;
extern int h;

void frameBuffer(GLFWwindow* window, int width, int height);

#endif //FRAMEBUFFER_H
