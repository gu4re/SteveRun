#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shaders.h"
#include "Model.h"

// Global Shaders
Shaders shaders;
// Global Models
Model triangle;
Model plane;
Model cylinder;
// Global viewports
int width = 700;
int height = 700;
bool fullscreen_mode = false;
// Init Window object
GLFWwindow *glfWwindow;
// Global variables for animations
float screw_transZ = 0.0;
float screw_rotZ = 0.0;
float mill_rotZ = 0.0;
double last_timer = 0.0;
double screw_rotZ_threshold = 0.01; // 10 milliseconds

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

void drawBlade(glm::mat4 projection_matrix, glm::mat4 cam_matrix, glm::mat4 model_matrix) {
    // Screw object
    glm::mat4 triangle_translate_matrix = glm::translate(I, glm::vec3(0, -0.8, 0.0));
    // Scale object
    glm::mat4 triangle_scale_matrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.4f, 0.8f, 0.5f));
    drawObject(triangle, glm::vec3(1.0, 0.0, 0.0),
               projection_matrix, cam_matrix, model_matrix * triangle_translate_matrix * triangle_scale_matrix);
}

void drawCylinder(glm::mat4 projection_matrix, glm::mat4 cam_matrix, glm::mat4 model_matrix) {
    // Cylinder object
    // scale, translate and rotate transformations are possible options inside a model matrix
    glm::mat4 cylinder_scale_matrix = glm::scale(I, glm::vec3(0.1, 2.0, 0.1));
    glm::mat4 cylinder_translate_matrix = glm::translate(I, glm::vec3(0, 2, screw_transZ));
    glm::mat4 cylinder_rotate_matrix = glm::rotate(I, glm::radians(mill_rotZ),
                                                   glm::vec3(0, 1, 0));
    drawObject(cylinder, glm::vec3(0.0, 1.0, 0.0),
               projection_matrix, cam_matrix,
               model_matrix * cylinder_translate_matrix * cylinder_scale_matrix * cylinder_rotate_matrix);
}

void drawScrew(glm::mat4 projection_matrix, glm::mat4 cam_matrix, glm::mat4 model_matrix) {
    // Angle of separation
    float angleSeparation = glm::radians(120.0f);

    // Get current time
    auto currentTime = glfwGetTime();
    double deltaTime = currentTime - last_timer;
    // Check if the threshold is passed
    if (deltaTime >= screw_rotZ_threshold) {
        last_timer = currentTime;
        screw_rotZ += 2.0;
        // Ensuring that the angle is always less than 360º
        screw_rotZ = fmod(screw_rotZ, 360.0);
    }
    glm::mat4 screw_translate_matrix = glm::translate(I,
                                                      glm::vec3(0.0, 4.0, screw_transZ));
    glm::mat4 screw_rotate_matrix = glm::rotate(I, glm::radians(screw_rotZ),
                                                glm::vec3(0, 0, 1));
    // rotate Y
    glm::mat4 screw_rotate_matrix_2 = glm::rotate(I, glm::radians(mill_rotZ),
                                                  glm::vec3(0, 1, 0));
    glm::mat4 screw_rotate_matrix_master = screw_rotate_matrix_2 * screw_rotate_matrix;
    drawBlade(projection_matrix, cam_matrix, model_matrix * screw_translate_matrix * screw_rotate_matrix_master);
    for (int i = 0; i < 3; ++i) {
        glm::mat4 blade_Rz90 = glm::rotate(I, angleSeparation * i, glm::vec3(0, 0, 1));
        drawBlade(projection_matrix, cam_matrix,
                  model_matrix * screw_translate_matrix * screw_rotate_matrix_master * blade_Rz90);
    }
}

void drawWindmill(glm::mat4 projection_matrix, glm::mat4 cam_matrix, glm::mat4 model_matrix) {
    /************************* DRAW CYLINDER *************************/
    drawCylinder(projection_matrix, cam_matrix, I);
    /************************* DRAW SCREW *************************/
    drawScrew(projection_matrix, cam_matrix, I);
}

void drawPlane(glm::mat4 projection_matrix, glm::mat4 cam_matrix, glm::mat4 model_matrix) {
    // Plane object
    // scale, translate and rotate transformations are possible options inside a model matrix
    glm::mat4 plane_scale_matrix = glm::scale(I, glm::vec3(5.0, 1.0, 5.0));
    drawObject(plane, glm::vec3(0.0, 0.0, 1.0),
               projection_matrix, cam_matrix, model_matrix * plane_scale_matrix);
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
    triangle.initModel("resources/models/triangle.obj");
    plane.initModel("resources/models/plane.obj");
    cylinder.initModel("resources/models/cylinder.obj");
}

void renderScene() {
    // Clean the color buffer to the color mentioned below and restore the depth buffer to default
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Use the shaders from a local directory
    shaders.useShaders();
    /************************* CAM MATRIX *************************/
    glm::vec3 eye(0.0, 3.0, 10.0);
    glm::vec3 center(0.0, 0.0, 0.0);
    glm::vec3 up(0.0, 1.0, 0.0);
    glm::mat4 cam_matrix = glm::lookAt(eye, center, up);
    /************************* PROJECTION MATRIX *************************/
    float fovy = 60.0; // grades
    float nplane = 0.1; // near plane
    float fplane = 25.0; // far plane
    float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
    glm::mat4 projection_matrix = glm::perspective(glm::radians(fovy), aspectRatio, nplane, fplane);
    /************************* DRAW PLANE *************************/
    drawPlane(projection_matrix, cam_matrix, I);
    /************************* DRAW WINDMILL *************************/
    drawWindmill(projection_matrix, cam_matrix, I);
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
        case GLFW_KEY_UP:
            screw_transZ -= 0.1;
            break;
        case GLFW_KEY_DOWN:
            screw_transZ += 0.1;
            break;
        case GLFW_KEY_LEFT:
            mill_rotZ += 5;
            break;
        case GLFW_KEY_RIGHT:
            mill_rotZ -= 5;
            break;
        case GLFW_KEY_F:
            if (action == GLFW_PRESS) {
                fullscreen_mode ? fullscreen_mode = false : fullscreen_mode = true;
                screenMode();
            }
            break;
        default: // Reset the screw when we press any key
            screw_transZ = 0.0;
            mill_rotZ = 0.0;
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
