/*

    Codigo escrito por Adrián Quiroga Linares

*/


#include "planetas.h"
#include "figuras.h"
#include "camaraTeclado.h"
#include <stdio.h>
#include <math.h>
#include <SOIL.h>

#define PI 3.14159265359
#define MYTIEMPO 1  // Define el intervalo de tiempo  entre cada actualización

extern int dibujarOrbitas;
extern int dibujarEjes;
extern int iluminacion;
extern int luzEncendida;


const int W_WIDTH = 500;
const int W_HEIGHT = 500;

// Array de astros global que se inicializa en el main llamando a la función crearSistema
Planeta** sistemaSolar; 


float calcularVelocidadTranslacion(float num){
        
        return (360 / num) * 0.01;
}

float calcularVelocidadRotacion(float num){
        return (((360 / num) * 0.005));
}

// Funcion que inicaliza los datos de todos los astros que apareceran en el sistema solar. Es un array de planetas. Los datos tratan de ser lo más realistas posibles.
Planeta ** crearSistema(){
        
        Planeta **arr = (Planeta **) malloc(11 * sizeof(Planeta *));
        if (!arr) {
                printf("Error: No se pudo asignar memoria para el sistema solar\n");
                return NULL;
        }

       
        float colorSol[3] = { 1.0f, 1.0f, 1.0f }; // Amarillo
        float colorMercurio[3] = { 1.0f, 1.0f, 1.0f }; // Gris
        float colorVenus[3] = { 1.0f, 1.0f, 1.0f }; // Naranja
        float colorTierra[3] = { 1.0f, 1.0f, 1.0f }; // Azul
        float colorLuna[3] = { 1.0f, 1.0f, 1.0f }; // Gris claro
        float colorISS[3] = { 1.0f, 1.0f, 1.0f }; // Gris
        float colorMarte[3] = { 1.0f, 1.0f, 1.0f }; // Rojo
        float colorJupiter[3] = { 1.0f, 1.0f, 1.0f }; // Marrón
        float colorSaturno[3] = { 1.0f, 1.0f, 1.0f }; // Beige
        float colorUrano[3] = { 1.0f, 1.0f, 1.0f }; // Azul claro


        
        arr[0] = crearPlaneta("sol", 35.0f, 0.0f, 0.0f, colorSol, 0.0f, NULL, myEsfera(), "sol.jpg"); // El Sol no orbita a nada

        
        arr[1] = crearPlaneta("mercurio", 3.5f, calcularVelocidadTranslacion(87.0), calcularVelocidadRotacion(1), colorMercurio, 62.387f, arr[0], myEsfera(), "mercurio.jpg"); // Orbita el Sol
        arr[2] = crearPlaneta("venus", 9.0f, calcularVelocidadTranslacion(225), calcularVelocidadRotacion(1), colorVenus, 115.723f, arr[0], myEsfera(), "venus.jpg"); // Orbita el Sol
        arr[3] = crearPlaneta("tierra", 9.7f,calcularVelocidadTranslacion(365), calcularVelocidadRotacion(1), colorTierra, 168.0f, arr[0], myEsfera(), "tierra.jpg"); // Orbita el Sol
        arr[4] = crearPlaneta("luna", 3.f, calcularVelocidadTranslacion(160), calcularVelocidadRotacion(1), colorLuna, 30.0f, arr[3], myEsfera(), "luna.jpg"); // Orbita la Tierra
        arr[5] = crearPlaneta("iss", 1.0f, 0.0f, calcularVelocidadRotacion(0.25), colorISS, 20.0f, arr[3], myISS(), "iss.jpg"); // Orbita la Tierra
        arr[6] = crearPlaneta("marte", 5.5f, calcularVelocidadTranslacion(687), calcularVelocidadRotacion(1), colorMarte, 228.524f, arr[0], myEsfera(), "marte.jpg"); // Orbita el Sol
        arr[7] = crearPlaneta("jupiter", 21.0f, calcularVelocidadTranslacion(1298.4), calcularVelocidadRotacion(1), colorJupiter, 333.4f, arr[0], myEsfera(), "jupiter.jpg"); // Orbita el Sol
        arr[8] = crearPlaneta("saturno", 18.0f, calcularVelocidadTranslacion(3225.6), calcularVelocidadRotacion(1), colorSaturno, 428.1f, arr[0], mySaturno(18.0f), "saturno.jpg"); // Orbita el Sol
        arr[9] = crearPlaneta("urano", 12.5f, calcularVelocidadTranslacion(3066.4), calcularVelocidadRotacion(1), colorUrano, 649.1f, arr[0], myEsfera(), "urano.jpg"); // Orbita el Sol

        arr[10] = NULL;

        return arr;
}

//Libero los recursos asociados al sistema tras la ejecución dle programa.
void destruirSistema(Planeta **sistema){
        if (!sistema)
                return;
        for (int i = 0; sistema[i] != NULL; i++) {
                free(sistema[i]);
        }
        free(sistema);
}



// Función que dibuja las órbitas de todos los planetas
void dibujarOrbita(float radio, float inclinacion){
        glDisable(GL_TEXTURE_2D);
        int n = 360;
        glPushMatrix();
        glColor3f(1.0f, 1.0f, 1.0f);

        glBegin(GL_LINE_LOOP);
        for (int i = 0; i < n; i++) {
                //Mediante estas formulas pinto un loop de puntos.
                float angulo = (i * 2 * PI) / n;
                float x = radio * cos(angulo);
                float z = radio * sin(angulo);
                float y = sin(inclinacion) * z; // Aplicamos inclinación en Y
                z = cos(inclinacion) * z; // Ajustamos la nueva coordenada Z
                glVertex3f(x, y, z);
        }
        glEnd();

        glPopMatrix();
        glEnable(GL_TEXTURE_2D);
}

// Funcion que calcula la posicion de un planeta dado.
void calcularPosicion(Planeta *p){
        if (p == nullptr)
                return;

        float x=0, y=0, z=0;

        // Aplico la inclinación si es la Luna o la ISS
        float inclinacion = 0.0f;
        if (strcmp(p->nombre, "luna") == 0)
                inclinacion = 45.0f * PI / 180.0f;
        else if (strcmp(p->nombre, "iss") == 0)
                inclinacion = 25.0f * PI / 180.0f;

        x = p->distanciaOrbita * cos(p->anguloTraslacion);
        y = sin(inclinacion) * p->distanciaOrbita * sin(p->anguloTraslacion) ;
        z = p->distanciaOrbita * sin(p->anguloTraslacion) * cos(inclinacion);

        // Guardo la nueva posición
        p->posicion[0] = x;
        p->posicion[1] = y;
        p->posicion[2] = z;
}






//Función más importante del programa. Se plantea de forma recursiva lo que permite ahorrar muchas líneas de código, puesto que sabemos que cada planeta orbita a otro a excepción del sol
void dibujarPlaneta(Planeta *p){
        if (iluminacion) glEnable(GL_LIGHTING);
        else glDisable(GL_LIGHTING);

        if (p == nullptr) //si p es null salgo de la llamada recursiva
                return;

        //Guardo la matriz donde me sitúo actualmente
        glPushMatrix();
        if (strcmp(p->nombre, "sol")==0 && luzEncendida) glDisable(GL_LIGHTING);
            float inclinacion = 0.0;
            if (strcmp(p->nombre, "luna") == 0)
                    inclinacion = 45.0 * PI / 180.0;
            else if (strcmp(p->nombre, "iss") == 0)
                    inclinacion = 25.0 * PI / 180.0;

            // En caso de querer dibujar las órbitas se dibujan
            if (dibujarOrbitas) dibujarOrbita(p->distanciaOrbita, inclinacion);

            // traslado el planeta a su posición
            glTranslatef(p->posicion[0], p->posicion[1], p->posicion[2]);
            
            // guardo la matriz
            glPushMatrix();
                //lo roto
                glRotatef(p->anguloRotacion, 0, 1, 0);

                //lo escalo
                glScalef(p->tamano, p->tamano, p->tamano);

                // en caso de quererlo se dibujan los ejes
                if (dibujarEjes) myEjes();

                // asigno los colores
                glColor3f(p->color[0], p->color[1], p->color[2]);

                glBindTexture(GL_TEXTURE_2D, p->textura);
               
                //mediante la llamada a la lista pinto el planeta
                glCallList(p->lista);
                
                if (strcmp(p->nombre, "sol")==0) glEnable(GL_LIGHTING);
            glPopMatrix();

            // llamo recursivamente a la funcion para pintar sus satélites
            for (int i = 0; i < p->nSatelites; i++) {
                   dibujarPlaneta(p->satelites[i]);
            }
        
       glPopMatrix();
}

// funcion equivalente a myDisplay() 
void dibujoSistemaSolar(){

        //Limpio los buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Llamo a la matriz del modelo y cargo la identidad
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        //Llamo a myCamara
        myCamara((float) glutGet(GLUT_WINDOW_WIDTH) / (float) glutGet(GLUT_WINDOW_HEIGHT), sistemaSolar, 10);;        

        //Encuentro el sol y lo dibujo, esto implica que tambien se van a dibujar sus satelites (los planetas) y los satelites de sus satelites (luna,ISS)
        Planeta *sol = encontrarPlaneta(sistemaSolar, 10, "sol");
        dibujarPlaneta(sol);

        //intercambio los buffers y fuerzo la impresión
        glutSwapBuffers();
        glFlush();
}

// funcion que va a actualizar la posicion de los planetas
void actualizar(int n){
        for (int i = 0; i < 10; i++) {
            if (sistemaSolar[i] != NULL) {
                   sistemaSolar[i]->anguloTraslacion += sistemaSolar[i]->velocidadTraslacion;
                   if (sistemaSolar[i]->anguloTraslacion > 360)
                           sistemaSolar[i]->anguloTraslacion -= 360;
                   sistemaSolar[i]->anguloRotacion += sistemaSolar[i]->velocidadRotacion;
                   if (sistemaSolar[i]->anguloRotacion > 360)
                            sistemaSolar[i]->anguloRotacion -= 360;
                   //calculamos la posicion del planeta
                   calcularPosicion(sistemaSolar[i]);
            }
        }

        //Redibujo la escena
        glutPostRedisplay();
        
        //refrescamos de nuevo
        glutTimerFunc(MYTIEMPO, actualizar, 10);
}


//no pongo el cuttoff porque es una fuente puntual de luz, no un foco puntual
void iniciarLuces() {
    // Luz ambiental: débil pero presente en toda la escena
    GLfloat luzAmbiente[] = { 0.2f, 0.2f, 0.2f, 1.0f };

    // Luz difusa: luz amarilla que reciben los planetas desde el Sol
    GLfloat luzDifusa[] = { 1.0f, 1.0f, 0.8f, 1.0f };

    // Luz especular: reflejos blancos en los objetos con brillo
    GLfloat luzEspecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    // Posición del Sol (luz puntual en el origen)
    GLfloat luzPosicion[] = { 0.0f, 0.0f, 0.0f, 1.0f };

    // Configuración de la luz ambiental, difusa y especular
    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
    glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);

    // Definir la posición de la luz (en el origen, donde está el Sol)
    glLightfv(GL_LIGHT0, GL_POSITION, luzPosicion);

    // Configuración de atenuación 
    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0f);  // Mantiene algo de iluminación constante
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.0005f); // Atenuación leve con la distancia
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.00002f); // Mayor atenuación para planetas lejanos

    // Habilitar iluminación y modelo de sombreado suave para transiciones de luz más naturales
    glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);

    // Activar la luz principal del Sol
    glEnable(GL_LIGHT0);

    // Permitir que los materiales respondan a la luz de manera realista
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    // Configuración de materiales para los planetas
    GLfloat mat_ambiente[] = { 0.3f, 0.3f, 0.3f, 1.0f };  // Reflejo ambiental leve
    GLfloat mat_difuso[] = { 0.6f, 0.6f, 0.6f, 1.0f };    // Tono medio para los planetas
    GLfloat mat_especular[] = { .5f, .5f, .5f, .5f }; // Brillo especular suave
    GLfloat mat_brillo = 32.0f;  // Nivel de brillo especular

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambiente);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_difuso);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_especular);
    glMaterialf(GL_FRONT, GL_SHININESS, mat_brillo);
}


void iniciar(){
        glClearColor(0, 0, 0, 1); //limpio la pantalla con negro
        glClearDepth(1.0f); //Especifico el valor de  limpieza del z-buffer

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        
        glEnable(GL_NORMALIZE); // Normaliza las normales automáticamente

        glEnable(GL_TEXTURE_2D);


        glutKeyboardFunc(myTeclado); //asgina la funcion que gestiona el teclado
        glutSpecialFunc(moverCamara); //Asigno la de la camara
}



//funcion para cuando cambie de tamaño la pantalla
void reshape(GLint newWidth, GLint newHeight){
        //establezco el area de visualizacion de opengl segun el nuevo tamaño de la ventana
        glViewport(0, 0, newWidth, newHeight);

        //Ajusto la camara dados los nuevos datos
        myCamara((float) newWidth / (float) newHeight, sistemaSolar, 10);

        //redibujo la escena
        glutPostRedisplay();
}

int main(int argc, char **argv){
        glutInit(&argc, argv); //incio glut

        glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE); //indico que uso rgba y double buffer

        glutInitWindowSize(W_WIDTH, W_HEIGHT); //indico las dimensiones inciales de la pantalla
        glutInitWindowPosition(100, 100); //Especifico la posicion inicial
        glutCreateWindow("SISTEMA SOLAR");

        iniciar();
        iniciarLuces();
        crearMenu();

        //creo el sistema solar
        sistemaSolar = crearSistema();

        glutDisplayFunc(dibujoSistemaSolar); //le digo que el display va ser la funcion que dibuja el sistema solar
        glutReshapeFunc(reshape); //especifico la funcion de reshape de la pantalla
        glutTimerFunc(MYTIEMPO, actualizar, 10); //indico la funcion que refresca la escena periodicamente

        glutMainLoop(); //bucle infinito para mostrar la imagen en pantalla

        destruirSistema(sistemaSolar); //libero memoria
        return 0;
}
