//
// Created by diegopicazo on 14/1/24.
//

#include "../../../../include/graphics/renders/menu/RenderMenu.h"
#include "../../../../include/core/variables/Variables.h"

void renderMenu(GLFWwindow *window, ALCdevice* SoundDevice, ALCcontext* SoundContext, ALuint SoundSource, ALuint SoundBuffer) {
    // Configuramos los CallBacks
    glfwSetKeyCallback(window, callbackMenuFunKey);
    glfwSetScrollCallback(window, nullptr);
    glfwSetCursorPosCallback(window, nullptr);

    // Borramos el buffer de color
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    toggleSound(SoundSource);

    // Indicamos los shaders a utilizar
    shaders.useShaders();

    // Matriz P
    float nplane = 0.1;
    float fplane = 25.0;
    float aspect = (float) w / (float) h;
    // Custom fovy
    fovy = 45;
    glm::mat4 P = glm::perspective(glm::radians(fovy), aspect, nplane, fplane);

    // Matriz V
    glm::vec3 eye(10.0, 5.0, 20.0);
    glm::vec3 center(0.0, 0.0, 0.0);
    glm::vec3 up(0.0, 1.0, 0.0);
    glm::mat4 V = glm::lookAt(eye, center, up);
    shaders.setVec3("ueye", eye);

    // Fijamos las luces
    setLights(P, V);

    // Dibujamos el personaje
    // Control de la rotacion automatica del personaje
    auto currentTime = glfwGetTime();
    double deltaTime = currentTime - last_timer;
    // Check if the threshold is passed
    if (deltaTime >= 0.019) {
        last_timer = currentTime;
        rotP += 2.0;
        // Ensuring that the angle is always less than 360º
        rotP = static_cast<float>(fmod(rotP, 360.0));
    }
    // Cubo
    glm::mat4 T = glm::translate(I, glm::vec3(cubeX, cubeY, cubeZ));
    glm::mat4 S1 = glm::scale(I, glm::vec3(0.5));
    glm::mat4 R1 = glm::rotate(I, glm::radians(rotP), glm::vec3(1, 0, 0));
    drawObjectTex(modelCube, texturesStoneBlock, P, V, R1 * S1 * T); // dibujamos el personaje

    drawEnvironment(P, V);

    // Dibujamos el título del juego
    drawObjectTex(modelPlane, texturesGameTitle, P, V, glm::scale(I, glm::vec3(5.0))*glm::rotate(
            glm::rotate(
                    glm::translate(I, glm::vec3(0.3, 0.1, 1.1)),
                    glm::radians(89.0f), glm::vec3(1, 0, 0)
            ),
            glm::radians(-89.0f), glm::vec3(0, 1, 0)
    ));
    // Dibujamos el subtítulo del juego
    drawObjectTex(modelPlane, texturesGameSubtitle, P, V, glm::scale(I, glm::vec3(0.7))*glm::scale(I, glm::vec3(3.0, 0.5, 3.0))*glm::rotate(
            glm::rotate(
                    glm::translate(I, glm::vec3(1.2, -0.8, 3.1)),
                    glm::radians(89.0f), glm::vec3(1, 0, 0)
            ),
            glm::radians(-89.0f), glm::vec3(0, 1, 0)
    ));

    // Efecto texturesSepiaEffect al menu
    glm::mat4 sepiaSize = glm::scale(I, glm::vec3(20));
    glm::mat4 sepiaPos = glm::rotate(
            glm::rotate(
                    glm::translate(I, glm::vec3(0.4, 0.1, 0.8)),
                    glm::radians(25.0f), glm::vec3(0, 1, 0)
            ),
            glm::radians(90.0f), glm::vec3(1, 0, 0)
    );
    glDepthMask(GL_FALSE);
    drawObjectTex(modelPlane, texturesSepiaEffect, P, V, sepiaSize * sepiaPos);
    glDepthMask(GL_TRUE);

}
