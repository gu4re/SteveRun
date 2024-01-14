//
// Created by diegopicazo on 14/1/24.
//

#include "../../../../include/graphics/renders/enemy/RenderEnemy.h"

void renderEnemy(float angle, glm::mat4 P, glm::mat4 V) {
    glm::mat4 S = glm::scale(I, glm::vec3(0.30));
    glm::mat4 T = glm::translate(I, glm::vec3(0, 14.42, 0));
    glm::mat4 R = glm::rotate(I, glm::radians(angle), glm::vec3(1, 0, 0));

    drawObjectTex(modelCube, texturesStoneBlock, P, V, R * S * T);
}
