//
// Created by diegopicazo on 13/1/24.
//

#ifndef LIGHTS_H
#define LIGHTS_H

#include "../shaders/ShadersManager.h"

#define   NLD 1
#define   NLP 1
#define   NLF 2

inline Light lightG;
inline Light lightD[NLD];
inline Light lightP[NLP];
inline Light lightF[NLF];
inline Material mluz;

#endif //LIGHTS_H
