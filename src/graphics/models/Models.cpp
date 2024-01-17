//
// Created by diegopicazo on 14/1/24.
//

#include "../../../include/graphics/models/Models.h"

void drawObjectMat(ModelsManager &model, Material &material, glm::mat4 P, glm::mat4 V, glm::mat4 M) {

    shaders.setMat4("uN", glm::transpose(glm::inverse(M)));
    shaders.setMat4("uM", M);
    shaders.setMat4("uPVM", P * V * M);
    shaders.setBool("uWithMaterials", true);
    shaders.setMaterial("umaterial", material);
    model.renderModel(GL_FILL);

}

void drawObjectTex(ModelsManager &model, Textures &textures, glm::mat4 P, glm::mat4 V, glm::mat4 M) {

    shaders.setMat4("uN", glm::transpose(glm::inverse(M)));
    shaders.setMat4("uM", M);
    shaders.setMat4("uPVM", P * V * M);
    shaders.setBool("uWithMaterials", false);
    shaders.setTextures("utextures", textures);
    if (textures.normal != 0) shaders.setBool("uWithNormals", true);
    else shaders.setBool("uWithNormals", false);
    model.renderModel(GL_FILL);

}

void drawWoodLog(Textures texturesLogSide, Textures texturesLogTop, glm::mat4 P, glm::mat4 V, glm::mat4 M) {
    // Oak Log 1
    glm::mat4 oakLogT = glm::translate(I, glm::vec3(0, 2, -9));
    glm::mat4 oakLogS = glm::scale(I, glm::vec3(0.5));
    glm::mat4 oakLogRotate = glm::rotate(I, glm::radians(90.0f), glm::vec3(1, 0, 0));
    drawObjectTex(modelPlane, texturesLogSide, P, V, M * oakLogRotate * oakLogS * oakLogT);
    glm::mat4 oakLogT2 = glm::translate(I, glm::vec3(0, 4, -9));
    glm::mat4 oakLogS2 = glm::scale(I, glm::vec3(0.5));
    glm::mat4 oakLogRotate2 = glm::rotate(I, glm::radians(90.0f), glm::vec3(1, 0, 0));
    drawObjectTex(modelPlane, texturesLogSide, P, V, M * oakLogRotate2 * oakLogS2 * oakLogT2);
    glm::mat4 oakLogT3 = glm::translate(I, glm::vec3(0, 8, 3));
    glm::mat4 oakLogS3 = glm::scale(I, glm::vec3(0.5));
    glm::mat4 oakLogRotate3 = glm::rotate(I, glm::radians(0.0f), glm::vec3(1, 0, 0));
    drawObjectTex(modelPlane, texturesLogTop, P, V, M * oakLogRotate3 * oakLogS3 * oakLogT3);
    glm::mat4 oakLogT4 = glm::translate(I, glm::vec3(0, 10, 3));
    glm::mat4 oakLogS4 = glm::scale(I, glm::vec3(0.5));
    glm::mat4 oakLogRotate4 = glm::rotate(I, glm::radians(0.0f), glm::vec3(1, 0, 0));
    drawObjectTex(modelPlane, texturesLogTop, P, V, M * oakLogRotate4 * oakLogS4 * oakLogT4);
    glm::mat4 oakLogT5 = glm::translate(I, glm::vec3(-3, 1, -9));
    glm::mat4 oakLogS5 = glm::scale(I, glm::vec3(0.5));
    glm::mat4 oakLogRotate5 = glm::rotate(I, glm::radians(90.0f), glm::vec3(1, 0, 0));
    glm::mat4 oakLogRotate6 = glm::rotate(I, glm::radians(90.0f), glm::vec3(0, 1, 0));
    drawObjectTex(modelPlane, texturesLogSide, P, V, M * oakLogRotate6 * oakLogRotate5 * oakLogS5 * oakLogT5);
    glm::mat4 oakLogT6 = glm::translate(I, glm::vec3(-3, -1, -9));
    glm::mat4 oakLogS6 = glm::scale(I, glm::vec3(0.5));
    glm::mat4 oakLogRotate7 = glm::rotate(I, glm::radians(90.0f), glm::vec3(1, 0, 0));
    glm::mat4 oakLogRotate8 = glm::rotate(I, glm::radians(90.0f), glm::vec3(0, 1, 0));
    drawObjectTex(modelPlane, texturesLogSide, P, V, M * oakLogRotate8 * oakLogRotate7 * oakLogS6 * oakLogT6);
}

void drawWoodLeaves(Textures texturesLeaves, glm::mat4 P, glm::mat4 V, glm::mat4 M) {
    glm::mat4 oakLeavesT = glm::translate(I, glm::vec3(0.0, 2.5, -6.5));
    glm::mat4 oakLeavesS = glm::scale(I, glm::vec3(0.5));
    glm::mat4 oakLeavesR = glm::rotate(I, glm::radians(90.0f), glm::vec3(1.0, 0.0, 0.0));
    drawObjectTex(modelCube, texturesLeaves, P, V, M * oakLeavesR * oakLeavesT * oakLeavesS);
}

void drawBirchTree(glm::mat4 P, glm::mat4 V, glm::mat4 M) {
    // Logs
    drawWoodLog(texturesBirchLogSide, texturesBirchLogTop, P, V, M * I);
    drawWoodLog(texturesBirchLogSide, texturesBirchLogTop, P, V, M * glm::translate(I, glm::vec3(0.0, 1.0, 0.0)));
    drawWoodLog(texturesBirchLogSide, texturesBirchLogTop, P, V, M * glm::translate(I, glm::vec3(0.0, 2.0, 0.0)));
    drawWoodLog(texturesBirchLogSide, texturesBirchLogTop, P, V, M * glm::translate(I, glm::vec3(0.0, 3.0, 0.0)));
    // Zero floor Circle
    drawWoodLeaves(texturesBirchLeaves, P, V, M * I);
    drawWoodLeaves(texturesBirchLeaves, P, V, M * glm::translate(I, glm::vec3(1.0, 0.0, 0.0)));
    drawWoodLeaves(texturesBirchLeaves, P, V, M * glm::translate(I, glm::vec3(-1.0, 0.0, 0.0)));
    drawWoodLeaves(texturesBirchLeaves, P, V, M * glm::translate(I, glm::vec3(-1.0, 0.0, -1.0)));
    drawWoodLeaves(texturesBirchLeaves, P, V, M * glm::translate(I, glm::vec3(1.0, 0.0, -1.0)));
    drawWoodLeaves(texturesBirchLeaves, P, V, M * glm::translate(I, glm::vec3(-1.0, 0.0, -2.0)));
    drawWoodLeaves(texturesBirchLeaves, P, V, M * glm::translate(I, glm::vec3(1.0, 0.0, -2.0)));
    drawWoodLeaves(texturesBirchLeaves, P, V, M * glm::translate(I, glm::vec3(0.0, 0.0, -2.0)));
    drawWoodLeaves(texturesBirchLeaves, P, V, M * glm::translate(I, glm::vec3(1.0, 0.0, 1.0)));
    drawWoodLeaves(texturesBirchLeaves, P, V, M * glm::translate(I, glm::vec3(0.0, 0.0, 1.0)));
    drawWoodLeaves(texturesBirchLeaves, P, V, M * glm::translate(I, glm::vec3(-1.0, 0.0, 1.0)));
    drawWoodLeaves(texturesBirchLeaves, P, V, M * glm::translate(I, glm::vec3(-1.0, 0.0, -3.0)));
    drawWoodLeaves(texturesBirchLeaves, P, V, M * glm::translate(I, glm::vec3(0.0, 0.0, -3.0)));
    drawWoodLeaves(texturesBirchLeaves, P, V, M * glm::translate(I, glm::vec3(1.0, 0.0, -3.0)));
    drawWoodLeaves(texturesBirchLeaves, P, V, M * glm::translate(I, glm::vec3(2.0, 0.0, 0.0)));
    drawWoodLeaves(texturesBirchLeaves, P, V, M * glm::translate(I, glm::vec3(2.0, 0.0, -1.0)));
    drawWoodLeaves(texturesBirchLeaves, P, V, M * glm::translate(I, glm::vec3(2.0, 0.0, -2.0)));
    drawWoodLeaves(texturesBirchLeaves, P, V, M * glm::translate(I, glm::vec3(-2.0, 0.0, 0.0)));
    drawWoodLeaves(texturesBirchLeaves, P, V, M * glm::translate(I, glm::vec3(-2.0, 0.0, -1.0)));
    drawWoodLeaves(texturesBirchLeaves, P, V, M * glm::translate(I, glm::vec3(-2.0, 0.0, -2.0)));
    // First floor Circle
    drawWoodLeaves(texturesBirchLeaves, P, V, M * glm::translate(I, glm::vec3(1.0, 1.0, 0.0)));
    drawWoodLeaves(texturesBirchLeaves, P, V, M * glm::translate(I, glm::vec3(-1.0, 1.0, 0.0)));
    drawWoodLeaves(texturesBirchLeaves, P, V, M * glm::translate(I, glm::vec3(-1.0, 1.0, -1.0)));
    drawWoodLeaves(texturesBirchLeaves, P, V, M * glm::translate(I, glm::vec3(1.0, 1.0, -1.0)));
    drawWoodLeaves(texturesBirchLeaves, P, V, M * glm::translate(I, glm::vec3(-1.0, 1.0, -2.0)));
    drawWoodLeaves(texturesBirchLeaves, P, V, M * glm::translate(I, glm::vec3(1.0, 1.0, -2.0)));
    drawWoodLeaves(texturesBirchLeaves, P, V, M * glm::translate(I, glm::vec3(0.0, 1.0, -2.0)));
    drawWoodLeaves(texturesBirchLeaves, P, V, M * glm::translate(I, glm::vec3(0.0, 1.0, 0.0)));
    // Top Leaves
    drawWoodLeaves(texturesBirchLeaves, P, V, M * glm::translate(I, glm::vec3(0.0, 2.0, -1.0)));
}

void drawOakTree(glm::mat4 P, glm::mat4 V, glm::mat4 M) {
    // Logs
    drawWoodLog(texturesOakLogSide, texturesOakLogTop, P, V, M * I);
    drawWoodLog(texturesOakLogSide, texturesOakLogTop, P, V, M * glm::translate(I, glm::vec3(0.0, 1.0, 0.0)));
    drawWoodLog(texturesOakLogSide, texturesOakLogTop, P, V, M * glm::translate(I, glm::vec3(0.0, 2.0, 0.0)));
    drawWoodLog(texturesOakLogSide, texturesOakLogTop, P, V, M * glm::translate(I, glm::vec3(0.0, 3.0, 0.0)));
    // Minus one floor circle
    drawWoodLeaves(texturesOakLeaves, P, V, M * I);
    drawWoodLeaves(texturesOakLeaves, P, V, M * glm::translate(I, glm::vec3(1.0, -1.0, 0.0)));
    drawWoodLeaves(texturesOakLeaves, P, V, M * glm::translate(I, glm::vec3(-1.0, -1.0, 0.0)));
    drawWoodLeaves(texturesOakLeaves, P, V, M * glm::translate(I, glm::vec3(-1.0, -1.0, -1.0)));
    drawWoodLeaves(texturesOakLeaves, P, V, M * glm::translate(I, glm::vec3(1.0, -1.0, -1.0)));
    drawWoodLeaves(texturesOakLeaves, P, V, M * glm::translate(I, glm::vec3(-1.0, -1.0, -2.0)));
    drawWoodLeaves(texturesOakLeaves, P, V, M * glm::translate(I, glm::vec3(1.0, -1.0, -2.0)));
    drawWoodLeaves(texturesOakLeaves, P, V, M * glm::translate(I, glm::vec3(0.0, -1.0, -2.0)));
    drawWoodLeaves(texturesOakLeaves, P, V, M * glm::translate(I, glm::vec3(1.0, -1.0, 1.0)));
    drawWoodLeaves(texturesOakLeaves, P, V, M * glm::translate(I, glm::vec3(0.0, -1.0, 1.0)));
    drawWoodLeaves(texturesOakLeaves, P, V, M * glm::translate(I, glm::vec3(-1.0, -1.0, 1.0)));
    drawWoodLeaves(texturesOakLeaves, P, V, M * glm::translate(I, glm::vec3(-1.0, -1.0, -3.0)));
    drawWoodLeaves(texturesOakLeaves, P, V, M * glm::translate(I, glm::vec3(0.0, -1.0, -3.0)));
    drawWoodLeaves(texturesOakLeaves, P, V, M * glm::translate(I, glm::vec3(1.0, -1.0, -3.0)));
    drawWoodLeaves(texturesOakLeaves, P, V, M * glm::translate(I, glm::vec3(2.0, -1.0, 0.0)));
    drawWoodLeaves(texturesOakLeaves, P, V, M * glm::translate(I, glm::vec3(2.0, -1.0, -1.0)));
    drawWoodLeaves(texturesOakLeaves, P, V, M * glm::translate(I, glm::vec3(2.0, -1.0, -2.0)));
    drawWoodLeaves(texturesOakLeaves, P, V, M * glm::translate(I, glm::vec3(-2.0, -1.0, 0.0)));
    drawWoodLeaves(texturesOakLeaves, P, V, M * glm::translate(I, glm::vec3(-2.0, -1.0, -1.0)));
    drawWoodLeaves(texturesOakLeaves, P, V, M * glm::translate(I, glm::vec3(-2.0, -1.0, -2.0)));
    drawWoodLeaves(texturesOakLeaves, P, V, M * glm::translate(I, glm::vec3(0.0, -1.0, 0.0)));
    // Zero floor Circle
    drawWoodLeaves(texturesOakLeaves, P, V, M * I);
    drawWoodLeaves(texturesOakLeaves, P, V, M * glm::translate(I, glm::vec3(1.0, 0.0, 0.0)));
    drawWoodLeaves(texturesOakLeaves, P, V, M * glm::translate(I, glm::vec3(-1.0, 0.0, 0.0)));
    drawWoodLeaves(texturesOakLeaves, P, V, M * glm::translate(I, glm::vec3(-1.0, 0.0, -1.0)));
    drawWoodLeaves(texturesOakLeaves, P, V, M * glm::translate(I, glm::vec3(1.0, 0.0, -1.0)));
    drawWoodLeaves(texturesOakLeaves, P, V, M * glm::translate(I, glm::vec3(-1.0, 0.0, -2.0)));
    drawWoodLeaves(texturesOakLeaves, P, V, M * glm::translate(I, glm::vec3(1.0, 0.0, -2.0)));
    drawWoodLeaves(texturesOakLeaves, P, V, M * glm::translate(I, glm::vec3(0.0, 0.0, -2.0)));
    drawWoodLeaves(texturesOakLeaves, P, V, M * glm::translate(I, glm::vec3(1.0, 0.0, 1.0)));
    drawWoodLeaves(texturesOakLeaves, P, V, M * glm::translate(I, glm::vec3(0.0, 0.0, 1.0)));
    drawWoodLeaves(texturesOakLeaves, P, V, M * glm::translate(I, glm::vec3(-1.0, 0.0, 1.0)));
    drawWoodLeaves(texturesOakLeaves, P, V, M * glm::translate(I, glm::vec3(-1.0, 0.0, -3.0)));
    drawWoodLeaves(texturesOakLeaves, P, V, M * glm::translate(I, glm::vec3(0.0, 0.0, -3.0)));
    drawWoodLeaves(texturesOakLeaves, P, V, M * glm::translate(I, glm::vec3(1.0, 0.0, -3.0)));
    drawWoodLeaves(texturesOakLeaves, P, V, M * glm::translate(I, glm::vec3(2.0, 0.0, 0.0)));
    drawWoodLeaves(texturesOakLeaves, P, V, M * glm::translate(I, glm::vec3(2.0, 0.0, -1.0)));
    drawWoodLeaves(texturesOakLeaves, P, V, M * glm::translate(I, glm::vec3(2.0, 0.0, -2.0)));
    drawWoodLeaves(texturesOakLeaves, P, V, M * glm::translate(I, glm::vec3(-2.0, 0.0, 0.0)));
    drawWoodLeaves(texturesOakLeaves, P, V, M * glm::translate(I, glm::vec3(-2.0, 0.0, -1.0)));
    drawWoodLeaves(texturesOakLeaves, P, V, M * glm::translate(I, glm::vec3(-2.0, 0.0, -2.0)));
    // First floor Circle
    drawWoodLeaves(texturesOakLeaves, P, V, M * glm::translate(I, glm::vec3(1.0, 1.0, 0.0)));
    drawWoodLeaves(texturesOakLeaves, P, V, M * glm::translate(I, glm::vec3(-1.0, 1.0, 0.0)));
    drawWoodLeaves(texturesOakLeaves, P, V, M * glm::translate(I, glm::vec3(-1.0, 1.0, -1.0)));
    drawWoodLeaves(texturesOakLeaves, P, V, M * glm::translate(I, glm::vec3(1.0, 1.0, -1.0)));
    drawWoodLeaves(texturesOakLeaves, P, V, M * glm::translate(I, glm::vec3(-1.0, 1.0, -2.0)));
    drawWoodLeaves(texturesOakLeaves, P, V, M * glm::translate(I, glm::vec3(1.0, 1.0, -2.0)));
    drawWoodLeaves(texturesOakLeaves, P, V, M * glm::translate(I, glm::vec3(0.0, 1.0, -2.0)));
    drawWoodLeaves(texturesOakLeaves, P, V, M * glm::translate(I, glm::vec3(0.0, 1.0, 0.0)));
    // Top Leaves
    drawWoodLeaves(texturesOakLeaves, P, V, M * glm::translate(I, glm::vec3(0.0, 2.0, -1.0)));

}

void drawTorch(glm::mat4 P, glm::mat4 V, glm::mat4 M) {
    drawWoodLog(texturesOakLogSide, texturesOakLogTop, P, V, M * I);
    drawWoodLog(texturesOakLogSide, texturesOakLogTop, P, V, M * glm::translate(I, glm::vec3(0.0, 1.0, 0.0)));
    drawWoodLog(texturesOakLogSide, texturesOakLogTop, P, V, M * glm::translate(I, glm::vec3(0.0, 2.0, 0.0)));
    drawObjectMat(modelSlab, mluz, P, V,
                  M * glm::translate(I, glm::vec3(0.0, 7.0, 1.5)) * glm::scale(I, glm::vec3(0.5)));
    drawObjectTex(modelSlab, texturesOrangeBlock, P, V,
                  M * glm::translate(I, glm::vec3(0.0, 7.5, 1.5)) * glm::scale(I, glm::vec3(0.5)));
}

void drawEnvironment(glm::mat4 P, glm::mat4 V) {
    // Planet
    glm::mat4 S = glm::scale(I, glm::vec3(2));
    drawObjectTex(modelSphere, texturesDirtBlock, P, V, S);
    // Ores
    drawObjectTex(modelDiamondOre, texturesDiamondOre, P, V,
                  glm::rotate(I, glm::radians(100.0f), glm::vec3(0.0, 1.0, 0.0)) *
                  glm::rotate(I, glm::radians(225.0f), glm::vec3(1.0, 0.0, 0.0)) *
                  glm::translate(I, glm::vec3(0.0, 3.8, 1.0)) *
                  glm::scale(I, glm::vec3(1)));
    drawObjectTex(modelIronOre, texturesIronOre, P, V,
                  glm::rotate(I, glm::radians(245.0f), glm::vec3(0.0, 1.0, 0.0)) *
                  glm::rotate(I, glm::radians(200.0f), glm::vec3(1.0, 0.0, 0.0)) *
                  glm::translate(I, glm::vec3(0.0, 3.8, 1.0)) *
                  glm::scale(I, glm::vec3(1)));
    // Mobs
    drawObjectTex(modelPig, texturesPig, P, V, glm::rotate(I, glm::radians(-90.0f), glm::vec3(1.0, 0.0, 0.0)) *
                                                       glm::rotate(I, glm::radians(-70.0f), glm::vec3(0.0, 1.0, 0.0)) *
                                                       glm::rotate(I, glm::radians(-55.0f), glm::vec3(1.0, 0.0, 0.0)) *
                                                       glm::translate(I, glm::vec3(0.0, 4.4, 1.0)) *
                                                       glm::scale(I, glm::vec3(0.08)));
    drawObjectTex(modelCreeper, texturesCreeper, P, V, glm::rotate(I, glm::radians(90.0f), glm::vec3(1.0, 0.0, 0.0)) *
                                                       glm::rotate(I, glm::radians(106.0f), glm::vec3(0.0, 1.0, 0.0)) *
                                                       glm::rotate(I, glm::radians(75.0f), glm::vec3(1.0, 0.0, 0.0)) *
                                                       glm::translate(I, glm::vec3(0.0, 3.8, 1.0)) *
                                                       glm::scale(I, glm::vec3(1)));
    drawObjectTex(modelSpider, texturesSpider, P, V, glm::rotate(I, glm::radians(-90.0f), glm::vec3(1.0, 0.0, 0.0)) *
                                                     glm::rotate(I, glm::radians(-50.0f), glm::vec3(0.0, 1.0, 0.0)) *
                                                     glm::rotate(I, glm::radians(140.0f), glm::vec3(1.0, 0.0, 0.0)) *
                                                     glm::translate(I, glm::vec3(0.0, 4.2, 1.0)) *
                                                     glm::scale(I, glm::vec3(0.05)));
    drawObjectTex(modelMagmacube, texturesMagmacube, P, V,
                  glm::rotate(I, glm::radians(90.0f), glm::vec3(1.0, 0.0, 0.0)) *
                  glm::rotate(I, glm::radians(-140.0f), glm::vec3(0.0, 1.0, 0.0)) *
                  glm::rotate(I, glm::radians(140.0f), glm::vec3(1.0, 0.0, 0.0)) *
                  glm::translate(I, glm::vec3(0.0, 4.2, 1.0)) *
                  glm::scale(I, glm::vec3(0.1)));
    // Torches
    drawTorch(P, V, glm::rotate(I, glm::radians(45.0f), glm::vec3(0.0, 1.0, 0.0)) *
                    glm::rotate(I, glm::radians(85.0f), glm::vec3(1.0, 0.0, 0.0)) *
                    glm::translate(I, glm::vec3(-0.1, 3.3, -0.25)) * glm::scale(I, glm::vec3(0.16)));
    drawTorch(P, V, glm::rotate(I, glm::radians(-45.0f), glm::vec3(0.0, 1.0, 0.0)) *
                    glm::rotate(I, glm::radians(85.0f), glm::vec3(1.0, 0.0, 0.0)) *
                    glm::translate(I, glm::vec3(-0.1, 3.3, -0.25)) * glm::scale(I, glm::vec3(0.16)));
    drawTorch(P, V, glm::rotate(I, glm::radians(45.0f), glm::vec3(0.0, 1.0, 0.0)) *
                    glm::rotate(I, glm::radians(135.0f), glm::vec3(1.0, 0.0, 0.0)) *
                    glm::translate(I, glm::vec3(-0.1, 3.3, -0.25)) * glm::scale(I, glm::vec3(0.16)));
    drawTorch(P, V, glm::rotate(I, glm::radians(135.0f), glm::vec3(0.0, 1.0, 0.0)) *
                    glm::rotate(I, glm::radians(135.0f), glm::vec3(1.0, 0.0, 0.0)) *
                    glm::translate(I, glm::vec3(-0.1, 3.3, -0.25)) * glm::scale(I, glm::vec3(0.16)));
    drawTorch(P, V, glm::rotate(I, glm::radians(115.0f), glm::vec3(0.0, 1.0, 0.0)) *
                    glm::rotate(I, glm::radians(100.0f), glm::vec3(1.0, 0.0, 0.0)) *
                    glm::translate(I, glm::vec3(-0.1, 3.3, -0.25)) * glm::scale(I, glm::vec3(0.16)));
    drawTorch(P, V, glm::rotate(I, glm::radians(195.0f), glm::vec3(0.0, 1.0, 0.0)) *
                    glm::rotate(I, glm::radians(85.0f), glm::vec3(1.0, 0.0, 0.0)) *
                    glm::translate(I, glm::vec3(-0.1, 3.3, -0.25)) * glm::scale(I, glm::vec3(0.16)));
    // Trees
    drawBirchTree(P, V, glm::rotate(I, glm::radians(45.0f), glm::vec3(0, 1, 0)) *
                        glm::rotate(I, glm::radians(45.0f), glm::vec3(1, 0, 0)) *
                        glm::rotate(I, glm::radians(15.0f), glm::vec3(1, 0, 0)) *
                        glm::translate(glm::scale(I, glm::vec3(0.5)), glm::vec3(0.0, 3.7, 0.0)));
    drawOakTree(P, V, glm::rotate(I, glm::radians(85.0f), glm::vec3(0, 1, 0)) *
                      glm::rotate(I, glm::radians(85.0f), glm::vec3(1, 0, 0)) *
                      glm::rotate(I, glm::radians(15.0f), glm::vec3(1, 0, 0)) *
                      glm::translate(glm::scale(I, glm::vec3(0.5)), glm::vec3(0.0, 3.7, 0.0)));
    drawOakTree(P, V, glm::rotate(I, glm::radians(-65.0f), glm::vec3(0, 1, 0)) *
                      glm::rotate(I, glm::radians(-65.0f), glm::vec3(1, 0, 0)) *
                      glm::rotate(I, glm::radians(0.0f), glm::vec3(1, 0, 0)) *
                      glm::translate(glm::scale(I, glm::vec3(0.5)), glm::vec3(0.0, 3.7, 0.0)));
    drawBirchTree(P, V, glm::rotate(I, glm::radians(120.0f), glm::vec3(0, 1, 0)) *
                        glm::rotate(I, glm::radians(120.0f), glm::vec3(1, 0, 0)) *
                        glm::rotate(I, glm::radians(15.0f), glm::vec3(1, 0, 0)) *
                        glm::translate(glm::scale(I, glm::vec3(0.5)), glm::vec3(0.0, 3.7, 0.0)));
    drawOakTree(P, V, glm::rotate(I, glm::radians(280.0f), glm::vec3(1, 0, 0)) *
                      glm::rotate(I, glm::radians(280.0f), glm::vec3(0, 1, 0)) *
                      glm::rotate(I, glm::radians(60.0f), glm::vec3(1, 0, 0)) *
                      glm::rotate(I, glm::radians(60.0f), glm::vec3(0, 0, 1)) *
                      glm::translate(glm::scale(I, glm::vec3(0.5)), glm::vec3(0.0, 3.7, 0.0)));
    drawBirchTree(P, V, glm::rotate(I, glm::radians(-270.0f), glm::vec3(1, 0, 0)) *
                        glm::rotate(I, glm::radians(-270.0f), glm::vec3(0, 0, 1)) *
                        glm::rotate(I, glm::radians(0.0f), glm::vec3(1, 0, 0)) *
                        glm::translate(glm::scale(I, glm::vec3(0.5)), glm::vec3(0.0, 3.7, 0.0)));
    drawOakTree(P, V, glm::rotate(I, glm::radians(-215.0f), glm::vec3(1, 0, 0)) *
                      glm::rotate(I, glm::radians(-215.0f), glm::vec3(0, 0, 1)) *
                      glm::rotate(I, glm::radians(0.0f), glm::vec3(1, 0, 0)) *
                      glm::translate(glm::scale(I, glm::vec3(0.5)), glm::vec3(0.0, 3.7, 0.0)));
    drawOakTree(P, V, glm::rotate(I, glm::radians(-320.0f), glm::vec3(1, 0, 0)) *
                      glm::rotate(I, glm::radians(-320.0f), glm::vec3(0, 0, 1)) *
                      glm::rotate(I, glm::radians(0.0f), glm::vec3(1, 0, 0)) *
                      glm::translate(glm::scale(I, glm::vec3(0.5)), glm::vec3(0.0, 3.7, 0.0)));

}
