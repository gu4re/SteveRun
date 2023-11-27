cmake_minimum_required(VERSION 3.22)

set(PROJECT_NAME plantillaProyecto)
set(CODE_PATH src)

set(CMAKE_CXX_STANDARD 14)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/binary)  # Ajustado para funcionar en cualquier entorno

project(${PROJECT_NAME})

# Configuración para directorios de bibliotecas en GitHub Actions
if (DEFINED ENV{RUNNER_OS} AND DEFINED ENV{RUNNER_TOOL_CACHE})
    set(GLEW_PATH      $ENV{RUNNER_TOOL_CACHE}/glew/2.2.0_1)
    set(GLFW_PATH      $ENV{RUNNER_TOOL_CACHE}/glfw/3.3.8)
    set(GLM_PATH       $ENV{RUNNER_TOOL_CACHE}/glm/0.9.9.8)
    set(ASSIMP_PATH    $ENV{RUNNER_TOOL_CACHE}/assimp/5.3.1)
    set(FREEIMAGE_PATH $ENV{RUNNER_TOOL_CACHE}/freeimage/3.18.0)
else()
    set(GLEW_PATH      /opt/homebrew/Cellar/glew/2.2.0_1)
    set(GLFW_PATH      /opt/homebrew/Cellar/glfw/3.3.8)
    set(GLM_PATH       /opt/homebrew/Cellar/glm/0.9.9.8)
    set(ASSIMP_PATH    /opt/homebrew/Cellar/assimp/5.3.1)
    set(FREEIMAGE_PATH /opt/homebrew/Cellar/freeimage/3.18.0)
endif()

include_directories(${CODE_PATH} ${GLEW_PATH}/include ${GLFW_PATH}/include ${GLM_PATH}/include ${ASSIMP_PATH}/include ${FREEIMAGE_PATH}/include)
link_directories(${GLEW_PATH}/lib ${GLFW_PATH}/lib ${GLM_PATH}/lib ${ASSIMP_PATH}/lib ${FREEIMAGE_PATH}/lib)

file(GLOB_RECURSE CODE_FILES ${CODE_PATH}/*.*)
add_executable(${PROJECT_NAME} ${CODE_FILES} src/Model.cpp)

# Configuración para bibliotecas en GitHub Actions
if (DEFINED ENV{RUNNER_OS} AND DEFINED ENV{RUNNER_TOOL_CACHE})
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL" libGLEW.2.2.0.dylib libglfw.3.3.dylib libassimp.5.3.0.dylib libfreeimage.3.18.0.dylib)
else()
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL" libGLEW.2.2.0.dylib libglfw.3.3.dylib libassimp.5.3.0.dylib libfreeimage.3.18.0.dylib)
endif()
