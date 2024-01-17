//
// Created by diegopicazo on 14/1/24.
//

#include "../../../include/graphics/lights/Lights.h"

void setLights(glm::mat4 P, glm::mat4 V) {

    shaders.setLight("ulightG", lightG);
    for (int i = 0; i < NLF; i++) shaders.setLight("ulightF[" + toString(i) + "]", lightF[i]);

}