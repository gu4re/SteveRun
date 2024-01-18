//
// Created by diegopicazo on 14/1/24.
//

#ifndef VARIABLES_H
#define VARIABLES_H

// Viewport
inline int w = 700;
inline int h = 700;
inline bool fullscreen_mode = false;

// Animaciones
inline float rotP = 0.0;
inline float jump = 0.0;
inline double last_timer = 0.0;

// Movimiento de camara
inline float fovy = 60.0;
inline float alphaX = 0.0;
inline float alphaY = 0.0;

// Variables globales para las coordenadas del cubo
inline float cubeX = 0.0f;
inline float cubeY = 9.0f;
inline float cubeZ = 0.0f;

// Variable que indica si el juego está en marcha
inline bool gameRunning = false;

// Variable que indica si el personaje está realmente saltando
// (comprueba que la tecla espacio no se haya dejado pulsada continuamente)
inline bool isJumping = false;
//  Variable que controla si estamos en el menu
inline bool inMainMenu = true;
// Variable que controla la música
inline bool isSoundActive = true;
// Variable que controla la finalizacion de la ejecucion
inline bool isAppActive = true;

void reset();

#endif //VARIABLES_H
