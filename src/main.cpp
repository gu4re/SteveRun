#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shaders.h"
#include "Model.h"

// Global Shaders
Shaders shaders;
// Global Models
Model sphere;
Model cube;
// Global viewports
int width = 700;
int height = 700;
bool fullscreen_mode = false;
// Init Window object
GLFWwindow *glfWwindow;

void drawObject(Model &model, glm::vec3 vec3_color, glm::mat4 projection_matrix,
                glm::mat4 cam_matrix, glm::mat4 model_matrix) {
    // Pass the multiplication of the three matrix through a uniform variable
    shaders.setMat4("uPVM", projection_matrix * cam_matrix * model_matrix);
    // Enable the offset for the first representation allows us to avoid z-fighting
    glEnable(GL_POLYGON_OFFSET_FILL);
    // Setting up the color of the model before saving it
    shaders.setVec3("uColor", vec3_color);
    // Render the model saved in a local directory
    // GL_LINE -> Model without filling color
    // GL_FILL -> Model with filling color
    model.renderModel(GL_FILL);
    // Important to disable the offset to only affect previous model
    glDisable(GL_POLYGON_OFFSET_FILL);
    // DEPRECATED: Rendering twice giving depth and avoiding luminous model at this moment
    shaders.setVec3("uColor", glm::vec3(1.0, 1.0, 1.0));
    model.renderModel(GL_LINE);
}
               
void drawSphere(glm::mat4 projection_matrix, glm::mat4 cam_matrix, glm::mat4 model_matrix){
    // Sphere object
    glm::mat4 sphere_scale_matrix = glm::scale(I, glm::vec3(6.0, 6.0, 1.0));
    drawObject(sphere, glm::vec3(0.0, 0.0, 1.0),
               projection_matrix, cam_matrix, sphere_scale_matrix*model_matrix);
}

void screenMode() {
    // Gets the current monitor where is running the game
    GLFWmonitor *primaryMonitor = glfwGetPrimaryMonitor();
    int xpos, ypos;
    glfwGetWindowPos(glfWwindow, &xpos, &ypos);
    // Gets the video mode to obtain screen specs
    const GLFWvidmode *videoMode = glfwGetVideoMode(primaryMonitor);
    if (fullscreen_mode) {
        glfwSetWindowMonitor(glfWwindow, primaryMonitor, 0, 0,
                             videoMode->width, videoMode->height, videoMode->refreshRate);
    } else {
        std::cout << videoMode->width << std::endl;
        glfwSetWindowMonitor(glfWwindow, nullptr, (videoMode->width / 2) - 700,
                             (videoMode->height / 2) - 700,700, 700,
                             videoMode->refreshRate);
    }
}

void configScene() {
    // Enable depth buffer and establish an offset of the polygon
    // the offset can be used by any model
    glEnable(GL_DEPTH_TEST);
    glPolygonOffset(1.0, 1.0);
    // Enable culling to avoid rendering those parts that are not visible (only for 3D objects)
    //glEnable(GL_CULL_FACE);
    // Init Shaders
    shaders.initShaders("resources/shaders/vshader.glsl",
                        "resources/shaders/fshader.glsl");
    // Init Models
    sphere.initModel("resources/models/sphere.obj");
    cube.initModel("resources/models/cube.obj");

}

void renderScene() {
    // Clean the color buffer to the color mentioned below and restore the depth buffer to default
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Use the shaders from a local directory
    shaders.useShaders();
    /************************* CAM MATRIX *************************/
    glm::vec3 eye(0.0, 5.0, 2.0); // Cam position
    glm::vec3 center(0.0, 5.0, 0.0); // Where we look
    glm::vec3 up(0.0, 1.0, 0.0); // normal vector
    glm::mat4 cam_matrix = glm::lookAt(eye, center, up);
    /************************* PROJECTION MATRIX *************************/
    float fovy = 60.0; // grades
    float nplane = 0.1; // near plane
    float fplane = 25.0; // far plane
    float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
    glm::mat4 projection_matrix = glm::perspective(glm::radians(fovy), aspectRatio, nplane, fplane);
    /************************* DRAW SPHERE *************************/
    drawSphere(projection_matrix, cam_matrix, I);
    drawObject(cube, glm::vec3(1.0, 0.0, 0.0), projection_matrix, cam_matrix,
               glm::translate(I, glm::vec3(-1.0, 5.0, 0.0))*glm::scale(I, glm::vec3(0.5)));
}

void callbackFramebufferSize(GLFWwindow *glfWwindow, int newWidth, int newHeight) {
    // Adjust viewport to the new window's size to adjust object to the whole screen
    glViewport(0, 0, newWidth, newHeight);
    // Update the width and height to the new values
    width = newWidth;
    height = newHeight;
}

void callbackKey(GLFWwindow *window, int key, int scancode, int action, int mods) {
    switch (key) {
        case GLFW_KEY_F:
            if (action == GLFW_PRESS) {
                fullscreen_mode ? fullscreen_mode = false : fullscreen_mode = true;
                screenMode();
            }
            break;
        default:
            break;
    }
}

int main() {

    /************************* OBJECTS *************************/
  
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
    glfWwindow = glfwCreateWindow(width, height, "CrocodileGame", nullptr, nullptr);
    // Checking if the creation of the window failed or not
    if (!glfWwindow) {
        glfwTerminate();
        std::cerr << "GLFWwindow failed to init";
        return -1;
    }

    // Set up Window Context to the window created successfully
    glfwMakeContextCurrent(glfWwindow);
    // Set up Vsync to 60 as Monitor
    glfwSwapInterval(1);

    /************************* GLEW LIBRARY *************************/
    // Init GLEW library showing support through console
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cerr << "Error: " << glewGetErrorString(err);
        return -1;
    }
    std::cout << "Status: Using GLEW Library v" << glewGetString(GLEW_VERSION) << std::endl;
    std::cout << "This system supports OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

    /************************* DEFINE EVENTS(CALLBACKS) *************************/
    glfwSetFramebufferSizeCallback(glfWwindow, callbackFramebufferSize);
    glfwSetKeyCallback(glfWwindow, callbackKey);
    /************************* SET UP SCENE *************************/
    configScene();

    /************************* MAIN LOOP *************************/
    // Loop until the user closes the window
    while (!glfwWindowShouldClose(glfWwindow)) {
        // Render Scene
        renderScene();
        // Swap buffers to change between frames
        glfwSwapBuffers(glfWwindow);
        // Check if an event should be attended or not (only if we have pending events)
        glfwPollEvents();
    }

    /************************* GARBAGE RECOLECTOR *************************/
    glfwDestroyWindow(glfWwindow);
    glfwTerminate();

    return 0;
}
