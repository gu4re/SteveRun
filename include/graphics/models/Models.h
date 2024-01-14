//
// Created by diegopicazo on 13/1/24.
//

#ifndef MODELS_H
#define MODELS_H

#include "ModelsManager.h"
#include "../shaders/Shaders.h"

// Modelos
// Blocks
inline ModelsManager modelDiamondOre;
inline ModelsManager modelEmeraldOre;
inline ModelsManager modelGoldOre;
inline ModelsManager modelGrassBlock;
inline ModelsManager modelIronOre;
inline ModelsManager modelLapisOre;
// Mobs
inline ModelsManager modelCreeper;
inline ModelsManager modelMagmacube;
inline ModelsManager modelSpider;
inline ModelsManager modelSteve;
// General
inline ModelsManager modelSphere;
inline ModelsManager modelPlane;
inline ModelsManager modelCube;

void drawObjectMat(ModelsManager &model, Material &material, glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawObjectTex(ModelsManager &model, Textures &textures, glm::mat4 P, glm::mat4 V, glm::mat4 M);

#endif //MODELS_H
