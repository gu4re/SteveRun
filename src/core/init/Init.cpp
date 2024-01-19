//
// Created by diegopicazo on 13/1/24.
//

#include "../../../include/core/init/Init.h"

void initScene();
void initGLFW();
GLFWwindow* initWindow();
void initGLEW();
std::tuple<FT_Library, FT_Face> initFreetype();
std::tuple<ALCdevice*, ALCcontext*, ALuint, ALuint> initOpenAL();

std::tuple<GLFWwindow *, FT_Library, FT_Face, ALCdevice*, ALCcontext*, ALuint, ALuint> init() {
    initGLFW();
    GLFWwindow *window = initWindow();
    initGLEW();
    auto [ft, face] = initFreetype();
    auto [SoundDevice, SoundContext, SoundSource, SoundBuffer] = initOpenAL();

    initScene();
    return std::make_tuple(window, ft, face, SoundDevice, SoundContext, SoundSource, SoundBuffer);
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
    modelGrassBlock.initModel("resources/models/_blocks/grassBlock.obj");
    modelIronOre.initModel("resources/models/_blocks/ironOre.obj");
    modelSlab.initModel("resources/models/_blocks/slab.obj");
    modelEmeraldOre.initModel("resources/models/_blocks/emeraldOre.obj");
    modelGoldOre.initModel("resources/models/_blocks/goldOre.obj");
    modelLapisOre.initModel("resources/models/_blocks/lapisOre.obj");
    // Mobs
    modelCreeper.initModel("resources/models/_mobs/creeper.obj");
    modelMagmacube.initModel("resources/models/_mobs/magmacube.obj");
    modelSpider.initModel("resources/models/_mobs/spider.obj");
    modelSteve.initModel("resources/models/_mobs/steve.obj");
    modelPig.initModel("resources/models/_mobs/pig.obj");
    // General
    modelSphere.initModel("resources/models/sphere.obj");
    modelPlane.initModel("resources/models/plane.obj");
    modelCube.initModel("resources/models/cube.obj");
    // Inicializamos el array random de modelos
    modelsRandomArray[0] = modelDiamondOre;
    modelsRandomArray[1] = modelEmeraldOre;
    modelsRandomArray[2] = modelGoldOre;
    modelsRandomArray[3] = modelGrassBlock;
    modelsRandomArray[4] = modelIronOre;
    modelsRandomArray[5] = modelLapisOre;
    // Imagenes (texturas)
    // Blocks
    diamondOreTexRes.initTexture("resources/textures/_blocks/diamondOreTexRes.png");
    grassBlockTexRes.initTexture("resources/textures/_blocks/grassBlockTexRes.png");
    ironOreEmissiveTexRes.initTexture("resources/textures/_blocks/ironOreEmissiveTexRes.png");
    ironOreTexRes.initTexture("resources/textures/_blocks/ironOreTexRes.png");
    oakLeavesTexRes.initTexture("resources/textures/_blocks/oakLeavesTexRes.png");
    oakLogSideTexRes.initTexture("resources/textures/_blocks/oakLogSideTexRes.png");
    oakLogTopTexRes.initTexture("resources/textures/_blocks/oakLogTopTexRes.png");
    oakPlanksTexRes.initTexture("resources/textures/_blocks/oakPlanksTexRes.jpg");
    stoneBlockTexRes.initTexture("resources/textures/_blocks/stoneBlockTexRes.jpg");
    birchLogTopTexRes.initTexture("resources/textures/_blocks/birchLogTopTexRes.png");
    birchLogSideTexRes.initTexture("resources/textures/_blocks/birchLogSideTexRes.png");
    birchLeavesTexRes.initTexture("resources/textures/_blocks/birchLeavesTexRes.png");
    dirtBlockTexRes.initTexture("resources/textures/_blocks/dirtBlockTexRes.png");
    orangeBlockTexRes.initTexture("resources/textures/_blocks/orangeBlockTexRes.png");
    emeraldOreTexRes.initTexture("resources/textures/_blocks/emeraldOreTexRes.png");
    goldOreTexRes.initTexture("resources/textures/_blocks/goldOreTexRes.png");
    lapisOreTexRes.initTexture("resources/textures/_blocks/lapisOreTexRes.png");
    // Effects
    sepiaEffectTexRes.initTexture("resources/textures/_effects/sepiaEffectTexRes.png");
    sepiaEffectEmissiveTexRes.initTexture("resources/textures/_effects/sepiaEffectEmissiveTexRes.png");
    // Mobs
    creeperTexRes.initTexture("resources/textures/_mobs/creeperTexRes.png");
    magmacubeTexRes.initTexture("resources/textures/_mobs/magmacubeTexRes.png");
    spiderTexRes.initTexture("resources/textures/_mobs/spiderTexRes.png");
    steveTexRes.initTexture("resources/textures/_mobs/steveTexRes.png");
    pigTexRes.initTexture("resources/textures/_mobs/pigTexRes.png");
    // General
    noEmissiveTexRes.initTexture("resources/textures/noEmissiveTexRes.png");
    gameTitleTexRes.initTexture("resources/textures/gameTitleTexRes.png");
    gameSubtitleTexRes.initTexture("resources/textures/gameSubtitleTexRes.png");

    // Luz ambiental global
    lightG.ambient = glm::vec3(0.9, 0.9, 0.9);

    // Luces posicionales
    for(auto & i : lightF) {
        // Luces posicionales
        i.position = glm::vec3(-0.1, 5.3, -0.25);
        i.direction = glm::vec3(0, -60.0, 2.5);
        i.ambient   = glm::vec3( 0.2, 0.2, 0.2);
        i.diffuse   = glm::vec3( 0.9, 0.9, 0.9);
        i.specular  = glm::vec3( 0.9, 0.9, 0.9);
        i.innerCutOff = 40.0;
        i.outerCutOff = static_cast<float>(lightF[0].innerCutOff + 3.0);
        i.c0        = 1.000;
        i.c1        = 0.090;
        i.c2        = 0.032;
    }
    // Posiciones de las luces de las antorchas
    lightF[0].position = glm::rotate(I, glm::radians(45.0f), glm::vec3(0.0, 1.0, 0.0)) *
                         glm::rotate(I, glm::radians(85.0f), glm::vec3(1.0, 0.0, 0.0)) *
                         glm::vec4(lightF[0].position, 1);
    lightF[0].direction = glm::rotate(I, glm::radians(45.0f), glm::vec3(0.0, 1.0, 0.0)) *
                          glm::rotate(I, glm::radians(85.0f), glm::vec3(1.0, 0.0, 0.0)) *
                          glm::vec4(lightF[0].direction, 1);
    lightF[1].position = glm::rotate(I, glm::radians(-45.0f), glm::vec3(0.0, 1.0, 0.0)) *
                         glm::rotate(I, glm::radians(85.0f), glm::vec3(1.0, 0.0, 0.0)) *
                         glm::vec4(lightF[1].position, 1);
    lightF[1].direction = glm::rotate(I, glm::radians(-45.0f), glm::vec3(0.0, 1.0, 0.0)) *
                          glm::rotate(I, glm::radians(85.0f), glm::vec3(1.0, 0.0, 0.0)) *
                          glm::vec4(lightF[1].direction, 1);
    lightF[2].position = glm::rotate(I, glm::radians(45.0f), glm::vec3(0.0, 1.0, 0.0)) *
                         glm::rotate(I, glm::radians(135.0f), glm::vec3(1.0, 0.0, 0.0)) *
                         glm::vec4(lightF[2].position, 1);
    lightF[2].direction = glm::rotate(I, glm::radians(45.0f), glm::vec3(0.0, 1.0, 0.0)) *
                          glm::rotate(I, glm::radians(135.0f), glm::vec3(1.0, 0.0, 0.0)) *
                          glm::vec4(lightF[2].direction, 1);
    lightF[3].position = glm::rotate(I, glm::radians(135.0f), glm::vec3(0.0, 1.0, 0.0)) *
                         glm::rotate(I, glm::radians(135.0f), glm::vec3(1.0, 0.0, 0.0)) *
                         glm::vec4(lightF[3].position, 1);
    lightF[3].direction = glm::rotate(I, glm::radians(135.0f), glm::vec3(0.0, 1.0, 0.0)) *
                          glm::rotate(I, glm::radians(135.0f), glm::vec3(1.0, 0.0, 0.0)) *
                          glm::vec4(lightF[3].direction, 1);
    lightF[4].position = glm::rotate(I, glm::radians(115.0f), glm::vec3(0.0, 1.0, 0.0)) *
                         glm::rotate(I, glm::radians(100.0f), glm::vec3(1.0, 0.0, 0.0)) *
                         glm::vec4(lightF[4].position, 1);
    lightF[4].direction = glm::rotate(I, glm::radians(115.0f), glm::vec3(0.0, 1.0, 0.0)) *
                          glm::rotate(I, glm::radians(100.0f), glm::vec3(1.0, 0.0, 0.0)) *
                          glm::vec4(lightF[4].direction, 1);
    lightF[5].position = glm::rotate(I, glm::radians(195.0f), glm::vec3(0.0, 1.0, 0.0)) *
                         glm::rotate(I, glm::radians(85.0f), glm::vec3(1.0, 0.0, 0.0)) *
                         glm::vec4(lightF[5].position, 1);
    lightF[5].direction = glm::rotate(I, glm::radians(195.0f), glm::vec3(0.0, 1.0, 0.0)) *
                          glm::rotate(I, glm::radians(85.0f), glm::vec3(1.0, 0.0, 0.0)) *
                          glm::vec4(lightF[5].direction, 1);

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
    texturesDiamondOre.emissive = diamondOreTexRes.getTexture();
    texturesDiamondOre.normal = 0;
    texturesDiamondOre.shininess = 10.0;
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
    texturesOakLogSide.diffuse = oakLogSideTexRes.getTexture();
    texturesOakLogSide.specular = oakLogSideTexRes.getTexture();
    texturesOakLogSide.emissive = oakLogSideTexRes.getTexture();
    texturesOakLogSide.normal = 0;
    texturesOakLogSide.shininess = 10.0;
    texturesOakLogTop.diffuse = oakLogTopTexRes.getTexture();
    texturesOakLogTop.specular = oakLogTopTexRes.getTexture();
    texturesOakLogTop.emissive = oakLogTopTexRes.getTexture();
    texturesOakLogTop.normal = 0;
    texturesOakLogTop.shininess = 10.0;
    texturesStoneBlock.diffuse = stoneBlockTexRes.getTexture();
    texturesStoneBlock.specular = stoneBlockTexRes.getTexture();
    texturesStoneBlock.emissive = stoneBlockTexRes.getTexture();
    texturesStoneBlock.normal = 0;
    texturesStoneBlock.shininess = 10.0;
    texturesBirchLogSide.diffuse = birchLogSideTexRes.getTexture();
    texturesBirchLogSide.specular = birchLogSideTexRes.getTexture();
    texturesBirchLogSide.emissive = birchLogSideTexRes.getTexture();
    texturesBirchLogSide.normal = 0;
    texturesBirchLogSide.shininess = 10.0;
    texturesBirchLogTop.diffuse = birchLogTopTexRes.getTexture();
    texturesBirchLogTop.specular = birchLogTopTexRes.getTexture();
    texturesBirchLogTop.emissive = birchLogTopTexRes.getTexture();
    texturesBirchLogTop.normal = 0;
    texturesBirchLogTop.shininess = 10.0;
    texturesBirchLeaves.diffuse = birchLeavesTexRes.getTexture();
    texturesBirchLeaves.specular = birchLeavesTexRes.getTexture();
    texturesBirchLeaves.emissive = birchLeavesTexRes.getTexture();
    texturesBirchLeaves.normal = 0;
    texturesBirchLeaves.shininess = 10.0;
    texturesDirtBlock.diffuse = dirtBlockTexRes.getTexture();
    texturesDirtBlock.specular = dirtBlockTexRes.getTexture();
    texturesDirtBlock.emissive = dirtBlockTexRes.getTexture();
    texturesDirtBlock.normal = 0;
    texturesDirtBlock.shininess = 10.0;
    texturesOrangeBlock.diffuse = orangeBlockTexRes.getTexture();
    texturesOrangeBlock.specular = orangeBlockTexRes.getTexture();
    texturesOrangeBlock.emissive = orangeBlockTexRes.getTexture();
    texturesOrangeBlock.normal = 0;
    texturesOrangeBlock.shininess = 10.0;
    texturesEmeraldOre.diffuse = emeraldOreTexRes.getTexture();
    texturesEmeraldOre.specular = emeraldOreTexRes.getTexture();
    texturesEmeraldOre.emissive = emeraldOreTexRes.getTexture();
    texturesEmeraldOre.normal = 0;
    texturesEmeraldOre.shininess = 10.0;
    texturesGoldOre.diffuse = goldOreTexRes.getTexture();
    texturesGoldOre.specular = goldOreTexRes.getTexture();
    texturesGoldOre.emissive = goldOreTexRes.getTexture();
    texturesGoldOre.normal = 0;
    texturesGoldOre.shininess = 10.0;
    texturesLapisOre.diffuse = lapisOreTexRes.getTexture();
    texturesLapisOre.specular = lapisOreTexRes.getTexture();
    texturesLapisOre.emissive = lapisOreTexRes.getTexture();
    texturesLapisOre.normal = 0;
    texturesLapisOre.shininess = 10.0;
    // Effects
    texturesSepiaEffect.diffuse = sepiaEffectTexRes.getTexture();
    texturesSepiaEffect.specular = sepiaEffectTexRes.getTexture();
    texturesSepiaEffect.emissive = sepiaEffectEmissiveTexRes.getTexture();
    texturesSepiaEffect.normal = 0;
    texturesSepiaEffect.shininess = 10.0;
    // Mobs
    texturesCreeper.diffuse = creeperTexRes.getTexture();
    texturesCreeper.specular = creeperTexRes.getTexture();
    texturesCreeper.emissive = creeperTexRes.getTexture();
    texturesCreeper.normal = 0;
    texturesCreeper.shininess = 10.0;
    texturesMagmacube.diffuse = magmacubeTexRes.getTexture();
    texturesMagmacube.specular = magmacubeTexRes.getTexture();
    texturesMagmacube.emissive = magmacubeTexRes.getTexture();
    texturesMagmacube.normal = 0;
    texturesMagmacube.shininess = 10.0;
    texturesSpider.diffuse = spiderTexRes.getTexture();
    texturesSpider.specular = spiderTexRes.getTexture();
    texturesSpider.emissive = spiderTexRes.getTexture();
    texturesSpider.normal = 0;
    texturesSpider.shininess = 10.0;
    texturesSteve.diffuse = steveTexRes.getTexture();
    texturesSteve.specular = steveTexRes.getTexture();
    texturesSteve.emissive = steveTexRes.getTexture();
    texturesSteve.normal = 0;
    texturesSteve.shininess = 10.0;
    texturesPig.diffuse = pigTexRes.getTexture();
    texturesPig.specular = pigTexRes.getTexture();
    texturesPig.emissive = pigTexRes.getTexture();
    texturesPig.normal = 0;
    texturesPig.shininess = 10.0;
    // General
    texturesGameTitle.diffuse = gameTitleTexRes.getTexture();
    texturesGameTitle.specular = gameTitleTexRes.getTexture();
    texturesGameTitle.emissive = gameTitleTexRes.getTexture();
    texturesGameTitle.normal = 0;
    texturesGameTitle.shininess = 10.0;
    texturesGameSubtitle.diffuse = gameSubtitleTexRes.getTexture();
    texturesGameSubtitle.specular = gameSubtitleTexRes.getTexture();
    texturesGameSubtitle.emissive = gameSubtitleTexRes.getTexture();
    texturesGameSubtitle.normal = 0;
    texturesGameSubtitle.shininess = 10.0;
    // Inicializamos el array random de texturas
    texturesRandomArray[0] = texturesDiamondOre;
    texturesRandomArray[1] = texturesEmeraldOre;
    texturesRandomArray[2] = texturesGoldOre;
    texturesRandomArray[3] = texturesGrassBlock;
    texturesRandomArray[4] = texturesIronOre;
    texturesRandomArray[5] = texturesLapisOre;
    texturesRandomArray[6] = texturesOakLeaves;
    texturesRandomArray[7] = texturesOakPlanks;
    texturesRandomArray[8] = texturesStoneBlock;

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

// Función para inicializar OpenAL y cargar el archivo de audio
std::tuple<ALCdevice*, ALCcontext*, ALuint, ALuint> initOpenAL() {
    ALCdevice* device = alcOpenDevice(nullptr);
    if (!device) {
        std::cerr << "Error al abrir el dispositivo de audio" << std::endl;
        exit(-1);
    }

    ALCcontext* context = alcCreateContext(device, nullptr);
    alcMakeContextCurrent(context);

    ALuint source, buffer;
    alGenBuffers(1, &buffer);
    alGenSources(1, &source);

    // Cargar archivo de audio usando libsndfile
    SF_INFO sndInfo;
    SNDFILE* sndFile = sf_open("resources/music/c418Venus.wav", SFM_READ, &sndInfo);
    if (!sndFile) {
        std::cerr << "Error al abrir el archivo de audio" << std::endl;
        exit(-1);
    }

    ALenum format;
    if (sndInfo.channels == 1) {
        format = AL_FORMAT_MONO16;
    } else if (sndInfo.channels == 2) {
        format = AL_FORMAT_STEREO16;
    } else {
        std::cerr << "Número de canales no soportado" << std::endl;
        sf_close(sndFile);
        exit(-1);
    }

    auto size = static_cast<ALsizei>(sndInfo.frames * sndInfo.channels);
    auto freq = static_cast<ALsizei>(sndInfo.samplerate);

    std::vector<ALshort> samples(size);
    sf_read_short(sndFile, samples.data(), size);
    sf_close(sndFile);

    alBufferData(buffer, format, samples.data(), static_cast<ALsizei>(size * sizeof(ALshort)), freq);
    alSourcei(source, AL_BUFFER, static_cast<ALint>(buffer));

    return std::make_tuple(device, context, source, buffer);
}
