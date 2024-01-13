//
// Created by diegopicazo on 13/1/24.
//

#include "Init.h"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../shaders/Shaders.h"
#include "../textures/TexturesResources.h"
#include "../textures/Textures.h"
#include <ft2build.h>
#include FT_FREETYPE_H
#include "../models/Models.h"
#include "../lights/Lights.h"

void initScene();
void initGLFW();
GLFWwindow* initWindow();
void initGLEW();
std::tuple<FT_Library, FT_Face> initFreetype();

std::tuple<GLFWwindow *, FT_Library, FT_Face> init() {
    initGLFW();
    GLFWwindow *window = initWindow();
    initGLEW();
    auto [ft, face] = initFreetype();
    initScene();
    return std::make_tuple(window, ft, face);
}

void initScene() {

    // Test de profundidad
    glEnable(GL_DEPTH_TEST);

    // Transparencias
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,
                GL_ONE_MINUS_SRC_ALPHA); //esto es el algoritmo que combina los colores de los objetos opacos de en las transparencias

    // ShadersManager
    shaders.initShaders("resources/shaders/vshader.glsl",
                        "resources/shaders/fshader.glsl");

    // Modelos
    // Blocks
    modelDiamondOre.initModel("resources/models/_blocks/diamondOre.obj");
    modelEmeraldOre.initModel("resources/models/_blocks/emeraldOre.obj");
    modelGoldOre.initModel("resources/models/_blocks/goldOre.obj");
    modelGrassBlock.initModel("resources/models/_blocks/grassBlock.obj");
    modelIronOre.initModel("resources/models/_blocks/ironOre.obj");
    modelLapisOre.initModel("resources/models/_blocks/lapisOre.obj");
    // Mobs
    modelCreeper.initModel("resources/models/_mobs/creeper.obj");
    modelMagmacube.initModel("resources/models/_mobs/magmacube.obj");
    modelSpider.initModel("resources/models/_mobs/spider.obj");
    modelSteve.initModel("resources/models/_mobs/steve.obj");
    // General
    modelSphere.initModel("resources/models/sphere.obj");
    modelPlane.initModel("resources/models/plane.obj");
    modelCube.initModel("resources/models/cube.obj");

    // Imagenes (texturas)
    // Blocks
    diamondOreEmissiveTexRes.initTexture("resources/textures/_blocks/diamondOreEmissiveTexRes.png");
    diamondOreTexRes.initTexture("resources/textures/_blocks/diamondOreTexRes.png");
    emeraldOreEmissiveTexRes.initTexture("resources/textures/_blocks/emeraldOreEmissiveTexRes.png");
    emeraldOreTexRes.initTexture("resources/textures/_blocks/emeraldOreTexRes.png");
    goldOreEmissiveTexRes.initTexture("resources/textures/_blocks/goldOreEmissiveTexRes.png");
    goldOreTexRes.initTexture("resources/textures/_blocks/goldOreTexRes.png");
    grassBlockTexRes.initTexture("resources/textures/_blocks/grassBlockTexRes.png");
    ironOreEmissiveTexRes.initTexture("resources/textures/_blocks/ironOreEmissiveTexRes.png");
    ironOreTexRes.initTexture("resources/textures/_blocks/ironOreTexRes.png");
    lapisOreEmissiveTexRes.initTexture("resources/textures/_blocks/lapisOreEmissiveTexRes.png");
    lapisOreTexRes.initTexture("resources/textures/_blocks/lapisOreTexRes.png");
    oakLeavesTexRes.initTexture("resources/textures/_blocks/oakLeavesTexRes.png");
    oakLogSideTexRes.initTexture("resources/textures/_blocks/oakLogSideTexRes.png");
    oakLogTopTexRes.initTexture("resources/textures/_blocks/oakLogTopTexRes.png");
    oakPlanksTexRes.initTexture("resources/textures/_blocks/oakPlanksTexRes.jpg");
    stoneBlockTexRes.initTexture("resources/textures/_blocks/stoneBlockTexRes.jpg");
    // Effects
    sepiaEffectTexRes.initTexture("resources/textures/_effects/sepiaEffectTexRes.png");
    sepiaEffectEmissiveTexRes.initTexture("resources/textures/_effects/sepiaEffectEmissiveTexRes.png");
    // Mobs
    creeperEmissiveTexRes.initTexture("resources/textures/_mobs/creeperEmissiveTexRes.png");
    creeperTexRes.initTexture("resources/textures/_mobs/creeperTexRes.png");
    magmacubeTexRes.initTexture("resources/textures/_mobs/magmacubeTexRes.png");
    spiderEmissiveTexRes.initTexture("resources/textures/_mobs/spiderEmissiveTexRes.jpeg");
    spiderTexRes.initTexture("resources/textures/_mobs/spiderTexRes.png");
    steveEmissiveTexRes.initTexture("resources/textures/_mobs/steveEmissiveTexRes.jpeg");
    steveTexRes.initTexture("resources/textures/_mobs/steveTexRes.png");
    // General
    noEmissiveTexRes.initTexture("resources/textures/noEmissiveTexRes.png");

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
    texturesDiamondOre.diffuse = diamondOreTexRes.getTexture();
    texturesDiamondOre.specular = diamondOreTexRes.getTexture();
    texturesDiamondOre.emissive = diamondOreEmissiveTexRes.getTexture();
    texturesDiamondOre.normal = 0;
    texturesDiamondOre.shininess = 10.0;
    texturesEmeraldOre.diffuse = emeraldOreTexRes.getTexture();
    texturesEmeraldOre.specular = emeraldOreTexRes.getTexture();
    texturesEmeraldOre.emissive = emeraldOreEmissiveTexRes.getTexture();
    texturesEmeraldOre.normal = 0;
    texturesEmeraldOre.shininess = 10.0;
    texturesGoldOre.diffuse = goldOreTexRes.getTexture();
    texturesGoldOre.specular = goldOreTexRes.getTexture();
    texturesGoldOre.emissive = goldOreEmissiveTexRes.getTexture();
    texturesGoldOre.normal = 0;
    texturesGoldOre.shininess = 10.0;
    texturesGrassBlock.diffuse = grassBlockTexRes.getTexture();
    texturesGrassBlock.specular = grassBlockTexRes.getTexture();
    texturesGrassBlock.emissive = grassBlockTexRes.getTexture();
    texturesGrassBlock.normal = 0;
    texturesGrassBlock.shininess = 10.0;
    texturesIronOre.diffuse = ironOreTexRes.getTexture();
    texturesIronOre.specular = ironOreTexRes.getTexture();
    texturesIronOre.emissive = ironOreEmissiveTexRes.getTexture();
    texturesIronOre.normal = 0;
    texturesIronOre.shininess = 10.0;
    texturesLapisOre.diffuse = lapisOreTexRes.getTexture();
    texturesLapisOre.specular = lapisOreTexRes.getTexture();
    texturesLapisOre.emissive = lapisOreEmissiveTexRes.getTexture();
    texturesLapisOre.normal = 0;
    texturesLapisOre.shininess = 10.0;
    texturesOakLeaves.diffuse = oakLeavesTexRes.getTexture();
    texturesOakLeaves.specular = oakLeavesTexRes.getTexture();
    texturesOakLeaves.emissive = oakLeavesTexRes.getTexture();
    texturesOakLeaves.normal = 0;
    texturesOakLeaves.shininess = 10.0;
    texturesOakPlanks.diffuse = oakPlanksTexRes.getTexture();
    texturesOakPlanks.specular = oakPlanksTexRes.getTexture();
    texturesOakPlanks.emissive = oakPlanksTexRes.getTexture();
    texturesOakPlanks.normal = 0;
    texturesOakPlanks.shininess = 10.0;
    texturesStoneBlock.diffuse = stoneBlockTexRes.getTexture();
    texturesStoneBlock.specular = stoneBlockTexRes.getTexture();
    texturesStoneBlock.emissive = stoneBlockTexRes.getTexture();
    texturesStoneBlock.normal = 0;
    texturesStoneBlock.shininess = 10.0;
    // Effects
    texturesSepiaEffect.diffuse = sepiaEffectTexRes.getTexture();
    texturesSepiaEffect.specular = sepiaEffectTexRes.getTexture();
    texturesSepiaEffect.emissive = sepiaEffectEmissiveTexRes.getTexture();
    texturesSepiaEffect.normal = 0;
    texturesSepiaEffect.shininess = 10.0;
    // Mobs
    texturesCreeper.diffuse = creeperTexRes.getTexture();
    texturesCreeper.specular = creeperTexRes.getTexture();
    texturesCreeper.emissive = creeperEmissiveTexRes.getTexture();
    texturesCreeper.normal = 0;
    texturesCreeper.shininess = 10.0;
    texturesMagmacube.diffuse = magmacubeTexRes.getTexture();
    texturesMagmacube.specular = magmacubeTexRes.getTexture();
    texturesMagmacube.emissive = magmacubeTexRes.getTexture();
    texturesMagmacube.normal = 0;
    texturesMagmacube.shininess = 10.0;
    texturesSpider.diffuse = spiderTexRes.getTexture();
    texturesSpider.specular = spiderTexRes.getTexture();
    texturesSpider.emissive = spiderEmissiveTexRes.getTexture();
    texturesSpider.normal = 0;
    texturesSpider.shininess = 10.0;
    texturesSteve.diffuse = steveTexRes.getTexture();
    texturesSteve.specular = steveTexRes.getTexture();
    texturesSteve.emissive = steveEmissiveTexRes.getTexture();
    texturesSteve.normal = 0;
    texturesSteve.shininess = 10.0;

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
    window = glfwCreateWindow(700, 700, "SteveRun", nullptr, nullptr);
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
    if (FT_New_Face(ft, "resources/fonts/minecraftfont.otf", 0, &face))
    {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
        exit(-1);
    }

    FT_Int major, minor, patch;
    FT_Library_Version(ft, &major, &minor, &patch);
    std::cout << "FreeType Version: " << major << "." << minor << "." << patch << std::endl;
    return std::make_tuple(ft, face);
}
