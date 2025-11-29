// Copyright (c) 2025 Adrián Quiroga Linares Lectura y referencia permitidas; reutilización y plagio prohibidos

#ifndef INPUT_H
#define INPUT_H

#include <glad.h>
#include <glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>


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

