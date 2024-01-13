#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "shaders/Shaders.h"
#include "models/Models.h"
#include "textures/Textures.h"
#include <set>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "init/Init.h"
#include "lights/Lights.h"

void renderGame(GLFWwindow *window);

void renderMenu(GLFWwindow *window);

void setLights(glm::mat4 P, glm::mat4 V);

void drawObjectMat(ModelsManager &model, Material &material, glm::mat4 P, glm::mat4 V, glm::mat4 M);

void drawObjectTex(ModelsManager &model, Textures &textures, glm::mat4 P, glm::mat4 V, glm::mat4 M);

void renderEnemy(float angle, glm::mat4 P, glm::mat4 V);

void reset();

void screenMode(GLFWwindow *window);

void funFramebufferSize(GLFWwindow *window, int width, int height);

void gamefunKey(GLFWwindow *window, int key, int scancode, int action, int mods);

void gamefunScroll(GLFWwindow *window, double xoffset, double yoffset);

void gamefunCursorPos(GLFWwindow *window, double xpos, double ypos);

void menufunKey(GLFWwindow *window, int key, int scancode, int action, int mods);

// Viewport
int w = 700;
int h = 700;
bool fullscreen_mode = false;

// Animaciones
float rotP = 0.0;
float jump = 0.0;
double last_timer = 0.0;

// Movimiento de camara
float fovy = 60.0;
float alphaX = 0.0;
float alphaY = 0.0;

// Variables globales para las coordenadas del cubo
float cubeX = 0.0f;
float cubeY = 9.0f;
float cubeZ = 0.0f;

// Variable que indica si el juego está en marcha
bool gameRunning = false;

// Variable que indica si el personaje está realmente saltando
// (comprueba que la tecla espacio no se haya dejado pulsada continuamente)
bool isJumping = false;
//  Variable que controla si estamos en el menu
bool inMainMenu = true;

int main() {

    // Inicializa lo necesario
    auto [window, ft, face] = init();

    // Callbacks globales para todas las capas de renderizado
    glfwSetFramebufferSizeCallback(window, funFramebufferSize);

    while (!glfwWindowShouldClose(window)) {
        if (inMainMenu) {
            renderMenu(window);
            glfwSwapBuffers(window);
            glfwPollEvents();
        } else {
            renderGame(window);
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

void renderGame(GLFWwindow *window) {
    // Configuramos los CallBacks
    glfwSetKeyCallback(window, gamefunKey);
    glfwSetScrollCallback(window, gamefunScroll);
    glfwSetCursorPosCallback(window, gamefunCursorPos);

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

void funFramebufferSize([[maybe_unused]] GLFWwindow *window, int width, int height) {

    // Configuracion del Viewport
    glViewport(0, 0, width, height);

    // Actualizacion de w y h
    w = width;
    h = height;

}

void gamefunKey(GLFWwindow *window, int key, [[maybe_unused]] int scancode, int action,
                [[maybe_unused]] int mods) {

    switch (key) {
        case GLFW_KEY_UP:
            rotP += 5.0f;
            //Imprime las coordenadas del cubo
            //std::cout << "Tecla de flecha arriba - Coordenadas del cubo: (" << cubeX << ", " << cubeY << ", " << cubeZ << ")" << std::endl;
            break;
        case GLFW_KEY_R:
            if (action == GLFW_PRESS) {
                gameRunning = false;
                reset();
            }
            break;
        case GLFW_KEY_SPACE:
            if (action == GLFW_PRESS) {
                if (!gameRunning) {
                    reset();
                }
                isJumping = true;
                gameRunning = true;
                jump = 2.0f;
                //std::cout << "Tecla de salto Coordenadas del cubo: (" << cubeX << ", " << cubeY << ", " << cubeZ << ")" << std::endl;
            } else {
                jump = 0.0f;
                isJumping = false;
            }
            break;
        case GLFW_KEY_F:
            if (action == GLFW_PRESS) {
                fullscreen_mode ? fullscreen_mode = false : fullscreen_mode = true;
                screenMode(window);
            }
            break;
        case GLFW_KEY_ESCAPE:
            if (action == GLFW_PRESS) {
                inMainMenu = true;
            }
            break;
        default:
            break;
    }

}

void gamefunScroll([[maybe_unused]] GLFWwindow *window, [[maybe_unused]] double xoffset,
                   double yoffset) {

    if (yoffset > 0) fovy -= fovy > 10.0f ? 5.0f : 0.0f;
    if (yoffset < 0) fovy += fovy < 90.0f ? 5.0f : 0.0f;

}

void gamefunCursorPos(GLFWwindow *window, double xpos, double ypos) {

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) return;

    float limY = 89.0;
    alphaX = static_cast<float>(90.0 * (2.0 * xpos / static_cast<float>(w) - 1.0));
    alphaY = static_cast<float>(90.0 * (1.0 - 2.0 * ypos / (float) h));
    if (alphaY < -limY) alphaY = -limY;
    if (alphaY > limY) alphaY = limY;

}

void renderEnemy(float angle, glm::mat4 P, glm::mat4 V) {
    glm::mat4 S = glm::scale(I, glm::vec3(0.30));
    glm::mat4 T = glm::translate(I, glm::vec3(0, 14.42, 0));
    glm::mat4 R = glm::rotate(I, glm::radians(angle), glm::vec3(1, 0, 0));

    drawObjectTex(modelCube, texturesStoneBlock, P, V, R * S * T);
}

void reset() {
    cubeX = 0.0;
    cubeZ = 0.0;
    cubeY = 9.0;
    rotP = 0.0;
}

void screenMode(GLFWwindow *window) {
    // Gets the current monitor where is running the game
    GLFWmonitor *primaryMonitor = glfwGetPrimaryMonitor();
    int xpos, ypos;
    glfwGetWindowPos(window, &xpos, &ypos);
    // Gets the video mode to obtain screen specs
    const GLFWvidmode *videoMode = glfwGetVideoMode(primaryMonitor);
    if (fullscreen_mode) {
        glfwSetWindowMonitor(window, primaryMonitor, 0, 0,
                             videoMode->width, videoMode->height, videoMode->refreshRate);
    } else {
        glfwSetWindowMonitor(window, nullptr, (videoMode->width / 2) - 700,
                             (videoMode->height / 2) - 700, 700, 700,
                             videoMode->refreshRate);
    }
}

void renderMenu(GLFWwindow *window) {
    // Configuramos los CallBacks
    glfwSetKeyCallback(window, menufunKey);
    glfwSetScrollCallback(window, nullptr);
    glfwSetCursorPosCallback(window, nullptr);

    // Borramos el buffer de color
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

    // Dibujamos el planeta
    glm::mat4 S = glm::scale(I, glm::vec3(2));
    drawObjectTex(modelSphere, texturesStoneBlock, P, V, S);

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

void menufunKey(GLFWwindow *window, int key, [[maybe_unused]] int scancode, int action,
                [[maybe_unused]] int mods) {
    switch (key) {
        case GLFW_KEY_ENTER:
            if (action == GLFW_PRESS) {
                inMainMenu = false;
                reset();
            }
            break;
        case GLFW_KEY_F:
            if (action == GLFW_PRESS) {
                fullscreen_mode ? fullscreen_mode = false : fullscreen_mode = true;
                screenMode(window);
            }
            break;
        case GLFW_KEY_ESCAPE:
            if (action == GLFW_PRESS) {
                exit(0);
            }
        default:
            break;
    }
}