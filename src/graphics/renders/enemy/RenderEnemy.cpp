//
// Created by diegopicazo on 14/1/24.
//

#include "../../../../include/graphics/renders/enemy/RenderEnemy.h"

void renderEnemy(float angle, int randNum, glm::mat4 P, glm::mat4 V) {
    glm::mat4 S;
    if(randNum <= 5) {
        glm::mat4 T;
        glm::mat4 R = glm::rotate(I, glm::radians(angle), glm::vec3(1, 0, 0));
        if(randNum == 3) {
            S = glm::scale(I, glm::vec3(0.42));
            T = glm::translate(I, glm::vec3(0, 9.49, 0));
        } else {
            S = glm::scale(I, glm::vec3(0.85));
            T = glm::translate(I, glm::vec3(0, 4.68, 0));
        }
        drawObjectTex(modelsRandomArray[randNum], texturesRandomArray[randNum], P, V, R * S * T);
    } else {
        S = glm::scale(I, glm::vec3(0.40));
        glm::mat4 T = glm::translate(I, glm::vec3(0, 11, 0));
        glm::mat4 R = glm::rotate(I, glm::radians(angle), glm::vec3(1, 0, 0));
        drawObjectTex(modelCube, texturesRandomArray[randNum], P, V, R * S * T);
    }

}
