//
// Created by diegopicazo on 14/1/24.
//

#include "../../../../include/graphics/renders/game/RenderGame.h"
#include "../../../../include/core/variables/Variables.h"

// Configurar el generador de números aleatorios
std::random_device rd;
std::mt19937 gen(rd());
// Array con las posiciones de los 8 obstáculos/enemigos
float enemyPositions[8] = {20.0, 65.0, 110.0, 155.0, 200.0, 245.0, 290.0, 335.0};
// Array con los números que seleccionarán las texturas de los obstaculos/enemigos
int textureNumber[8] = {0, 1, 2, 3, 4, 5, 6, 7};

void renderGame(GLFWwindow *window, ALuint SoundSource) {
    // Configuramos los CallBacks
    glfwSetKeyCallback(window, callbackGameFunKey);
    glfwSetScrollCallback(window, callbackGameFunScroll);
    glfwSetCursorPosCallback(window, callbackGameFunCursorPos);

    // Borramos el buffer de color
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Controlamos la música
    toggleSound(SoundSource);

    // Indicamos los shaders a utilizar
    shaders.useShaders();

    // Matriz P
    float nplane = 0.1;
    float fplane = 35.0;
    float aspect = (float) w / (float) h;
    glm::mat4 P = glm::perspective(glm::radians(fovy), aspect, nplane, fplane);

    // Matriz V
    float x = -10.0f * glm::cos(glm::radians(alphaY)) * glm::sin(glm::radians(alphaX));
    float y = -10.0f * glm::sin(glm::radians(alphaY));
    float z = -10.0f * glm::cos(glm::radians(alphaY)) * glm::cos(glm::radians(alphaX));
    glm::vec3 eye(x, y, z);
    glm::vec3 center(0.0, 5.0, 0.0);
    glm::vec3 up(0.0, 1.0, 0.0);

    glm::mat4 rotationMatrix = glm::rotate(I, glm::radians(rotP), glm::vec3(1, 0, 0));
    eye = glm::vec3(rotationMatrix * glm::vec4(eye, 1.0));
    center = glm::vec3(rotationMatrix * glm::vec4(center, 1.0));
    up = glm::vec3(rotationMatrix * glm::vec4(up, 1.0));

    glm::mat4 V = glm::lookAt(eye, center, up);
    shaders.setVec3("ueye", eye);

    // Fijamos las luces
    setLights();

    // Dibujamos la escena
    if (gameRunning) {
        auto currentTime = glfwGetTime();
        double deltaTime = currentTime - last_timer;
        // Check if the threshold is passed
        if (deltaTime >= 0.030) {
            last_timer = currentTime;
            rotP += 2.0;
            // Ensuring that the angle is always less than 360º
            rotP = static_cast<float>(fmod(rotP, 360.0));
        }
    }
    glm::mat4 T = glm::translate(I, glm::vec3(cubeX, cubeY, cubeZ));
    glm::mat4 Salto = glm::translate(I, glm::vec3(cubeX, jump, cubeZ));
    glm::mat4 S1 = glm::scale(I, glm::vec3(0.07));
    glm::mat4 R1 = glm::rotate(I, glm::radians(rotP), glm::vec3(1, 0, 0));
    drawObjectTex(modelSteve, texturesSteve, P, V, R1 * S1 * Salto * T);// dibujamos el personaje

    //Dibujamos obstáculo/enemigo
    for(int i = 0; i <=7; i++) {
        if(renderedEnemy[i]){
            renderEnemy(enemyPositions[i], textureNumber[i], P, V);
            // Comparamos los ángulos de rotación del personaje y el enemigo
            std::set<int> rangoPermitido;
            for (int j = (int)enemyPositions[i] - 8; j <= (int)enemyPositions[i] + 8; j++) {
                rangoPermitido.insert(j);
            }
            if (rangoPermitido.count(static_cast<int>(rotP)) && !isJumping) {
                gameRunning = false;
            }
        }
    }

    switch ((int)rotP) {
        case 20: {
            std::uniform_int_distribution<int> uniformIntDistribution(0, 8);
            textureNumber[3] = uniformIntDistribution(gen);
            renderedEnemy[2] = true;
            renderedEnemy[7] = false;
            break;
        }
        case 66: { // rotP nunca será impar porque avanza de 2 en 2
            std::uniform_int_distribution<int> uniformIntDistribution(0, 8);
            textureNumber[4] = uniformIntDistribution(gen);
            renderedEnemy[3] = true;
            renderedEnemy[0] = false;
            break;
        }
        case 110: {
            std::uniform_int_distribution<int> uniformIntDistribution(0, 8);
            textureNumber[5] = uniformIntDistribution(gen);
            renderedEnemy[4] = true;
            renderedEnemy[1] = false;
            break;
        }
        case 156: {
            std::uniform_int_distribution<int> uniformIntDistribution(0, 8);
            textureNumber[6] = uniformIntDistribution(gen);
            renderedEnemy[5] = true;
            renderedEnemy[2] = false;
            break;
        }
        case 200: {
            std::uniform_int_distribution<int> uniformIntDistribution(0, 8);
            textureNumber[7] = uniformIntDistribution(gen);
            renderedEnemy[6] = true;
            renderedEnemy[3] = false;
            break;
        }
        case 246: {
            std::uniform_int_distribution<int> uniformIntDistribution(0, 8);
            textureNumber[0] = uniformIntDistribution(gen);
            renderedEnemy[7] = true;
            renderedEnemy[4] = false;
            break;
        }
        case 290: {
            std::uniform_int_distribution<int> uniformIntDistribution(0, 8);
            textureNumber[1] = uniformIntDistribution(gen);
            renderedEnemy[0] = true;
            renderedEnemy[5] = false;
            break;
        }
        case 336: {
            std::uniform_int_distribution<int> uniformIntDistribution(0, 8);
            textureNumber[2] = uniformIntDistribution(gen);
            renderedEnemy[1] = true;
            renderedEnemy[6] = false;
            break;
        }
    }

    // Dibujamos el entorno
    drawEnvironment(P, V);
}
