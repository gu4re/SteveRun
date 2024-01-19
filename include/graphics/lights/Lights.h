//
// Created by diegopicazo on 13/1/24.
//

#ifndef LIGHTS_H
#define LIGHTS_H

#include "../shaders/ShadersManager.h"
#include "../models/Models.h"
#include "../shaders/Shaders.h"

#define   NLF 6

inline Light lightG;
inline Light lightF[NLF];
inline Material mluz;

void setLights();

#endif //LIGHTS_H
