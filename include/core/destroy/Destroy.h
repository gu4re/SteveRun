//
// Created by diegopicazo on 14/1/24.
//

#ifndef DESTROY_H
#define DESTROY_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <AL/al.h>
#include <AL/alc.h>
#include <sndfile.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <thread>

void destroy(GLFWwindow* window, FT_Library FTLibrary, FT_Face FTFace, ALCdevice* SoundDevice, ALCcontext* SoundContext, ALuint SoundSource, ALuint SoundBuffer);

#endif //DESTROY_H
