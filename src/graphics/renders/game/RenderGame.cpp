//
// Created by diegopicazo on 14/1/24.
//

#include "../../../../include/graphics/renders/game/RenderGame.h"
#include "../../../../include/core/variables/Variables.h"

void renderGame(GLFWwindow *window) {
    // Configuramos los CallBacks
    glfwSetKeyCallback(window, callbackGameFunKey);
    glfwSetScrollCallback(window, callbackGameFunScroll);
    glfwSetCursorPosCallback(window, callbackGameFunCursorPos);

    // Borramos el buffer de color
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Indicamos los shaders a utilizar
    shaders.useShaders();

    // Matriz P
    float nplane = 0.1;
    float fplane = 25.0;
    float aspect = (float) w / (float) h;
    glm::mat4 P = glm::perspective(glm::radians(fovy), aspect, nplane, fplane);

    // Matriz V
    float x = 10.0f * glm::cos(glm::radians(alphaY)) * glm::sin(glm::radians(alphaX));
    float y = 10.0f * glm::sin(glm::radians(alphaY));
    float z = 10.0f * glm::cos(glm::radians(alphaY)) * glm::cos(glm::radians(alphaX));
    glm::vec3 eye(x, y, z);
    glm::vec3 center(0.0, 5.0, 0.0);
    glm::vec3 up(0.0, 1.0, 0.0);
    glm::mat4 V = glm::lookAt(eye, center, up);
    shaders.setVec3("ueye", eye);

    // Fijamos las luces
    setLights(P, V);

    // Dibujamos la escena
    if (gameRunning) {
        auto currentTime = glfwGetTime();
        double deltaTime = currentTime - last_timer;
        // Check if the threshold is passed
        if (deltaTime >= 0.019) {
            last_timer = currentTime;
            rotP += 2.0;
            // Ensuring that the angle is always less than 360º
            rotP = static_cast<float>(fmod(rotP, 360.0));
        }
    }
    glm::mat4 T = glm::translate(I, glm::vec3(cubeX, cubeY, cubeZ));
    glm::mat4 Salto = glm::translate(I, glm::vec3(cubeX, jump, cubeZ));
    glm::mat4 S1 = glm::scale(I, glm::vec3(0.5));
    glm::mat4 R1 = glm::rotate(I, glm::radians(rotP), glm::vec3(1, 0, 0));
    drawObjectTex(modelCube, texturesStoneBlock, P, V, R1 * S1 * Salto * T);// dibujamos el personaje

    //Dibujamos obstáculo/enemigo
    renderEnemy(45, P, V);

    glm::mat4 S = glm::scale(I, glm::vec3(2));
    drawObjectTex(modelSphere, texturesStoneBlock, P, V, S); // dibujamos el planeta

    // Comparamos los ángulos de rotación del personaje y el enemigo
    std::set<int> rangoPermitido;
    for (int i = 33; i <= 57; i++) {
        rangoPermitido.insert(i);
    }
    if (rangoPermitido.count(static_cast<int>(rotP)) && !isJumping) {
        gameRunning = false;
    }
}
