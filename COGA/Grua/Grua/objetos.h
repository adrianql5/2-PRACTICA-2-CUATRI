// Copyright (c) 2025 AdriÃ¡n Quiroga Linares Lectura y referencia permitidas; reutilizaciÃ³n y plagio prohibidos

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
	vec3 pos;          // Posición en 3D
	float velocidad;   // Velocidad del objeto
	vec3 escalado;     // Escalado en 3D
	float angulo_trans; // Ángulo de translación
	vec3 color;    // Color RGB
	int textura; 
} Objeto;


#endif