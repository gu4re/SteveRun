#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shaders.h"
#include "Model.h"

// Global Shaders
Shaders shaders;
// Global Models
Model triangle;

void configScene();
void renderScene();
void callbackFramebufferSize(GLFWwindow* glfWwindow, int width, int height);

void configScene(){
    // Shaders
    shaders.initShaders("resources/shaders/vshader.glsl",
                        "resources/shaders/fshader.glsl");
    // Models
    triangle.initModel("resources/models/triangle.obj");
}

void renderScene(){
    // Clean the actual buffer to the color mentioned below
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    // Use the shaders saved
    shaders.useShaders();
    // Render the model saved
    triangle.renderModel(GL_FILL);
}

void callbackFramebufferSize(GLFWwindow* glfWwindow, int width, int height){
    std::cout << "Screen size (pixels): " << width << "x" << height << std::endl;
}

int main() {

    /************************* OBJECTS *************************/
    // Init Window object
    GLFWwindow* glfWwindow;

    /************************* GLFW LIBRARY *************************/
    // Init GLFW library
    if (!glfwInit()) {
        std::cerr << "GLFW failed in init";
        return -1;
    }

    // Init the version of OpenGL to v3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Create a window using GLFW
    glfWwindow = glfwCreateWindow(500, 500, "Session 1", nullptr, nullptr);
    // Checking if the creation of the window failed or not
    if (!glfWwindow){
        glfwTerminate();
        std::cerr << "GLFWwindow failed in init";
        return -1;
    }

    // Set up Window Context to the window created successfully
    glfwMakeContextCurrent(glfWwindow);
    // Set up Vsync to 60 as Monitor
    glfwSwapInterval(1);

    /************************* GLEW LIBRARY *************************/
    // Init GLEW library showing support through console
    GLenum err = glewInit();
    if (err != GLEW_OK){
        std::cerr << "Error: " << glewGetErrorString(err);
        return -1;
    }
    std::cout << "Status: Using GLEW Library v" << glewGetString(GLEW_VERSION) << std::endl;
    std::cout << "This system supports OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

    /************************* DEFINE EVENTS(CALLBACKS) *************************/
    glfwSetFramebufferSizeCallback(glfWwindow, callbackFramebufferSize);

    /************************* SET UP SCENE *************************/
    configScene();

    /************************* MAIN LOOP *************************/
    // Loop until the user closes the window
    while (!glfwWindowShouldClose(glfWwindow)){
        // Render Scene
        renderScene();
        // Swap buffers to change between frames
        glfwSwapBuffers(glfWwindow);
        // Check if an event should be attended or not (only if we have pending events)
        glfwPollEvents();
    }
    return 0;
}
