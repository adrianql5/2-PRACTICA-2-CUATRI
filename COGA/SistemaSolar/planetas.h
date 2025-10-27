// Copyright (c) 2025 AdriÃ¡n Quiroga Linares Lectura y referencia permitidas; reutilizaciÃ³n y plagio prohibidos

#pragma once
#include <windows.h>	
#include <glut.h>
#define MAX_SATELITES 10


//Defino la estructura de los planetas y las funciones que se relacionan con ellos
typedef struct Planeta {

	char nombre[15];
	float tamano;

	float velocidadTraslacion;
	float velocidadRotacion;

	float anguloTraslacion;
	float anguloRotacion;

	float posicion[3];
	float color[3];

	float distanciaOrbita; // Radio de la órbita con respecto a su estrella/padre

	int nSatelites=0; // Número de satélites naturales (inicializado en 0)
	struct Planeta* satelites[MAX_SATELITES]; // Array de punteros a satélites (otros planetas que orbitan este)
	Planeta* padre; // Puntero al planeta alrededor del cual orbita este planeta

    int lista; // Identificador de la lista de visualización en OpenGL (almacena su representación gráfica)

	GLuint textura;

}Planeta;

Planeta* crearPlaneta(const char nombre[15], float tamano, float velocidadTraslacion, float velocidadRotacion, float color[3], float distanciaOrbita, Planeta* planetaQueOrbita,int lista, const char* archivoTextura);
void modificarPosicion(Planeta* p, float posicion[3]);
Planeta* encontrarPlaneta(Planeta ** arr, int size,const char * nombre);
GLuint cargaTextura(const char* nombre);