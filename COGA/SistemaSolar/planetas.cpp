// Copyright (c) 2025 Adrian Quiroga Linares. Lectura y referencia permitidas; reutilizacion y plagio prohibidos.

#include "planetas.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

static std::string resolverRutaTextura(const char* nombre) {
    const std::string candidatos[] = {
        std::string(nombre),
        std::string("SistemaSolarFinal/") + nombre
    };

    for (const std::string& ruta : candidatos) {
        FILE* archivo = fopen(ruta.c_str(), "rb");
        if (archivo != NULL) {
            fclose(archivo);
            return ruta;
        }
    }

    return std::string(nombre);
}


GLuint cargaTextura(const char* nombre){
    const std::string ruta = resolverRutaTextura(nombre);
    stbi_set_flip_vertically_on_load(1);

    int width = 0;
    int height = 0;
    int channels = 0;
    unsigned char* data = stbi_load(ruta.c_str(), &width, &height, &channels, 0);

    if (data == NULL) {
        printf("Error cargando la textura '%s': %s\n", ruta.c_str(), stbi_failure_reason());
        return 0;
    }

    GLenum formato = GL_RGB;
    if (channels == 1) {
        formato = GL_RED;
    } else if (channels == 3) {
        formato = GL_RGB;
    } else if (channels == 4) {
        formato = GL_RGBA;
    }

    GLuint textura = 0;
    glGenTextures(1, &textura);
    glBindTexture(GL_TEXTURE_2D, textura);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, formato, width, height, 0, formato, GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);

    return textura;
}


//Constructor del planeta que incializa todos sus atributos yd evuelveun puntero a el
Planeta* crearPlaneta(const char nombre[15], float tamano, float velocidadTraslacion, float velocidadRotacion,
    float color[3], float distanciaOrbita, Planeta* padre, int lista, const char * archivoTextura) {

    Planeta* nuevoPlaneta = (Planeta*)malloc(sizeof(Planeta));
    if (!nuevoPlaneta) {
        printf("Error: No se pudo asignar memoria para el planeta\n");
        return NULL;
    }


    strncpy(nuevoPlaneta->nombre, nombre, sizeof(nuevoPlaneta->nombre) - 1);
    nuevoPlaneta->nombre[sizeof(nuevoPlaneta->nombre) - 1] = '\0';


    // Inicializar propiedades del planeta
    nuevoPlaneta->tamano = tamano;
    nuevoPlaneta->velocidadTraslacion = velocidadTraslacion;
    nuevoPlaneta->velocidadRotacion = velocidadRotacion;
    nuevoPlaneta->anguloTraslacion = 0.0f;
    nuevoPlaneta->anguloRotacion = 0.0f;
    nuevoPlaneta->distanciaOrbita = distanciaOrbita;
    nuevoPlaneta->nSatelites = 0; // Se inicializa a 0

    memcpy(nuevoPlaneta->color, color, 3 * sizeof(float));
    nuevoPlaneta->padre = padre;
    nuevoPlaneta->lista=lista;

    if (archivoTextura != NULL) {
        nuevoPlaneta->textura = cargaTextura(archivoTextura);
    }
    else {
        nuevoPlaneta->textura = 0; // O algún valor por defecto
    }

    // Inicializar la lista de satélites con NULL
    for (int i = 0; i < MAX_SATELITES; i++) {
        nuevoPlaneta->satelites[i] = NULL;
    }

    // Verificar que planetaQueOrbita no sea NULL antes de acceder a él
    if (padre != NULL) {
        if (padre->nSatelites < MAX_SATELITES) {
            padre->satelites[padre->nSatelites] = nuevoPlaneta;
            padre->nSatelites++;
        }
        else {
            printf("Advertencia: %s no puede tener más de %d satélites.\n", padre->nombre, MAX_SATELITES);
        }
    }

    return nuevoPlaneta;
}


//setter de la posicion
void modificarPosicion(Planeta* p, float posicion[3]) {
    memcpy(p->posicion, posicion, 3 * sizeof(float));
}



//devuelve un planeta dado su nombre y un array de planetas
Planeta* encontrarPlaneta(Planeta** arr, int nPlanetas, const char* nombre) {
    for (int i = 0; i < nPlanetas; i++) {
        if (arr[i] != NULL && strcmp(arr[i]->nombre, nombre) == 0) {
            return arr[i];
        }
    }
    return NULL; // Si no se encuentra, devuelve NULL
}
