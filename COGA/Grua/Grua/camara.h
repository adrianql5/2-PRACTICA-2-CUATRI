#ifndef INPUT_H
#define INPUT_H

#include <iostream>

#include "deps.h"


extern float alpha;
extern float beta;
extern float DISTANCIA;

using namespace glm;
//Uso este .h para no tener 1000 lineas de codigo en un mismo archivo y mejorar la legibilidad

extern GLuint shadersProgram;

void myCamaraExterior(int W_WIDTH, int W_HEIGHT);

void myCamaraPrimeraPersona(int W_WIDTH, int W_HEIGHT, float posicionx, float posiciony, float posicionz, float angulo);

void myCamaraTerceraPersona(int W_WIDTH, int W_HEIGHT, float posicionx, float posiciony, float posicionz, float angulo);

vec3 obtenerPosicionCamara(float posicionx, float posiciony, float posicionz, float angulo, int tipoCamara);


#endif

