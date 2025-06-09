#include "camara.h"

#define DEG_TO_RAD(x) ((x) * 0.01745329252f) // Convierto grados a radianes



float DISTANCIA = 100; // Defino la distancia de la cámara en la vista exterior

using namespace glm;

float alpha = 0.35f; // Establezco el ángulo horizontal inicial en la vista exterior
float beta = 0.78f;  // Establezco el ángulo vertical inicial en la vista exterior

// Configuro una cámara exterior que me permite ver toda la escena y rotarla alrededor del origen
void myCamaraExterior(int W_WIDTH, int W_HEIGHT) {
    // Defino la proyección en perspectiva
    mat4 projection = perspective(radians(45.0f), (float)W_WIDTH / (float)W_HEIGHT, 1.0f, 200.0f);
    unsigned int projectionLoc = glGetUniformLocation(shadersProgram, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, value_ptr(projection));

    // Defino la vista usando una cámara orbital
    mat4 view = lookAt(
        vec3(
            DISTANCIA * sin(DEG_TO_RAD(alpha)) * cos(DEG_TO_RAD(beta)), // Calculo la posición en X
            DISTANCIA * sin(DEG_TO_RAD(beta)), // Calculo la posición en Y
            DISTANCIA * cos(DEG_TO_RAD(alpha)) * cos(DEG_TO_RAD(beta))  // Calculo la posición en Z
        ),
        vec3(0.0f, 0.0f, 0.0f), // Apunto la cámara al centro de la escena
        vec3(0.0f, 1.0f, 0.0f)  // Establezco la dirección "up"
    );

    unsigned int viewLoc = glGetUniformLocation(shadersProgram, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(view));
}

void myCamaraPrimeraPersona(int W_WIDTH, int W_HEIGHT, float posicionx, float posiciony, float posicionz, float angulo) {
    // Defino la proyección en perspectiva
    mat4 projection = perspective(radians(45.0f), (float)W_WIDTH / (float)W_HEIGHT, 1.0f, 200.0f);
    unsigned int projectionLoc = glGetUniformLocation(shadersProgram, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, value_ptr(projection));

    // Defino la vista en tercera persona
    mat4 view = lookAt(
        vec3(
            posicionx + 7 * sin(DEG_TO_RAD(angulo)), // Coloco la cámara detrás del personaje en X
            posiciony+2 , // Elevo la cámara en Y
            posicionz +7 * cos(DEG_TO_RAD(angulo))  // Coloco la cámara detrás del personaje en Z
        ),
        vec3(posicionx + 25 *sin(DEG_TO_RAD(angulo)), 2, posicionz + 25*cos(DEG_TO_RAD(angulo))), // Apunto la cámara hacia el personaje
        vec3(0.0f, 1.0f, 0.0f) // Mantengo la dirección "up"
    );

    unsigned int viewLoc = glGetUniformLocation(shadersProgram, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(view));
}



// Configuro una cámara en tercera persona, colocando la vista detrás del personaje
void myCamaraTerceraPersona(int W_WIDTH, int W_HEIGHT, float posicionx, float posiciony, float posicionz, float angulo) {
    // Defino la proyección en perspectiva
    mat4 projection = perspective(radians(45.0f), (float)W_WIDTH / (float)W_HEIGHT, 1.0f, 200.0f);
    unsigned int projectionLoc = glGetUniformLocation(shadersProgram, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, value_ptr(projection));

    // Defino la vista en tercera persona
    mat4 view = lookAt(
        vec3(
            posicionx - 20 * sin(DEG_TO_RAD(angulo)), // Coloco la cámara detrás del personaje en X
            posiciony + 10, // Elevo la cámara en Y
            posicionz - 20 * cos(DEG_TO_RAD(angulo))  // Coloco la cámara detrás del personaje en Z
        ),
        vec3(posicionx + sin(DEG_TO_RAD(angulo)), 10, posicionz + cos(DEG_TO_RAD(angulo))), // Apunto la cámara hacia el personaje
        vec3(0.0f, 1.0f, 0.0f) // Mantengo la dirección "up"
    );

    unsigned int viewLoc = glGetUniformLocation(shadersProgram, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(view));
}

vec3 obtenerPosicionCamara(float posicionx, float posiciony, float posicionz, float angulo, int tipoCamara) {
    if (tipoCamara == 1) { // Primera Persona
        return vec3(posicionx, posiciony, posicionz);
    }
    else if (tipoCamara == 2) { // Tercera Persona
        return vec3(
            posicionx - 20 * sin(DEG_TO_RAD(angulo)),
            posiciony + 10,
            posicionz - 20 * cos(DEG_TO_RAD(angulo))
        );
    }
    else { // Cámara Exterior (por defecto)
        return vec3(
            DISTANCIA * sin(DEG_TO_RAD(alpha)) * cos(DEG_TO_RAD(beta)),
            DISTANCIA * sin(DEG_TO_RAD(beta)),
            DISTANCIA * cos(DEG_TO_RAD(alpha)) * cos(DEG_TO_RAD(beta))
        );
    }
}
