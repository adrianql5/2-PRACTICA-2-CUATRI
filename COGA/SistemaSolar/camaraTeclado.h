#pragma once
#include "planetas.h"

//Defino las funciones relacionadas con la camra y el teclado

void myCamara(float ratio, Planeta ** arrPlanetas, int nPlanetas);
void myTeclado(unsigned char tras, int x, int y);
void moverCamara(int cursor, int x, int y);
void crearMenu();

