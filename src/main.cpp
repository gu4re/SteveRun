#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shaders.h"
#include "Model.h"
#include "Texture.h"
#include <set>
#include <ft2build.h>
#include FT_FREETYPE_H

std::tuple<GLFWwindow *, FT_Library, FT_Face>init();

void renderGame(GLFWwindow *window);

void renderMenu(GLFWwindow *window);

void setLights(glm::mat4 P, glm::mat4 V);

void drawObjectMat(Model &model, Material &material, glm::mat4 P, glm::mat4 V, glm::mat4 M);

void drawObjectTex(Model &model, Textures &textures, glm::mat4 P, glm::mat4 V, glm::mat4 M);

void renderEnemy(float angle, glm::mat4 P, glm::mat4 V);

void reset();

void screenMode(GLFWwindow *window);

void funFramebufferSize(GLFWwindow *window, int width, int height);

void gamefunKey(GLFWwindow *window, int key, int scancode, int action, int mods);

void gamefunScroll(GLFWwindow *window, double xoffset, double yoffset);

void gamefunCursorPos(GLFWwindow *window, double xpos, double ypos);

void menufunKey(GLFWwindow *window, int key, int scancode, int action, int mods);

// Shaders
Shaders shaders;

// Modelos
// Blocks
Model objDiamondOre;
Model objEmeraldOre;
Model objGoldOre;
Model objGrassBlock;
Model objIronOre;
Model objLapisOre;
// Mobs
Model objCreeper;
Model objMagmacube;
Model objSpider;
Model objSteve;
// General
Model objSphere;
Model objPlane;
Model objCube;

// Imagenes (texturas)
// Blocks
Texture diamondOreEmissiveTex;
Texture diamondOreTex;
Texture emeraldOreEmissiveTex;
Texture emeraldOreTex;
Texture goldOreEmissiveTex;
Texture goldOreTex;
Texture grassBlockTex;
Texture ironOreEmissiveTex;
Texture ironOreTex;
Texture lapisOreEmissiveTex;
Texture lapisOreTex;
Texture oakLeavesTex;
Texture oakLogSideTex;
Texture oakLogTopTex;
Texture oakPlanksTex;
Texture stoneBlockTex;
// Effects
Texture sepiaEffectTex;
Texture sepiaEffectEmissiveTex;
// Mobs
Texture creeperEmissiveTex;
Texture creeperTex;
Texture magmacubeTex;
Texture spiderEmissiveTex;
Texture spiderTex;
Texture steveEmissiveTex;
Texture steveTex;
// General
Texture noEmissiveTex;

// Luces y materiales
#define   NLD 1
#define   NLP 1
#define   NLF 2
Light lightG;
Light lightD[NLD];
Light lightP[NLP];
Light lightF[NLF];
Material mluz;

// Textures
// Blocks
Textures texturesDiamondOre;
Textures texturesEmeraldOre;
Textures texturesGoldOre;
Textures texturesGrassBlock;
Textures texturesIronOre;
Textures texturesLapisOre;
Textures texturesOakLeaves;
Textures texturesOakPlanks;
Textures texturesStoneBlock;
// Effects
Textures texturesSepiaEffect;
// Mobs
Textures texturesCreeper;
Textures texturesMagmacube;
Textures texturesSpider;
Textures texturesSteve;

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

void initScene() {

    // Test de profundidad
    glEnable(GL_DEPTH_TEST);

    // Transparencias
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,
                GL_ONE_MINUS_SRC_ALPHA); //esto es el algoritmo que combina los colores de los objetos opacos de en las transparencias

    // Shaders
    shaders.initShaders("resources/shaders/vshader.glsl",
                        "resources/shaders/fshader.glsl");

    // Modelos
    // Blocks
    objDiamondOre.initModel("resources/models/_blocks/diamondOre.obj");
    objEmeraldOre.initModel("resources/models/_blocks/emeraldOre.obj");
    objGoldOre.initModel("resources/models/_blocks/goldOre.obj");
    objGrassBlock.initModel("resources/models/_blocks/grassBlock.obj");
    objIronOre.initModel("resources/models/_blocks/ironOre.obj");
    objLapisOre.initModel("resources/models/_blocks/lapisOre.obj");
    // Mobs
    objCreeper.initModel("resources/models/_mobs/creeper.obj");
    objMagmacube.initModel("resources/models/_mobs/magmacube.obj");
    objSpider.initModel("resources/models/_mobs/spider.obj");
    objSteve.initModel("resources/models/_mobs/steve.obj");
    // General
    objSphere.initModel("resources/models/sphere.obj");
    objPlane.initModel("resources/models/plane.obj");
    objCube.initModel("resources/models/cube.obj");

    // Imagenes (texturas)
    // Blocks
    diamondOreEmissiveTex.initTexture("resources/textures/_blocks/diamondOreEmissiveTex.png");
    diamondOreTex.initTexture("resources/textures/_blocks/diamondOreTex.png");
    emeraldOreEmissiveTex.initTexture("resources/textures/_blocks/emeraldOreEmissiveTex.png");
    emeraldOreTex.initTexture("resources/textures/_blocks/emeraldOreTex.png");
    goldOreEmissiveTex.initTexture("resources/textures/_blocks/goldOreEmissiveTex.png");
    goldOreTex.initTexture("resources/textures/_blocks/goldOreTex.png");
    grassBlockTex.initTexture("resources/textures/_blocks/grassBlockTex.png");
    ironOreEmissiveTex.initTexture("resources/textures/_blocks/ironOreEmissiveTex.png");
    ironOreTex.initTexture("resources/textures/_blocks/ironOreTex.png");
    lapisOreEmissiveTex.initTexture("resources/textures/_blocks/lapisOreEmissiveTex.png");
    lapisOreTex.initTexture("resources/textures/_blocks/lapisOreTex.png");
    oakLeavesTex.initTexture("resources/textures/_blocks/oakLeavesTex.png");
    oakLogSideTex.initTexture("resources/textures/_blocks/oakLogSideTex.png");
    oakLogTopTex.initTexture("resources/textures/_blocks/oakLogTopTex.png");
    oakPlanksTex.initTexture("resources/textures/_blocks/oakPlanksTex.jpg");
    stoneBlockTex.initTexture("resources/textures/_blocks/stoneBlockTex.jpg");
    // Effects
    sepiaEffectTex.initTexture("resources/textures/_effects/sepiaEffectTex.png");
    sepiaEffectEmissiveTex.initTexture("resources/textures/_effects/sepiaEffectEmissiveTex.png");
    // Mobs
    creeperEmissiveTex.initTexture("resources/textures/_mobs/creeperEmissiveTex.png");
    creeperTex.initTexture("resources/textures/_mobs/creeperTex.png");
    magmacubeTex.initTexture("resources/textures/_mobs/magmacubeTex.png");
    spiderEmissiveTex.initTexture("resources/textures/_mobs/spiderEmissiveTex.jpeg");
    spiderTex.initTexture("resources/textures/_mobs/spiderTex.png");
    steveEmissiveTex.initTexture("resources/textures/_mobs/steveEmissiveTex.jpeg");
    steveTex.initTexture("resources/textures/_mobs/steveTex.png");
    // General
    noEmissiveTex.initTexture("resources/textures/noEmissiveTex.png");

    // Luz ambiental global
    lightG.ambient = glm::vec3(0.5, 0.5, 0.5);

    // Luces direccionales
    lightD[0].direction = glm::vec3(0.0, -1.0, 0.0);
    lightD[0].ambient = glm::vec3(0.1, 0.1, 0.1);
    lightD[0].diffuse = glm::vec3(0.7, 0.7, 0.7);
    lightD[0].specular = glm::vec3(0.7, 0.7, 0.7);

    // Luces posicionales
    lightP[0].position = glm::vec3(0.0, 3.0, 3.0);
    lightP[0].ambient = glm::vec3(0.2, 0.2, 0.2);
    lightP[0].diffuse = glm::vec3(0.9, 0.9, 0.9);
    lightP[0].specular = glm::vec3(0.9, 0.9, 0.9);
    lightP[0].c0 = 1.00;
    lightP[0].c1 = 0.22;
    lightP[0].c2 = 0.20;

    // Luces focales
    lightF[0].position = glm::vec3(-2.0, 2.0, 5.0);
    lightF[0].direction = glm::vec3(2.0, -2.0, -5.0);
    lightF[0].ambient = glm::vec3(0.2, 0.2, 0.2);
    lightF[0].diffuse = glm::vec3(0.9, 0.9, 0.9);
    lightF[0].specular = glm::vec3(0.9, 0.9, 0.9);
    lightF[0].innerCutOff = 10.0;
    lightF[0].outerCutOff = static_cast<float>(lightF[0].innerCutOff + 5.0);
    lightF[0].c0 = 1.000;
    lightF[0].c1 = 0.090;
    lightF[0].c2 = 0.032;
    lightF[1].position = glm::vec3(2.0, 2.0, 5.0);
    lightF[1].direction = glm::vec3(-2.0, -2.0, -5.0);
    lightF[1].ambient = glm::vec3(0.2, 0.2, 0.2);
    lightF[1].diffuse = glm::vec3(0.9, 0.9, 0.9);
    lightF[1].specular = glm::vec3(0.9, 0.9, 0.9);
    lightF[1].innerCutOff = 5.0;
    lightF[1].outerCutOff = static_cast<float>(lightF[1].innerCutOff + 1.0);
    lightF[1].c0 = 1.000;
    lightF[1].c1 = 0.090;
    lightF[1].c2 = 0.032;

    // Materiales
    mluz.ambient = glm::vec4(0.0, 0.0, 0.0, 1.0);
    mluz.diffuse = glm::vec4(0.0, 0.0, 0.0, 1.0);
    mluz.specular = glm::vec4(0.0, 0.0, 0.0, 1.0);
    mluz.emissive = glm::vec4(1.0, 1.0, 1.0, 1.0);
    mluz.shininess = 1.0;

    // Textures
    // Blocks
    texturesDiamondOre.diffuse = diamondOreTex.getTexture();
    texturesDiamondOre.specular = diamondOreTex.getTexture();
    texturesDiamondOre.emissive = diamondOreEmissiveTex.getTexture();
    texturesDiamondOre.normal = 0;
    texturesDiamondOre.shininess = 10.0;
    texturesEmeraldOre.diffuse = emeraldOreTex.getTexture();
    texturesEmeraldOre.specular = emeraldOreTex.getTexture();
    texturesEmeraldOre.emissive = emeraldOreEmissiveTex.getTexture();
    texturesEmeraldOre.normal = 0;
    texturesEmeraldOre.shininess = 10.0;
    texturesGoldOre.diffuse = goldOreTex.getTexture();
    texturesGoldOre.specular = goldOreTex.getTexture();
    texturesGoldOre.emissive = goldOreEmissiveTex.getTexture();
    texturesGoldOre.normal = 0;
    texturesGoldOre.shininess = 10.0;
    texturesGrassBlock.diffuse = grassBlockTex.getTexture();
    texturesGrassBlock.specular = grassBlockTex.getTexture();
    texturesGrassBlock.emissive = grassBlockTex.getTexture();
    texturesGrassBlock.normal = 0;
    texturesGrassBlock.shininess = 10.0;
    texturesIronOre.diffuse = ironOreTex.getTexture();
    texturesIronOre.specular = ironOreTex.getTexture();
    texturesIronOre.emissive = ironOreEmissiveTex.getTexture();
    texturesIronOre.normal = 0;
    texturesIronOre.shininess = 10.0;
    texturesLapisOre.diffuse = lapisOreTex.getTexture();
    texturesLapisOre.specular = lapisOreTex.getTexture();
    texturesLapisOre.emissive = lapisOreEmissiveTex.getTexture();
    texturesLapisOre.normal = 0;
    texturesLapisOre.shininess = 10.0;
    texturesOakLeaves.diffuse = oakLeavesTex.getTexture();
    texturesOakLeaves.specular = oakLeavesTex.getTexture();
    texturesOakLeaves.emissive = oakLeavesTex.getTexture();
    texturesOakLeaves.normal = 0;
    texturesOakLeaves.shininess = 10.0;
    texturesOakPlanks.diffuse = oakPlanksTex.getTexture();
    texturesOakPlanks.specular = oakPlanksTex.getTexture();
    texturesOakPlanks.emissive = oakPlanksTex.getTexture();
    texturesOakPlanks.normal = 0;
    texturesOakPlanks.shininess = 10.0;
    texturesStoneBlock.diffuse = stoneBlockTex.getTexture();
    texturesStoneBlock.specular = stoneBlockTex.getTexture();
    texturesStoneBlock.emissive = stoneBlockTex.getTexture();
    texturesStoneBlock.normal = 0;
    texturesStoneBlock.shininess = 10.0;
    // Effects
    texturesSepiaEffect.diffuse = sepiaEffectTex.getTexture();
    texturesSepiaEffect.specular = sepiaEffectTex.getTexture();
    texturesSepiaEffect.emissive = sepiaEffectEmissiveTex.getTexture();
    texturesSepiaEffect.normal = 0;
    texturesSepiaEffect.shininess = 10.0;
    // Mobs
    texturesCreeper.diffuse = creeperTex.getTexture();
    texturesCreeper.specular = creeperTex.getTexture();
    texturesCreeper.emissive = creeperEmissiveTex.getTexture();
    texturesCreeper.normal = 0;
    texturesCreeper.shininess = 10.0;
    texturesMagmacube.diffuse = magmacubeTex.getTexture();
    texturesMagmacube.specular = magmacubeTex.getTexture();
    texturesMagmacube.emissive = magmacubeTex.getTexture();
    texturesMagmacube.normal = 0;
    texturesMagmacube.shininess = 10.0;
    texturesSpider.diffuse = spiderTex.getTexture();
    texturesSpider.specular = spiderTex.getTexture();
    texturesSpider.emissive = spiderEmissiveTex.getTexture();
    texturesSpider.normal = 0;
    texturesSpider.shininess = 10.0;
    texturesSteve.diffuse = steveTex.getTexture();
    texturesSteve.specular = steveTex.getTexture();
    texturesSteve.emissive = steveEmissiveTex.getTexture();
    texturesSteve.normal = 0;
    texturesSteve.shininess = 10.0;

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
    drawObjectTex(objCube, texturesStoneBlock, P, V, R1 * S1 * Salto * T);// dibujamos el personaje

    //Dibujamos obstáculo/enemigo
    renderEnemy(45, P, V);

    glm::mat4 S = glm::scale(I, glm::vec3(2));
    drawObjectTex(objSphere, texturesStoneBlock, P, V, S); // dibujamos el planeta

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
        drawObjectMat(objSphere, mluz, P, V, M);
    }

    for (auto &i: lightF) {
        glm::mat4 M = glm::translate(I, i.position) * glm::scale(I, glm::vec3(0.025));
        drawObjectMat(objSphere, mluz, P, V, M);
    }

}

void drawObjectMat(Model &model, Material &material, glm::mat4 P, glm::mat4 V, glm::mat4 M) {

    shaders.setMat4("uN", glm::transpose(glm::inverse(M)));
    shaders.setMat4("uM", M);
    shaders.setMat4("uPVM", P * V * M);
    shaders.setBool("uWithMaterials", true);
    shaders.setMaterial("umaterial", material);
    model.renderModel(GL_FILL);

}

void drawObjectTex(Model &model, Textures &textures, glm::mat4 P, glm::mat4 V, glm::mat4 M) {

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

    drawObjectTex(objCube, texturesStoneBlock, P, V, R * S * T);
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
    drawObjectTex(objCube, texturesStoneBlock, P, V, R1 * S1 * T); // dibujamos el personaje

    // Dibujamos el planeta
    glm::mat4 S = glm::scale(I, glm::vec3(2));
    drawObjectTex(objSphere, texturesStoneBlock, P, V, S);

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
    drawObjectTex(objPlane, texturesSepiaEffect, P, V, sepiaSize * sepiaPos);
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

void initGLFW() {
    // Inicializamos GLFW
    if (!glfwInit()) exit(-1);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}

GLFWwindow *initWindow() {
    // Creamos la ventana
    GLFWwindow *window;
    window = glfwCreateWindow(w, h, "CrocodileGame", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    return window;
}

void initGLEW() {
    // Inicializamos GLEW
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        std::cout << "Error: " << glewGetErrorString(err) << std::endl;
        exit(-1);
    }
    std::cout << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;
    const GLubyte *oglVersion = glGetString(GL_VERSION);
    std::cout << "This system supports OpenGL Version: " << oglVersion << std::endl;
}

std::tuple<FT_Library, FT_Face> initFreetype() {
    FT_Library ft;
    if (FT_Init_FreeType(&ft))
    {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        exit(-1);
    }

    FT_Face face;
    if (FT_New_Face(ft, "resources/fonts/comicsansms.ttf", 0, &face))
    {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
        exit(-1);
    }

    FT_Int major, minor, patch;
    FT_Library_Version(ft, &major, &minor, &patch);
    std::cout << "FreeType Version: " << major << "." << minor << "." << patch << std::endl;
    return std::make_tuple(ft, face);
}

std::tuple<GLFWwindow *, FT_Library, FT_Face> init() {
    initGLFW();
    GLFWwindow *window = initWindow();
    initGLEW();
    auto [ft, face] = initFreetype();
    initScene();
    return std::make_tuple(window, ft, face);
}