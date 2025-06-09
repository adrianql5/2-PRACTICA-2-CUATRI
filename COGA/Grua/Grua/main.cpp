/*

    Codigo escrito por Adrián Quiroga Linares

*/

#include <Windows.h>
#include <iostream>
#include <stdio.h>

#include <glad.h>
#include <glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <unordered_map>

#include "lecturaShader_0_9.h"
#include "objetos.h"
#include "camara.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#define RGB_TO_FLOAT(x) ((x) / 256.0f) //convierto RGB  a float
#define DEG_TO_RAD(x) ((x) * 0.01745329252f) //convierto grados a radianes

int giroDerecha = 0;
int giroIzquierda = 0;
int avance = 0;
int retroceso = 0;

using namespace glm; //con esto me ahorro de andar usando todo el rato glm::

int W_WIDTH = 800;
int W_HEIGHT = 800;

int modoCamara = 1; // Modo de cámara inicial (1 = exterior, 2 = primera persona, 3 = tercera persona)

int iluminacionNoct = 1;

// Mapa de teclas para detectar múltiples entradas
std::unordered_map<int, bool> teclas;
std::unordered_map<int, bool> teclas2;

//Inicializo todos los objetos
Objeto terreno = { {0, 0, 0}, 0, {100, 1, 100}, 0, {RGB_TO_FLOAT(256), RGB_TO_FLOAT(256),RGB_TO_FLOAT(256)}, 0 };

Objeto base = { {0, 1.5, 0.5}, 0, {10, 2, 4}, 0, {RGB_TO_FLOAT(256), RGB_TO_FLOAT(256),RGB_TO_FLOAT(256)}, 0 };
Objeto cabina = { {5.0, 1.0, 0.0}, 0, {2.0, 3.0, 4.0},  0, {RGB_TO_FLOAT(256), RGB_TO_FLOAT(256), RGB_TO_FLOAT(256)}, 0 };
Objeto articulacion1 = { {-0.4, 0.4, 0.0}, 0, {1.0, 1.0, 1.0},  0, {RGB_TO_FLOAT(256), RGB_TO_FLOAT(256), RGB_TO_FLOAT(256)}, 0 };
Objeto articulacion2 = { {0, 0, 0.0}, 0, {1.0, 1.0, 1.0},  0, {RGB_TO_FLOAT(256), RGB_TO_FLOAT(256), RGB_TO_FLOAT(256)} , 0 };

Objeto brazo = { {0.0, 3.0, 0.0}, 0, {0.5, 6.0, 0.5}, 0, {RGB_TO_FLOAT(256), RGB_TO_FLOAT(256), RGB_TO_FLOAT(256)}, 0 };
Objeto foco = { {5.0, 2.5,0.0},0,{0.5,0.5,0.5}, 0 , {1,1,1}, 0 };
Objeto parabrisas = { {5.8,1,0},0,{.5,1.5,3.5},0,{1,1,1}, 0 };
Objeto faro = { {5.8,-0.4,0},0,{.5,.2,3.5},0,{RGB_TO_FLOAT(256),RGB_TO_FLOAT(256),RGB_TO_FLOAT(256)}, 0 };


Objeto rueda1 = { {3.5, -0.5, 2.0}, 0, {1.5, 1.5, 1.5},  0, {RGB_TO_FLOAT(256), RGB_TO_FLOAT(256), RGB_TO_FLOAT(256)} , 0 };
Objeto rueda2 = { {-3.5, -0.5, 2.0}, 0, {1.5, 1.5, 1.5},  0, {RGB_TO_FLOAT(256), RGB_TO_FLOAT(256), RGB_TO_FLOAT(256)}, 0 };
Objeto rueda3 = { {3.5, -0.5, -2.0}, 0, {1.5, 1.5, 1.5},  0, {RGB_TO_FLOAT(256), RGB_TO_FLOAT(256), RGB_TO_FLOAT(256)} , 0 };
Objeto rueda4 = { {-3.5, -0.5, -2.0}, 0, {1.5, 1.5, 1.5},  0, {RGB_TO_FLOAT(256), RGB_TO_FLOAT(256), RGB_TO_FLOAT(256)}, 0 };


Objeto planta1 = { {40, 0, 40}, 0, {4, 3, 0}, 0, {RGB_TO_FLOAT(256), RGB_TO_FLOAT(256), RGB_TO_FLOAT(256)}, 0 };
Objeto planta2 = { {-35, 0, -45}, 0, {3.5, 2.8, 0}, 0, {RGB_TO_FLOAT(256), RGB_TO_FLOAT(256), RGB_TO_FLOAT(256)}, 0 };
Objeto planta3 = { {30, 0, -30}, 0, {4.2, 3.1, 0}, 0, {RGB_TO_FLOAT(256), RGB_TO_FLOAT(256), RGB_TO_FLOAT(256)}, 0 };
Objeto planta4 = { {-40, 0, 35}, 0, {3.8, 3.0, 0}, 0, {RGB_TO_FLOAT(256), RGB_TO_FLOAT(256), RGB_TO_FLOAT(256)}, 0 };
Objeto planta5 = { {0, 0, 45}, 0, {5.0, 4.0, 0}, 0, {RGB_TO_FLOAT(256), RGB_TO_FLOAT(256), RGB_TO_FLOAT(256)}, 0 };

Objeto cactus1 = { {25, 2, 20}, 0, {2.5, 4, 5}, 0, {RGB_TO_FLOAT(256), RGB_TO_FLOAT(256), RGB_TO_FLOAT(256)}, 0 };
Objeto cactus2 = { {-20, 2, -25}, 0, {2.8, 3.5, 2}, 0, {RGB_TO_FLOAT(256), RGB_TO_FLOAT(256), RGB_TO_FLOAT(256)}, 0 };
Objeto cactus3 = { {10, 2, -40}, 0, {3.0, 8, 2}, 0, {RGB_TO_FLOAT(256), RGB_TO_FLOAT(256), RGB_TO_FLOAT(256)}, 0 };
Objeto cactus4 = { {-30, 2, 30}, 0, {4.7, 7, 3}, 0, {RGB_TO_FLOAT(256), RGB_TO_FLOAT(256), RGB_TO_FLOAT(256)}, 0 };

unsigned int balazos, remolino;

// Identificadores de los VAOs para cada objeto
unsigned int VAOCubo, VAOCuadrado, VAOEsfera;

// Variables para el control del tiempo
float lastTime=glfwGetTime();
float currentTime;
float lapsoTime;
int nbFrames = 0;


// Carga de shaders
extern GLuint setShaders(const char* nVertx, const char* nFrag);
GLuint shadersProgram;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void tiempo();
GLuint cargaTextura(const char* nombre);
void iniciarTexturas();




// Funcion para controlar el movimiento
void movimiento() {
    base.pos[0] += base.velocidad * sin(DEG_TO_RAD(base.angulo_trans)) * lapsoTime;
    base.pos[2] += base.velocidad * cos(DEG_TO_RAD(base.angulo_trans)) * lapsoTime;
    
    //si se sale de un lado del mapa entra por el otro
    if (base.pos[0] > 50) base.pos[0] = -50;
    if (base.pos[0] < -50) base.pos[0] = 50;

    if (base.pos[2] > 50) base.pos[2] = -50;
    if (base.pos[2] < -50) base.pos[2] = 50;

    rueda1.angulo_trans += base.velocidad * 0.01;
    if (rueda1.angulo_trans > 360) rueda1.angulo_trans -= 360;
}


void dibujarPlanta(Objeto& planta, unsigned int transformLoc, unsigned int colorLoc) {
    mat4 transform = mat4(1.0f); // Matriz identidad
    transform = translate(transform, planta.pos);
    transform = scale(transform, planta.escalado);

    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, value_ptr(transform));
    glUniform3f(colorLoc, planta.color[0], planta.color[1], planta.color[2]);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, planta.textura);
    glBindVertexArray(VAOCubo);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindTexture(GL_TEXTURE_2D, 0);
}

//Funcion que dibuja la decoracion de la escena
void dibujarAccesorios() {
    unsigned int transformLoc = glGetUniformLocation(shadersProgram, "model");
    unsigned int colorLoc = glGetUniformLocation(shadersProgram, "objectColor");

    dibujarPlanta(planta1, transformLoc, colorLoc);
    dibujarPlanta(planta2, transformLoc, colorLoc);
    dibujarPlanta(planta3, transformLoc, colorLoc);
    dibujarPlanta(planta4, transformLoc, colorLoc);
    dibujarPlanta(planta5, transformLoc, colorLoc);

    dibujarPlanta(cactus1, transformLoc, colorLoc);
    dibujarPlanta(cactus2, transformLoc, colorLoc);
    dibujarPlanta(cactus3, transformLoc, colorLoc);
    dibujarPlanta(cactus4, transformLoc, colorLoc);
}



void dibujarRueda() {
    glBindVertexArray(VAOCubo);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}


void dibujarRuedas(mat4 matGrua) {
    unsigned int transformLoc = glGetUniformLocation(shadersProgram, "model");

    float anguloGiroRuedas = 0.0f;
    if (giroDerecha) anguloGiroRuedas = DEG_TO_RAD(20);  // Gira a la derecha
    if (giroIzquierda) anguloGiroRuedas = DEG_TO_RAD(-20); // Gira a la izquierda

    mat4 matAux = matGrua;

    matGrua = translate(matGrua, rueda1.pos);
    matGrua = rotate(matGrua, anguloGiroRuedas, vec3(0.0f, 1.0f, 0.0f));
    matGrua = rotate(matGrua, DEG_TO_RAD(-rueda1.angulo_trans), vec3(0.0f, 0.0f, 1.0f));
    matGrua = scale(matGrua, rueda1.escalado);

    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, value_ptr(matGrua));
    GLuint colorLoc = glGetUniformLocation(shadersProgram, "objectColor");
    glUniform3f(colorLoc, rueda1.color[0], rueda1.color[1], rueda1.color[2]);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, rueda1.textura);
    dibujarRueda();

    matGrua = matAux;

    matGrua = translate(matGrua, rueda2.pos);
    matGrua = rotate(matGrua, DEG_TO_RAD(-rueda1.angulo_trans), vec3(0.0f, 0.0f, 1.0f));
    matGrua = scale(matGrua, rueda2.escalado);

    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, value_ptr(matGrua));
    glUniform3f(colorLoc, rueda2.color[0], rueda2.color[1], rueda2.color[2]);
    dibujarRueda();

    matGrua = matAux;
    matGrua = translate(matGrua, rueda3.pos);
    matGrua = rotate(matGrua, anguloGiroRuedas, vec3(0.0f, 1.0f, 0.0f));
    matGrua = rotate(matGrua, DEG_TO_RAD(-rueda1.angulo_trans), vec3(0.0f, 0.0f, 1.0f));
    matGrua = scale(matGrua, rueda3.escalado);

    

    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, value_ptr(matGrua));
    glUniform3f(colorLoc, rueda3.color[0], rueda3.color[1], rueda3.color[2]);
    dibujarRueda();

    matGrua = matAux;
    matGrua = translate(matGrua, rueda4.pos);
    matGrua = rotate(matGrua, DEG_TO_RAD(-rueda1.angulo_trans), vec3(0.0f, 0.0f, 1.0f));
    matGrua = scale(matGrua, rueda4.escalado);

    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, value_ptr(matGrua));
    glUniform3f(colorLoc, rueda4.color[0], rueda4.color[1], rueda4.color[2]);
    dibujarRueda();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

//funcion del display
void display() {
    // Actualiza el tiempo de animaciones o lógica
    tiempo();

    // Actualiza posiciones y movimientos (e.g., del rover, grúa, etc.)
    movimiento();

    // Obtiene la ubicación de las variables uniformes en el shader
    unsigned int transformLoc = glGetUniformLocation(shadersProgram, "model");
    unsigned int colorLoc = glGetUniformLocation(shadersProgram, "objectColor");

    // ----------------------
    // DIBUJAR EL TERRENO
    // ----------------------
    mat4 transform = mat4(); // matriz identidad
    transform = scale(transform, terreno.escalado); // aplica escalado
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, value_ptr(transform)); // pasa la matriz al shader

    // Aplica el color del terreno
    glUniform3f(colorLoc, terreno.color[0], terreno.color[1], terreno.color[2]);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // modo de dibujo (relleno)

    // Textura del terreno
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, terreno.textura);

    // Dibuja el terreno
    glBindVertexArray(VAOCuadrado);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    // Limpieza de textura
    glBindTexture(GL_TEXTURE_2D, 0);

    // Dibuja objetos extra (accesorios tipo cactus u otros decorativos)
    dibujarAccesorios();

    // ----------------------
    // DIBUJAR BASE DEL ROVER / GRÚA
    // ----------------------

    // Indico al shader que usaré doble textura para este objeto
    unsigned int nTexturasLoc = glGetUniformLocation(shadersProgram, "nTexturas");
    glUniform1i(nTexturasLoc, 1);

    // Reseteo la transformación y aplico traslación y rotación
    transform = mat4();
    transform = translate(transform, base.pos);
    transform = rotate(transform, DEG_TO_RAD(base.angulo_trans - 90), vec3(0, 1, 0));

    mat4 matGrua = transform; // guardo la transformación de la base para usarla en piezas hijas

    transform = scale(transform, base.escalado);
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, value_ptr(transform));
    glUniform3f(colorLoc, base.color[0], base.color[1], base.color[2]);

    // Aplico doble textura (base y overlay)
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, base.textura);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, balazos); // segunda textura

    glBindVertexArray(VAOCubo);
    glDrawArrays(GL_TRIANGLES, 0, 36); // dibuja cubo

    // Limpieza de texturas
    glBindTexture(GL_TEXTURE_2D, 0);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, 0);

    // Desactivo textura doble para próximos objetos
    glUniform1i(nTexturasLoc, 0);

    // ----------------------
    // CABINA
    // ----------------------
    mat4 matAux = matGrua; // guarda base
    matGrua = translate(matGrua, cabina.pos);
    matGrua = rotate(matGrua, DEG_TO_RAD(cabina.angulo_trans), vec3(1, 0, 0));
    matGrua = scale(matGrua, cabina.escalado);

    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, value_ptr(matGrua));
    glUniform3f(colorLoc, cabina.color[0], cabina.color[1], cabina.color[2]);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, cabina.textura);
    glBindVertexArray(VAOCubo);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindTexture(GL_TEXTURE_2D, 0);

    // ----------------------
    // FOCO SUPERIOR
    // ----------------------
    matGrua = matAux;
    matGrua = translate(matGrua, foco.pos);
    matGrua = rotate(matGrua, DEG_TO_RAD(foco.angulo_trans), vec3(1, 0, 0));
    matGrua = scale(matGrua, foco.escalado);

    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, value_ptr(matGrua));

    // Cambia el color del foco según la velocidad del vehículo
    if (base.velocidad == 0) {
        foco.color = { RGB_TO_FLOAT(0), RGB_TO_FLOAT(0), RGB_TO_FLOAT(0) }; // apagado
    }
    else if (base.velocidad < 0) {
        foco.color = { RGB_TO_FLOAT(255), RGB_TO_FLOAT(0), RGB_TO_FLOAT(0) }; // rojo
    }
    else {
        foco.color = { RGB_TO_FLOAT(0), RGB_TO_FLOAT(255), RGB_TO_FLOAT(0) }; // verde
    }
    glUniform3f(colorLoc, foco.color[0], foco.color[1], foco.color[2]);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, foco.textura);
    glBindVertexArray(VAOCubo);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindTexture(GL_TEXTURE_2D, 0);

    // ----------------------
    // PARABRISAS
    // ----------------------
    matGrua = matAux;
    matGrua = translate(matGrua, parabrisas.pos);
    matGrua = rotate(matGrua, DEG_TO_RAD(parabrisas.angulo_trans), vec3(1, 0, 0));
    matGrua = scale(matGrua, parabrisas.escalado);

    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, value_ptr(matGrua));
    glUniform3f(colorLoc, parabrisas.color[0], parabrisas.color[1], parabrisas.color[2]);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, parabrisas.textura);
    glBindVertexArray(VAOCubo);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindTexture(GL_TEXTURE_2D, 0);

    // ----------------------
    // FARO
    // ----------------------
    matGrua = matAux;
    matGrua = translate(matGrua, faro.pos);
    matGrua = rotate(matGrua, DEG_TO_RAD(faro.angulo_trans), vec3(1, 0, 0));
    matGrua = scale(matGrua, faro.escalado);

    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, value_ptr(matGrua));
    glUniform3f(colorLoc, faro.color[0], faro.color[1], faro.color[2]);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, faro.textura);
    glBindVertexArray(VAOCubo);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindTexture(GL_TEXTURE_2D, 0);

    // ----------------------
    // ARTICULACIÓN 1 (rotación eje Y)
    // ----------------------
    matGrua = matAux;
    matGrua = translate(matGrua, articulacion1.pos);
    matGrua = rotate(matGrua, DEG_TO_RAD(articulacion1.angulo_trans), vec3(0, 1, 0));
    matGrua = scale(matGrua, articulacion1.escalado);

    mat4 matArticulacion1 = matGrua;
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, value_ptr(matGrua));
    glUniform3f(colorLoc, articulacion1.color[0], articulacion1.color[1], articulacion1.color[2]);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, articulacion1.textura);
    glBindVertexArray(VAOEsfera);
    glDrawArrays(GL_TRIANGLES, 0, 1080);
    glBindTexture(GL_TEXTURE_2D, 0);

    // ----------------------
    // ARTICULACIÓN 2 (rotación eje Z)
    // ----------------------
    matGrua = matArticulacion1;
    matGrua = translate(matGrua, articulacion2.pos);
    matGrua = rotate(matGrua, DEG_TO_RAD(articulacion2.angulo_trans), vec3(0, 0, 1));
    matGrua = scale(matGrua, articulacion2.escalado);

    mat4 matArticulacion2 = matGrua;
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, value_ptr(matGrua));
    glUniform3f(colorLoc, articulacion2.color[0], articulacion2.color[1], articulacion2.color[2]);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, articulacion2.textura);
    glBindVertexArray(VAOEsfera);
    glDrawArrays(GL_TRIANGLES, 0, 1080);
    glBindTexture(GL_TEXTURE_2D, 0);

    // ----------------------
    // BRAZO
    // ----------------------
    matArticulacion2 = translate(matArticulacion2, brazo.pos);
    matArticulacion2 = rotate(matArticulacion2, DEG_TO_RAD(brazo.angulo_trans), vec3(1, 0, 0));
    matArticulacion2 = scale(matArticulacion2, brazo.escalado);

    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, value_ptr(matArticulacion2));
    glUniform3f(colorLoc, brazo.color[0], brazo.color[1], brazo.color[2]);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, brazo.textura);
    glBindVertexArray(VAOCubo);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindTexture(GL_TEXTURE_2D, 0);

    // ----------------------
    // RUEDAS
    // ----------------------
    matGrua = matAux;
    dibujarRuedas(matGrua); // función externa que dibuja todas las ruedas

}


// Configura la iluminación para el modo diurno
void iluminacionDiurn() {
    // Establece el color de fondo del "cielo" en modo diurno (cielo celeste)
    glClearColor(RGB_TO_FLOAT(85), RGB_TO_FLOAT(228), RGB_TO_FLOAT(249), 1);

    // Obtiene la ubicación del uniform 'iluminacionNocturna' en el shader y lo desactiva (modo día)
    unsigned int soloAmbienteLoc = glGetUniformLocation(shadersProgram, "iluminacionNocturna");
    glUniform1i(soloAmbienteLoc, 0);  // 0 = falso

    // Define el color de la luz en modo día: luz blanca ambiental
    unsigned int lightLoc = glGetUniformLocation(shadersProgram, "lightColor");
    glUniform3f(lightLoc, 1.f, 1.f, 1.f);  // Luz blanca completa (RGB 1,1,1)
}

// Configura la iluminación para el modo nocturno, incluyendo una luz tipo spotlight
void iluminacionNocturn() {
    // Establece el color de fondo oscuro para simular la noche
    glClearColor(RGB_TO_FLOAT(10), RGB_TO_FLOAT(10), RGB_TO_FLOAT(10), 1);

    // Activa la iluminación nocturna (solo luz ambiental y spotlight)
    unsigned int soloAmbienteLoc = glGetUniformLocation(shadersProgram, "iluminacionNocturna");
    glUniform1i(soloAmbienteLoc, 1);  // 1 = verdadero

    // Establece la posición de la fuente de luz (por ejemplo, un faro de la grúa)
    unsigned int lightPosLoc = glGetUniformLocation(shadersProgram, "lightPos");
    glUniform3f(lightPosLoc, base.pos[0], base.pos[1], base.pos[2]);

    // Define la dirección en la que apunta la luz (basada en el ángulo de rotación de la base)
    unsigned int lightDirLoc = glGetUniformLocation(shadersProgram, "luzDir");
    glUniform3f(lightDirLoc,
        sin(DEG_TO_RAD(base.angulo_trans)), // dirección X
        0,                                  // dirección Y fija (plana)
        cos(DEG_TO_RAD(base.angulo_trans))  // dirección Z
    );

    // Establece el color de la luz (puede cambiar dependiendo del tipo de foco usado)
    unsigned int lightColorLoc = glGetUniformLocation(shadersProgram, "lightColor");
    glUniform3f(lightColorLoc, faro.color[0], faro.color[1], faro.color[2]);

    // Ángulo interno del foco (cut-off brusco del cono de luz)
    unsigned int innerCutOffLoc = glGetUniformLocation(shadersProgram, "innerCutOff");
    glUniform1f(innerCutOffLoc, cos(glm::radians(15.0f)));  // Luz fuerte dentro de 15°

    // Ángulo externo del foco (transición gradual a oscuridad)
    unsigned int outerCutOffLoc = glGetUniformLocation(shadersProgram, "outerCutOff");
    glUniform1f(outerCutOffLoc, cos(glm::radians(20.0f)));  // De 15° a 20° se desvanece
}


// Configuración inicial de OpenGL
void iniciar() {
    // Defino el color de fondo utilizando valores RGB convertidos a float (escala 0-1)
    glClearColor(RGB_TO_FLOAT(85), RGB_TO_FLOAT(228), RGB_TO_FLOAT(249), 1);

    // Configuro la profundidad inicial de la escena
    glClearDepth(1.0f);

    // Habilito el test de profundidad para que los objetos 3D se rendericen correctamente
    glEnable(GL_DEPTH_TEST);

    // Habilito la eliminación de caras traseras para mejorar el rendimiento
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

   
}


// Función principal
int main(int argc, char** argv) {
    // Inicializo GLFW
    if (!glfwInit()) {
        std::cerr << "Error al inicializar GLFW" << std::endl;
        return -1;
    }

    // Especifico la versión de OpenGL a usar (3.3 Core Profile)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Creo una ventana GLFW
    GLFWwindow* window = glfwCreateWindow(W_WIDTH, W_HEIGHT, "Grua", NULL, NULL);

    // Verifico si la ventana se creó correctamente
    if (!window) {
        std::cerr << "Error al crear la ventana" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Establezco la ventana como el contexto actual
    glfwMakeContextCurrent(window);

    // Cargo los punteros de funciones OpenGL con GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Error al inicializar GLAD" << std::endl;
        return -1;
    }

    // Defino el viewport de la ventana
    glViewport(0, 0, W_WIDTH, W_HEIGHT);

    // Asigno los callbacks de teclado y redimensionamiento de ventana
    glfwSetKeyCallback(window, keyCallback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Inicializo configuraciones de OpenGL
    iniciar();
    iniciarTexturas();

    // Cargo y compilo los shaders desde archivos externos
    shadersProgram = setShaders("shader.vert", "shader.frag");

    glUseProgram(shadersProgram);

    glUniform1i(glGetUniformLocation(shadersProgram, "objectTexture"), 0);
    glUniform1i(glGetUniformLocation(shadersProgram, "objectTexture2"), 1);

    // Genero los modelos básicos para renderizar la escena
    crearCubo();
    crearCuadrado();
    crearEsfera();

    

    // Bucle principal de renderizado
    while (!glfwWindowShouldClose(window)) {
        // Procesar la entrada del usuario
        processInput(window);

        // Limpio los buffers de color y profundidad antes de renderizar la nueva escena
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Configuro la cámara según el modo seleccionado
        switch (modoCamara) {
        case 1:
            myCamaraExterior(W_WIDTH, W_HEIGHT);
            break;
        case 2:
            myCamaraPrimeraPersona(W_WIDTH, W_HEIGHT, base.pos[0], base.pos[1], base.pos[2], base.angulo_trans);
            break;
        case 3:
            myCamaraTerceraPersona(W_WIDTH, W_HEIGHT, base.pos[0], base.pos[1], base.pos[2], base.angulo_trans);
            break;
        }

        if (iluminacionNoct==1) iluminacionNocturn();
        else iluminacionDiurn();


        // Llamo a la función de dibujado de la escena
        display();

        // Intercambio los buffers para mostrar la imagen renderizada en pantalla
        glfwSwapBuffers(window);

        // Procesar los eventos de la ventana
        glfwPollEvents();
    }

    // Limpio los recursos de OpenGL al cerrar la aplicación
    glDeleteVertexArrays(1, &VAOCubo);
    glDeleteVertexArrays(1, &VAOCuadrado);
    glDeleteVertexArrays(1, &VAOEsfera);

    // Termino GLFW y libero recursos
    glfwTerminate();
    return 0;
}




void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    // Almacena el estado de la tecla (presionada o liberada)
    teclas[key] = (action != GLFW_RELEASE);
    teclas2[key] = (action == GLFW_RELEASE);


    if (teclas2[GLFW_KEY_A]) {
        giroDerecha = 0;
    }

    if (teclas2[GLFW_KEY_D]) {
        giroIzquierda = 0;
    }
    // Controles de movimiento y rotación
    if (teclas[GLFW_KEY_A]) {
        base.angulo_trans += 4;
        giroDerecha = 1;
    }
    if (teclas[GLFW_KEY_D]) {
        base.angulo_trans -= 4;
        giroIzquierda = 1;
    }
    if (teclas[GLFW_KEY_W]) base.velocidad++;
    if (teclas[GLFW_KEY_S]) base.velocidad--;

    // Controles de articulaciones
    if (teclas[GLFW_KEY_I]) articulacion2.angulo_trans--;
    if (teclas[GLFW_KEY_K]) articulacion2.angulo_trans++;
    if (teclas[GLFW_KEY_J]) articulacion1.angulo_trans--;
    if (teclas[GLFW_KEY_L]) articulacion1.angulo_trans++;

    // Controles de ángulos de cámara
    if (teclas[GLFW_KEY_UP]) beta++;
    if (teclas[GLFW_KEY_DOWN]) beta--;
    if (teclas[GLFW_KEY_LEFT]) alpha--;
    if (teclas[GLFW_KEY_RIGHT]) alpha++;

    // Modificación de la distancia
    if (teclas[47]) DISTANCIA += 1.0f;
    if (teclas[93]) DISTANCIA = std::max(1.0f, DISTANCIA - 1.0f); // Evita valores negativos

    // Cambio de modo de cámara
    if (teclas[GLFW_KEY_1]) modoCamara = 1;
    if (teclas[GLFW_KEY_2]) modoCamara = 2;
    if (teclas[GLFW_KEY_3]) modoCamara = 3;

    if (teclas[GLFW_KEY_N]) {
        iluminacionNoct = !iluminacionNoct;
    }
}

// Procesar la entrada del usuario
void processInput(GLFWwindow* window) {
    // Si presiono la tecla ESC, cierro la ventana
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}


// Función para ajustar la ventana y la proyección
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height); // Actualiza el tamaño del viewport

    W_WIDTH = width;
    W_HEIGHT = height;

    switch (modoCamara) {
    case 1:
        myCamaraExterior(width, height); // Si necesita algún parámetro específico, actualízalo aquí
        break;
    case 2:
        myCamaraPrimeraPersona(width, height, base.pos[0], base.pos[1], base.pos[2], base.angulo_trans);
        break;
    case 3:
        myCamaraTerceraPersona(width, height, base.pos[0], base.pos[1], base.pos[2], base.angulo_trans);
        break;
    }
}

// Función para manejar el tiempo de ejecución
void tiempo() {
    static float unSegundo = 0;
    currentTime = glfwGetTime();
    nbFrames++;
    lapsoTime = currentTime - lastTime;
    unSegundo += lapsoTime;
    if (unSegundo >= 1.0) {
        printf("%f frame/s\n", double(nbFrames));
        nbFrames = 0;
        unSegundo = 0;
    }

    lastTime = currentTime;
}



// Función para cargar una textura desde un archivo de imagen
GLuint cargaTextura(const char* nombre) {
    GLuint textura;

    // Genera un identificador para la textura
    glGenTextures(1, &textura);

    // Activa (vincula) la textura como una textura 2D
    glBindTexture(GL_TEXTURE_2D, textura);

    // Configura el modo de envoltura (wrapping) en S y T (horizontal y vertical) a repetición
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Establece el tipo de filtrado para minimizar y magnificar la textura
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Suavizado al reducir tamaño
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Suavizado al aumentar tamaño

    // Indica que la imagen se debe voltear verticalmente al cargar
    stbi_set_flip_vertically_on_load(1);

    // Variables para almacenar las dimensiones y canales de color de la imagen
    int width, height, nrChannels;

    // Carga la imagen usando stb_image
    unsigned char* data = stbi_load(nombre, &width, &height, &nrChannels, 0);

    // Si se cargó correctamente la imagen
    if (data) {
        GLenum format;

        // Determina el formato de la textura según el número de canales
        if (nrChannels == 1) format = GL_RED;
        else if (nrChannels == 3) format = GL_RGB;
        else if (nrChannels == 4) format = GL_RGBA;
        else format = GL_RGB; // Por defecto

        // Crea la textura en memoria de video
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

        // Genera los mipmaps automáticamente (niveles de detalle)
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        // Si falla la carga, imprime un mensaje de error
        printf("Error cargando textura: %s\n", nombre);
        printf("stbi_failure_reason: %s\n", stbi_failure_reason());
    }

    // Libera la memoria de la imagen cargada
    stbi_image_free(data);

    // Devuelve el ID de la textura generada
    return textura;
}



//Funcion para inicizalicar las texturas
void iniciarTexturas() {
    terreno.textura = cargaTextura("terrenos.png");
    base.textura = cargaTextura("base.jpg");
    cabina.textura = cargaTextura("base.jpg");
    articulacion1.textura = cargaTextura("articulacion.jpg");
    articulacion2.textura = cargaTextura("articulacion.jpg");
    brazo.textura = cargaTextura("brazo.jpg");

    parabrisas.textura = cargaTextura("parabrisas.png");

    foco.textura = cargaTextura("faro.jpg");

    faro.textura = cargaTextura("faro.jpg");

    planta1.textura = cargaTextura("planta.png");
    planta2.textura = cargaTextura("planta.png");
    planta3.textura = cargaTextura("planta.png");
    planta4.textura = cargaTextura("planta.png");
    planta5.textura = cargaTextura("planta.png");

    cactus1.textura = cargaTextura("cactus.jpg");
    cactus2.textura = cargaTextura("cactus.jpg");
    cactus3.textura = cargaTextura("cactus.jpg");
    cactus4.textura = cargaTextura("cactus.jpg");

    balazos = cargaTextura("balazos.png");
   
}