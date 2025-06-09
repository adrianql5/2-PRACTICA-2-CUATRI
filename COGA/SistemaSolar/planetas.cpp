#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include <windows.h>	
#include <glut.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>


#define MAX_SATELITES 10


typedef struct Planeta {
    char nombre[15];
    float tamano;

    float velocidadTraslacion;
    float velocidadRotacion;

    float anguloTraslacion;
    float anguloRotacion;

    float posicion[3];
    float color[3];

    float distanciaOrbita;
    int nSatelites;
    struct Planeta* satelites[MAX_SATELITES];
    Planeta* padre;

    int lista;
    
    GLuint textura;

} Planeta;


GLuint cargaTextura(const char* nombre){
    GLuint textura;
    glGenTextures(1, &textura);
    glBindTexture(GL_TEXTURE_2D, textura);

    // Configuración de wrapping y filtrado
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Invertir imagen verticalmente al cargar (OpenGL lo necesita)
    stbi_set_flip_vertically_on_load(1);

    int width, height, nrChannels;
    unsigned char* data = stbi_load(nombre, &width, &height, &nrChannels, 0);

    if (data)
    {
        if (nrChannels == 3)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            //glGenerateMipmap(GL_TEXTURE_2D); // Si quieres mipmaps
        }
        if (nrChannels == 4)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            //glGenerateMipmap(GL_TEXTURE_2D); // Si quieres mipmaps
        }

    }
    else {
        printf("Error en las texturas.\n");
    }

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


    strncpy_s(nuevoPlaneta->nombre, sizeof(nuevoPlaneta->nombre), nombre, _TRUNCATE);


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
