#include <windows.h>	
#include <glut.h>	
#include <stdio.h>
#include <math.h>
#include <iostream>

#include "planetas.h"

#define INCREMENTO .05
#define PI 3.1416


int DISTANCIA = 2000;

float alpha = 0;
float beta = 0;
int modo = 0;
int objetivo = 0;
int luzEncendida = 1; // 1 significa que está encendida, 0 apagada


int dibujarOrbitas = 1;
int dibujarEjes = 0;
int iluminacion = 1;

extern int modo;      // Variable global que indica el modo de vista
extern int objetivo;  // Variable global que indica qué planeta ver

// Necesito calcular la posicion absoluta en el modelo para poder ubicar correctamente la camara, por eso tengo esta función.
// El funcionamiento básico es aplicar las formulas dadas y mirando la posicion del padre calcular la del hijo de forma recursiva
void calcularPosicionAbsoluta(Planeta *p) {
        if (p == nullptr)
                return;

        float x = 0, y = 0, z = 0;

        if (p->padre) {
                calcularPosicionAbsoluta(p->padre);
                x = p->padre->posicion[0];
                y = p->padre->posicion[1];
                z = p->padre->posicion[2];
        }

        float inclinacion = 0.0f;
        if (strcmp(p->nombre, "luna") == 0)
                inclinacion = 45.0f * PI / 180.0f;
        else if (strcmp(p->nombre, "iss") == 0)
                inclinacion = 25.0f * PI / 180.0f;

        // Posición en su órbita (asumiendo órbita circular)
        x += p->distanciaOrbita * cos(p->anguloTraslacion);
        y += sin(inclinacion) * p->distanciaOrbita * sin(p->anguloTraslacion) ;
        z += p->distanciaOrbita * sin(p->anguloTraslacion) * cos(inclinacion);

        // Guardar la nueva posición
        p->posicion[0] = x;
        p->posicion[1] = y;
        p->posicion[2] = z;
}

// Función que maneja las opciones del menú contextual
void menuCallback(int option) {
    if (option >= 0 && option <= 8) {
        modo = 1;       // Activar el modo telescopio
        objetivo = option; // Cambiar el objetivo de la cámara
    }
    else if (option == 9) {
        modo = 0;       // Regresar al modo libre
    }
    glutPostRedisplay(); // Refrescar la pantalla
}

// Función para crear el menú y asociarlo al clic derecho
void crearMenu() {
    int menu = glutCreateMenu(menuCallback);
    glutAddMenuEntry("Ver el Sol", 0);
    glutAddMenuEntry("Ver Mercurio", 1);
    glutAddMenuEntry("Ver Venus", 2);
    glutAddMenuEntry("Ver la Tierra desde la Luna", 3);
    glutAddMenuEntry("Ver la Tierra desde la ISS", 4);
    glutAddMenuEntry("Ver Marte", 5);
    glutAddMenuEntry("Ver Júpiter", 6);
    glutAddMenuEntry("Ver Saturno", 7);
    glutAddMenuEntry("Ver Urano", 8);
    glutAddMenuEntry("Modo Libre", 9);

    // Asociar el menú al botón derecho del mouse
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

// funcion que define la posicion de la cámara
void myCamara(float ratio, Planeta **arrPlanetas, int nPlanetas){
        // Configuro la matriz de Proyección
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45, ratio, 0.1f, 3000.0f);


        // Configuro la posición de la cámara
        if (modo == 0) // si es el modo default se puede rotar y girar la cámara, lo de (cos(beta) >= 0 ? 1 : -1) evita que dé el famoso salto.
                gluLookAt(((float) DISTANCIA * (float) sin(alpha) * cos(beta)), ((float) DISTANCIA * (float) sin(beta)), ((float) DISTANCIA * cos(alpha) * cos(beta)), 0, 0, 0, 0, (cos(beta) >= 0 ? 1 : -1), 0);

        else {
                // En caso de ser modo telescopio obtengo los planetas
                Planeta *tierra = encontrarPlaneta(arrPlanetas, nPlanetas, "tierra");
                Planeta *sol = encontrarPlaneta(arrPlanetas, nPlanetas, "sol");
                Planeta *mercurio = encontrarPlaneta(arrPlanetas, nPlanetas, "mercurio");
                Planeta *venus = encontrarPlaneta(arrPlanetas, nPlanetas, "venus");
                Planeta *luna = encontrarPlaneta(arrPlanetas, nPlanetas, "luna");
                Planeta *iss = encontrarPlaneta(arrPlanetas, nPlanetas, "iss");
                Planeta *marte = encontrarPlaneta(arrPlanetas, nPlanetas, "marte");
                Planeta *jupiter = encontrarPlaneta(arrPlanetas, nPlanetas, "jupiter");
                Planeta *saturno = encontrarPlaneta(arrPlanetas, nPlanetas, "saturno");
                Planeta *urano = encontrarPlaneta(arrPlanetas, nPlanetas, "urano");

                // Para decidir a qué planeta mirar desde la Tierra o desde la ISS o Luna, basicamente le paso las posicions de los planetas a la cámara.
                //gluLookAt(posCam, posObjetivo, "arriba")
                switch (objetivo) {
                case 0: // Sol
                        gluLookAt(tierra->posicion[0], tierra->posicion[1], tierra->posicion[2],
                                  sol->posicion[0], sol->posicion[1], sol->posicion[2], 0, (cos(beta) >= 0 ? 1 : -1), 0);
                        break;
                case 1: // Mercurio
                        gluLookAt(tierra->posicion[0], tierra->posicion[1], tierra->posicion[2],
                                  mercurio->posicion[0], mercurio->posicion[1], mercurio->posicion[2], 0, (cos(beta) >= 0 ? 1 : -1), 0);
                        break;
                case 2: // Venus
                        gluLookAt(tierra->posicion[0], tierra->posicion[1], tierra->posicion[2],
                                  venus->posicion[0], venus->posicion[1], venus->posicion[2], 0, (cos(beta) >= 0 ? 1 : -1), 0);
                        break;
                case 3: // Luna
                        calcularPosicionAbsoluta(luna);
                        gluLookAt(luna->posicion[0], luna->posicion[1], luna->posicion[2],
                                  tierra->posicion[0], tierra->posicion[1], tierra->posicion[2], 0, (cos(beta) >= 0 ? 1 : -1), 0);
                        break;
                case 4: // ISS
                        calcularPosicionAbsoluta(iss);
                        gluLookAt(iss->posicion[0], iss->posicion[1], iss->posicion[2],
                                  tierra->posicion[0], tierra->posicion[1], tierra->posicion[2], 0, (cos(beta) >= 0 ? 1 : -1), 0);
                        break;
                case 5: // Marte
                        gluLookAt(tierra->posicion[0], tierra->posicion[1], tierra->posicion[2],
                                  marte->posicion[0], marte->posicion[1], marte->posicion[2], 0, (cos(beta) >= 0 ? 1 : -1), 0);
                        break;
                case 6: // Júpiter
                        gluLookAt(tierra->posicion[0], tierra->posicion[1], tierra->posicion[2],
                                  jupiter->posicion[0], jupiter->posicion[1], jupiter->posicion[2], 0, (cos(beta) >= 0 ? 1 : -1), 0);
                        break;
                case 7: // Saturno
                        gluLookAt(tierra->posicion[0], tierra->posicion[1], tierra->posicion[2],
                                  saturno->posicion[0], saturno->posicion[1], saturno->posicion[2], 0, (cos(beta) >= 0 ? 1 : -1), 0);
                        break;
                case 8: // Urano
                        gluLookAt(tierra->posicion[0], tierra->posicion[1], tierra->posicion[2],
                                  urano->posicion[0], urano->posicion[1], urano->posicion[2], 0, (cos(beta) >= 0 ? 1 : -1), 0);
                        break;
                default:
                        std::cerr << "Error: Opción no válida en el menú.\n";
                        break;
                }
        }
        glMatrixMode(GL_MODELVIEW);
}

//funcion que detecta las pulsaciones de las teclas
void myTeclado(unsigned char tras, int x, int y) {
    switch (tras) {
    case '-':
        DISTANCIA += 10; //decremento el zoom
        break;

    case '+':
        DISTANCIA -= 10; //aumento el zoom
        break;

    case 'o':
        dibujarOrbitas = !dibujarOrbitas; //invierto el modo de dibujar o no orbitas
        break;

    case 'e':
        dibujarEjes = !dibujarEjes; //invierto el modo de dibujar o no ejes
        break;

    case 'i':
        iluminacion = !iluminacion; //inviero el modo de iluminar o no
        break;

    case 'n':
        luzEncendida = !luzEncendida;
        if (luzEncendida) {
            glEnable(GL_LIGHT0);
            glEnable(GL_LIGHTING);
        }
        else {
            glDisable(GL_LIGHT0);
            glDisable(GL_LIGHTING);
        }
        glutPostRedisplay(); // Fuerza a que se redibuje la escena
        break;

    case 'v':
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //para solo ver las lineas de los poligonos
        break;

    case 'b':
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //para ver el área de los polígonos coloreada
        break;

    }

    //refresco
    glutPostRedisplay();
}

//funcion para mover la cámara, donde incremento y decremento los valores de alpha y beta
void moverCamara(int cursor, int x, int y){
        switch (cursor) {
        case GLUT_KEY_F1:
                break;
        case GLUT_KEY_F2:
                break;
        case GLUT_KEY_F3:
                break;
        case GLUT_KEY_F4:
                break;
        case GLUT_KEY_F5:
                break;
        case GLUT_KEY_F6:
                break;

        case GLUT_KEY_UP:
                beta += INCREMENTO;
                break;
        case GLUT_KEY_DOWN:
                beta -= INCREMENTO;
                break;
        case GLUT_KEY_RIGHT:
                alpha -= INCREMENTO;
                break;
        case GLUT_KEY_LEFT:
                alpha += INCREMENTO;
                break;

        default:
                break;
        }
        //refresco
        glutPostRedisplay();
}
