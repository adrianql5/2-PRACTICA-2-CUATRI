#ifndef OBJETOS_H
#define OBJETOS_H

#include <Windows.h>
#include <iostream>
#include <stdio.h>

#include <glad.h>
#include <glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;


// Variables globales para los VAOs
extern unsigned int VAOCubo, VAOCuadrado, VAOEsfera;

// Declaraciones de las funciones
void crearCubo();
void crearCuadrado();
void crearEsfera();


typedef struct {
	vec3 pos;          // Posici�n en 3D
	float velocidad;   // Velocidad del objeto
	vec3 escalado;     // Escalado en 3D
	float angulo_trans; // �ngulo de translaci�n
	vec3 color;    // Color RGB
	int textura; 
} Objeto;


#endif