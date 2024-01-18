//
// Created by diegopicazo on 17/1/24.
//

#ifndef TOGGLESOUND_H
#define TOGGLESOUND_H

#include <AL/al.h>
#include <AL/alc.h>
#include <sndfile.h>
#include <thread>

extern bool isSoundActive;

void toggleSound(ALuint SoundSource);

#endif //TOGGLESOUND_H
