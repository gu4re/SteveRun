//
// Created by diegopicazo on 14/1/24.
//

#include "../../../include/graphics/lights/Lights.h"

void setLights(glm::mat4 P, glm::mat4 V) {

    shaders.setLight("ulightG", lightG);
    for (int i = 0; i < NLD; i++) shaders.setLight("ulightD[" + toString(i) + "]", lightD[i]);
    for (int i = 0; i < NLP; i++) shaders.setLight("ulightP[" + toString(i) + "]", lightP[i]);
    for (int i = 0; i < NLF; i++) shaders.setLight("ulightF[" + toString(i) + "]", lightF[i]);

    for (auto &i: lightP) {
        glm::mat4 M = glm::translate(I, i.position) * glm::scale(I, glm::vec3(0.1));
        drawObjectMat(modelSphere, mluz, P, V, M);
    }

    for (auto &i: lightF) {
        glm::mat4 M = glm::translate(I, i.position) * glm::scale(I, glm::vec3(0.025));
        drawObjectMat(modelSphere, mluz, P, V, M);
    }

}