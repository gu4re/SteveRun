#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shaders.h"
#include "Model.h"
#include "Texture.h"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

void configScene();
void renderGame(GLFWwindow* window);
void renderMenu(GLFWwindow* window);
void setLights(glm::mat4 P, glm::mat4 V);
void drawObjectMat(Model &model, Material &material, glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawObjectTex(Model &model, Textures &textures, glm::mat4 P, glm::mat4 V, glm::mat4 M);
void renderEnemy(float angle, glm::mat4 P, glm::mat4 V);
void funTimer(double seconds, double &t0);
void reset();
void screenMode(GLFWwindow* window);

void funFramebufferSize(GLFWwindow* window, int width, int height);

void gamefunKey            (GLFWwindow* window, int key  , int scancode, int action, int mods);
void gamefunScroll         (GLFWwindow* window, double xoffset, double yoffset);
void gamefunCursorPos      (GLFWwindow* window, double xpos, double ypos);

void menufunKey            (GLFWwindow* window, int key  , int scancode, int action, int mods);

// Shaders
   Shaders shaders;

// Modelos
   Model sphere;
   Model plane;
   Model cube;

// Imagenes (texturas)
   Texture imgNoEmissive;
   Texture imgRuby;
   Texture imgGold;
   Texture imgEarth;
   Texture imgChess;
   Texture imgCubeDiffuse;
   Texture imgCubeSpecular;
   Texture imgWindow;
   Texture imgWallDiffuse;
   Texture imgWallSpecular;
   Texture imgWallNormal;
   Texture imgSepia;
   Texture imgSepiaEmissive;


// Luces y materiales
   #define   NLD 1
   #define   NLP 1
   #define   NLF 2
   Light     lightG;
   Light     lightD[NLD];
   Light     lightP[NLP];
   Light     lightF[NLF];
   Material  mluz;
   Material  ruby;
   Material  gold;
   Textures  texRuby;
   Textures  texGold;
   Textures  texEarth;
   Textures  texChess;
   Textures  texCube;
   Textures  texWindow;
   Textures  texPlane;
   Textures  texSepia;

// Viewport
   int w = 700;
   int h = 700;
   bool fullscreen_mode = false;

// Animaciones
   float rotP = 0.0;
   float jump = 0.0;
   double last_timer = 0.0;

// Movimiento de camara
   float fovy   = 60.0;
   float alphaX =  0.0;
   float alphaY =  0.0;

// Variables globales para las coordenadas del cubo
    float cubeX = 0.0f;
    float cubeY = 9.0f;
    float cubeZ = 0.0f;

// Variable que indica si el juego está en marcha
    int gameRunning = 0;


// Variable que indica si el personaje está realmente saltando
// (comprueba que la tecla espacio no se haya dejado pulsada continuamente)
    bool isJumping = false;
//  Variable que controla si estamos en el menu
    bool inMainMenu = true;


int main() {

 // Inicializamos GLFW
    if(!glfwInit()) return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

 // Creamos la ventana
    GLFWwindow* window;
    window = glfwCreateWindow(w, h, "CrocodileGame", NULL, NULL);
    if(!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

 // Inicializamos GLEW
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if(GLEW_OK != err) {
        std::cout << "Error: " << glewGetErrorString(err) << std::endl;
        return -1;
    }
    std::cout << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;
    const GLubyte *oglVersion = glGetString(GL_VERSION);
    std::cout <<"This system supports OpenGL Version: " << oglVersion << std::endl;

    // Inicializamos IMGUI
    IMGUI_CHECKVERSION();
    std::cout <<"This system supports ImGui Version: " << ImGui::GetVersion() << std::endl;

    // Entramos en el bucle de renderizado
    configScene();
    double t0 = glfwGetTime();
    double elapsed = 0.0;

    while (!glfwWindowShouldClose(window)) {
        if (inMainMenu) {
            renderMenu(window);
            glfwSwapBuffers(window);
            glfwPollEvents();
        } else {
            double t1 = glfwGetTime();
            double deltaTime = t1 - t0;
            t0 = t1;

            renderGame(window);
            glfwSwapBuffers(window);
            glfwPollEvents();

            // Solo llamamos a funTimer cuando gameRunning es 1
            if (gameRunning == 1) {
                elapsed += deltaTime;
                if (elapsed >= 0.01) {  // Llama a la función funTimer cada 0.01 segundos
                    funTimer(elapsed, t0);
                    elapsed = 0.0;
                }
            }
        }
    }
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

void configScene() {

 // Test de profundidad
    glEnable(GL_DEPTH_TEST);

 // Transparencias
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //esto es el algoritmo que combina los colores de los objetos opacos de en las transparencias

 // Shaders
    shaders.initShaders("resources/shaders/vshader.glsl","resources/shaders/fshader.glsl");

 // Modelos
    sphere.initModel("resources/models/sphere.obj");
    plane.initModel("resources/models/plane.obj");
    cube.initModel("resources/models/cube.obj");

 // Imagenes (texturas)
    imgNoEmissive.initTexture("resources/textures/imgNoEmissive.png");
    imgRuby.initTexture("resources/textures/imgRuby.png");
    imgGold.initTexture("resources/textures/imgGold.png");
    imgEarth.initTexture("resources/textures/imgEarth.png");
    imgChess.initTexture("resources/textures/imgChess.png");
    imgCubeDiffuse.initTexture("resources/textures/imgCubeDiffuse.png");
    imgCubeSpecular.initTexture("resources/textures/imgCubeSpecular.png");
    imgWindow.initTexture("resources/textures/imgWindow.png");
    imgWallDiffuse.initTexture("resources/textures/imgWallDiffuse.png");
    imgWallSpecular.initTexture("resources/textures/imgWallSpecular.png");
    imgWallNormal.initTexture("resources/textures/imgWallNormal.png");
    imgSepia.initTexture("resources/textures/imgSepia.png");
    imgSepiaEmissive.initTexture("resources/textures/imgSepiaEmissive.png");

 // Luz ambiental global
    lightG.ambient = glm::vec3(0.5, 0.5, 0.5);

 // Luces direccionales
    lightD[0].direction = glm::vec3(0.0, -1.0, 0.0);
    lightD[0].ambient   = glm::vec3( 0.1, 0.1, 0.1);
    lightD[0].diffuse   = glm::vec3( 0.7, 0.7, 0.7);
    lightD[0].specular  = glm::vec3( 0.7, 0.7, 0.7);

 // Luces posicionales
    lightP[0].position    = glm::vec3(0.0, 3.0, 3.0);
    lightP[0].ambient     = glm::vec3(0.2, 0.2, 0.2);
    lightP[0].diffuse     = glm::vec3(0.9, 0.9, 0.9);
    lightP[0].specular    = glm::vec3(0.9, 0.9, 0.9);
    lightP[0].c0          = 1.00;
    lightP[0].c1          = 0.22;
    lightP[0].c2          = 0.20;

 // Luces focales
    lightF[0].position    = glm::vec3(-2.0,  2.0,  5.0);
    lightF[0].direction   = glm::vec3( 2.0, -2.0, -5.0);
    lightF[0].ambient     = glm::vec3( 0.2,  0.2,  0.2);
    lightF[0].diffuse     = glm::vec3( 0.9,  0.9,  0.9);
    lightF[0].specular    = glm::vec3( 0.9,  0.9,  0.9);
    lightF[0].innerCutOff = 10.0;
    lightF[0].outerCutOff = lightF[0].innerCutOff + 5.0;
    lightF[0].c0          = 1.000;
    lightF[0].c1          = 0.090;
    lightF[0].c2          = 0.032;
    lightF[1].position    = glm::vec3( 2.0,  2.0,  5.0);
    lightF[1].direction   = glm::vec3(-2.0, -2.0, -5.0);
    lightF[1].ambient     = glm::vec3( 0.2,  0.2,  0.2);
    lightF[1].diffuse     = glm::vec3( 0.9,  0.9,  0.9);
    lightF[1].specular    = glm::vec3( 0.9,  0.9,  0.9);
    lightF[1].innerCutOff = 5.0;
    lightF[1].outerCutOff = lightF[1].innerCutOff + 1.0;
    lightF[1].c0          = 1.000;
    lightF[1].c1          = 0.090;
    lightF[1].c2          = 0.032;

 // Materiales
    mluz.ambient   = glm::vec4(0.0, 0.0, 0.0, 1.0);
    mluz.diffuse   = glm::vec4(0.0, 0.0, 0.0, 1.0);
    mluz.specular  = glm::vec4(0.0, 0.0, 0.0, 1.0);
    mluz.emissive  = glm::vec4(1.0, 1.0, 1.0, 1.0);
    mluz.shininess = 1.0;

    ruby.ambient   = glm::vec4(0.174500, 0.011750, 0.011750, 0.55);
    ruby.diffuse   = glm::vec4(0.614240, 0.041360, 0.041360, 0.55);
    ruby.specular  = glm::vec4(0.727811, 0.626959, 0.626959, 0.55);
    ruby.emissive  = glm::vec4(0.000000, 0.000000, 0.000000, 1.00);
    ruby.shininess = 76.8;

    gold.ambient   = glm::vec4(0.247250, 0.199500, 0.074500, 1.00);
    gold.diffuse   = glm::vec4(0.751640, 0.606480, 0.226480, 1.00);
    gold.specular  = glm::vec4(0.628281, 0.555802, 0.366065, 1.00);
    gold.emissive  = glm::vec4(0.000000, 0.000000, 0.000000, 1.00);
    gold.shininess = 51.2;

    texRuby.diffuse   = imgRuby.getTexture();
    texRuby.specular  = imgRuby.getTexture();
    texRuby.emissive  = imgNoEmissive.getTexture();
    texRuby.normal    = 0;
    texRuby.shininess = 76.8;

    texGold.diffuse   = imgGold.getTexture();
    texGold.specular  = imgGold.getTexture();
    texGold.emissive  = imgNoEmissive.getTexture();
    texGold.normal    = 0;
    texGold.shininess = 51.2;

    texEarth.diffuse   = imgEarth.getTexture();
    texEarth.specular  = imgEarth.getTexture();
    texEarth.emissive  = imgNoEmissive.getTexture();
    texEarth.normal    = 0;
    texEarth.shininess = 10.0;

    texChess.diffuse   = imgChess.getTexture();
    texChess.specular  = imgChess.getTexture();
    texChess.emissive  = imgNoEmissive.getTexture();
    texChess.normal    = 0;
    texChess.shininess = 10.0;

    texCube.diffuse   = imgCubeDiffuse.getTexture(); //la difusa es la textura que va a cubrir el modelo
    texCube.specular  = imgCubeSpecular.getTexture(); // la especular es la que va a determinar el brillo del modelo
    texCube.emissive  = imgNoEmissive.getTexture(); // la emisiva es si va a emitir luz por si solo
    texCube.normal    = 0;
    texCube.shininess = 10.0;

    texWindow.diffuse   = imgWindow.getTexture();
    texWindow.specular  = imgWindow.getTexture();
    texWindow.emissive  = imgWindow.getTexture();
    texWindow.normal    = 0;
    texWindow.shininess = 10.0;

    texPlane.diffuse   = imgGold.getTexture();
    texPlane.specular  = imgWallSpecular.getTexture();
    texPlane.emissive  = imgNoEmissive.getTexture();
    texPlane.normal    = imgWallNormal.getTexture();
    texPlane.shininess = 51.2;

    texSepia.diffuse   = imgSepia.getTexture();
    texSepia.specular  = imgSepia.getTexture();
    texSepia.emissive  = imgSepiaEmissive.getTexture();
    texSepia.normal    = 0;
    texSepia.shininess = 10.0;

}

void renderGame(GLFWwindow* window) {
 // Configuramos los CallBacks
    glfwSetFramebufferSizeCallback(window, funFramebufferSize);
    glfwSetKeyCallback      (window, gamefunKey);
    glfwSetScrollCallback   (window, gamefunScroll);
    glfwSetCursorPosCallback(window, gamefunCursorPos);

 // Borramos el buffer de color
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

 // Indicamos los shaders a utilizar
    shaders.useShaders();

 // Matriz P
    float nplane =  0.1;
    float fplane = 25.0;
    float aspect = (float)w/(float)h;
    glm::mat4 P = glm::perspective(glm::radians(fovy), aspect, nplane, fplane);

 // Matriz V
    float x = 10.0f*glm::cos(glm::radians(alphaY))*glm::sin(glm::radians(alphaX));
    float y = 10.0f*glm::sin(glm::radians(alphaY));
    float z = 10.0f*glm::cos(glm::radians(alphaY))*glm::cos(glm::radians(alphaX));
    glm::vec3 eye   (  x,   y,   z);
    glm::vec3 center(0.0, 5.0,  0.0);
    glm::vec3 up    (0.0, 1.0,  0.0);
    glm::mat4 V = glm::lookAt(eye, center, up);
    shaders.setVec3("ueye",eye);

 // Fijamos las luces
    setLights(P,V);

 // Dibujamos la escena

    glm::mat4 T = glm::translate(I, glm::vec3(cubeX, cubeY, cubeZ));
    glm::mat4 Salto = glm::translate(I, glm::vec3(cubeX, jump, cubeZ));
    glm::mat4 S1 = glm::scale(I, glm::vec3(0.5));
    glm::mat4 R1 = glm::rotate(I, glm::radians(rotP), glm::vec3(1,0, 0));
    drawObjectTex(cube, texRuby, P, V, R1*S1*Salto*T);// dibujamos el personaje

    //Dibujamos obstáculo/enemigo
    renderEnemy(45, P, V);

    // Comparamos los ángulos de rotación del personaje y el enemigo
    if (static_cast<int>(rotP) == 45 && !isJumping) {
        gameRunning = 0;
    }

    glm::mat4 S = glm::scale(I, glm::vec3(2));
    drawObjectTex(sphere, texGold, P, V, S); // dibujamos el planeta

}

void setLights(glm::mat4 P, glm::mat4 V) {

    shaders.setLight("ulightG",lightG);
    for(int i=0; i<NLD; i++) shaders.setLight("ulightD["+toString(i)+"]",lightD[i]);
    for(int i=0; i<NLP; i++) shaders.setLight("ulightP["+toString(i)+"]",lightP[i]);
    for(int i=0; i<NLF; i++) shaders.setLight("ulightF["+toString(i)+"]",lightF[i]);

    for(int i=0; i<NLP; i++) {
        glm::mat4 M = glm::translate(I,lightP[i].position) * glm::scale(I,glm::vec3(0.1));
        drawObjectMat(sphere, mluz, P, V, M);
    }

    for(int i=0; i<NLF; i++) {
        glm::mat4 M = glm::translate(I,lightF[i].position) * glm::scale(I,glm::vec3(0.025));
        drawObjectMat(sphere, mluz, P, V, M);
    }

}

void drawObjectMat(Model &model, Material &material, glm::mat4 P, glm::mat4 V, glm::mat4 M) {

    shaders.setMat4("uN"  ,glm::transpose(glm::inverse(M)));
    shaders.setMat4("uM"  ,M);
    shaders.setMat4("uPVM",P*V*M);
    shaders.setBool("uWithMaterials",true);
    shaders.setMaterial("umaterial",material);
    model.renderModel(GL_FILL);

}

void drawObjectTex(Model &model, Textures &textures, glm::mat4 P, glm::mat4 V, glm::mat4 M) {

    shaders.setMat4("uN"  ,glm::transpose(glm::inverse(M)));
    shaders.setMat4("uM"  ,M);
    shaders.setMat4("uPVM",P*V*M);
    shaders.setBool("uWithMaterials",false);
    shaders.setTextures("utextures",textures);
    if(textures.normal!=0) shaders.setBool("uWithNormals",true);
    else                   shaders.setBool("uWithNormals",false);
    model.renderModel(GL_FILL);

}

void funFramebufferSize(GLFWwindow* window, int width, int height) {

 // Configuracion del Viewport
    glViewport(0, 0, width, height);

 // Actualizacion de w y h
    w = width;
    h = height;

}

void gamefunKey(GLFWwindow* window, int key  , int scancode, int action, int mods) {

    switch(key) {
        case GLFW_KEY_UP:
            rotP += 5.0f;
            //Imprime las coordenadas del cubo
            //std::cout << "Tecla de flecha arriba - Coordenadas del cubo: (" << cubeX << ", " << cubeY << ", " << cubeZ << ")" << std::endl;
            break;
        case GLFW_KEY_R:
            if (action == GLFW_PRESS) {
                gameRunning = 0;
                reset();
            }
            break;
        case GLFW_KEY_S:
            if (action == GLFW_PRESS) {
                gameRunning = 0;
            }
            break;
        case GLFW_KEY_SPACE:
            if (action == GLFW_PRESS) {
                if(gameRunning == 0) {
                    reset();
                }
                isJumping = true;
                gameRunning = 1;
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
    }

}

void gamefunScroll(GLFWwindow* window, double xoffset, double yoffset) {

    if(yoffset>0) fovy -= fovy>10.0f ? 5.0f : 0.0f;
    if(yoffset<0) fovy += fovy<90.0f ? 5.0f : 0.0f;

}

void gamefunCursorPos(GLFWwindow* window, double xpos, double ypos) {

    if(glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_LEFT)==GLFW_RELEASE) return;

    float limY = 89.0;
    alphaX = 90.0*(2.0*xpos/(float)w - 1.0);
    alphaY = 90.0*(1.0 - 2.0*ypos/(float)h);
    if(alphaY<-limY) alphaY = -limY;
    if(alphaY> limY) alphaY =  limY;

}

void renderEnemy(float angle, glm::mat4 P, glm::mat4 V) {
    glm::mat4 S = glm::scale(I, glm::vec3(0.30));
    glm::mat4 T = glm::translate(I, glm::vec3(0, 14.42, 0));
    glm::mat4 R = glm::rotate(I, glm::radians(angle), glm::vec3(1,0, 0));

    drawObjectTex(cube, texRuby, P, V, R*S*T);
}

void funTimer(double seconds, double &t0) { //se encarga de la rotacion automatica del personaje
    double t1 = glfwGetTime();
    if (t1 - t0 > seconds) {
        rotP += 5.0f;
        rotP = glm::mod(rotP, 360.0f);  // Asegurar que el ángulo esté en el rango [0, 359]
        t0 = t1;
    }
}


void reset() {
    cubeX = 0.0;
    cubeZ = 0.0;
    cubeY = 9.0;
    rotP = 0.0;
}

void screenMode(GLFWwindow* window) {
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
        std::cout << videoMode->width << std::endl;
        glfwSetWindowMonitor(window, nullptr, (videoMode->width / 2) - 700,
                             (videoMode->height / 2) - 700,700, 700,
                             videoMode->refreshRate);
    }
}

void renderMenu(GLFWwindow* window) {
    // Configuramos los CallBacks
    glfwSetFramebufferSizeCallback(window, funFramebufferSize);
    glfwSetKeyCallback      (window, menufunKey);
    glfwSetScrollCallback   (window, nullptr);
    glfwSetCursorPosCallback(window, nullptr);

    // Borramos el buffer de color
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Indicamos los shaders a utilizar
    shaders.useShaders();

    // Matriz P
    float nplane =  0.1;
    float fplane = 25.0;
    float aspect = (float)w/(float)h;
    // Custom fovy
    fovy = 45;
    glm::mat4 P = glm::perspective(glm::radians(fovy), aspect, nplane, fplane);

    // Matriz V
    glm::vec3 eye   (10.0,5.0,20.0);
    glm::vec3 center(0.0,0.0,0.0);
    glm::vec3 up    (0.0,1.0,0.0);
    glm::mat4 V = glm::lookAt(eye, center, up);
    shaders.setVec3("ueye",eye);

    // Fijamos las luces
    setLights(P,V);

    // Dibujamos el personaje
    // Control de la rotacion automatica del personaje
    auto currentTime = glfwGetTime();
    double deltaTime = currentTime - last_timer;
    // Check if the threshold is passed
    if (deltaTime >= 0.019){
        last_timer = currentTime;
        rotP += 2.0;
        // Ensuring that the angle is always less than 360º
        rotP = fmod(rotP, 360.0);
    }
    // Cubo
    glm::mat4 T = glm::translate(I, glm::vec3(cubeX, cubeY, cubeZ));
    glm::mat4 S1 = glm::scale(I, glm::vec3(0.5));
    glm::mat4 R1 = glm::rotate(I, glm::radians(rotP), glm::vec3(1,0, 0));
    drawObjectTex(cube, texRuby, P, V, R1*S1*T); // dibujamos el personaje

    // Dibujamos el planeta
    glm::mat4 S = glm::scale(I, glm::vec3(2));
    drawObjectTex(sphere, texGold, P, V, S);

    // Efecto sepia al menu
    glm::mat4 sepiaSize = glm::scale(I, glm::vec3(20));
    glm::mat4 sepiaPos = glm::rotate(
            glm::rotate(
                    glm::translate(I, glm::vec3(0.4, 0.1, 0.8)),
                    glm::radians(25.0f), glm::vec3(0, 1, 0)
                    ),
                    glm::radians(90.0f), glm::vec3(1,0, 0)
            );
    glDepthMask(GL_FALSE);
        drawObjectTex(plane, texSepia, P, V, sepiaSize*sepiaPos);
    glDepthMask(GL_TRUE);

}

void menufunKey(GLFWwindow* window, int key, int scancode, int action, int mods) {
    switch(key) {
        case GLFW_KEY_ENTER:
            if (action == GLFW_PRESS) {
                inMainMenu = false;
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
    }
}