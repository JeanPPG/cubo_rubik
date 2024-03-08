#include "include/rotaciones.h"
#include "include/rubik.h"
#include "include/cubito.h"
#include "include/algoritmos.h"
#include "include/timer.h"

#include <GL/glut.h>
#include <GL/freeglut.h>
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <sstream>


Timer timer; // Declarar una instancia global de Timer
Rubik cuboRubik; // Objeto de la clase Rubik que representa el cubo de Rubik

float radioCamara = 10.0f; // Radio de la c�mara para visualizar el cubo
float anguloCamaraX = 0.0f; // �ngulo de rotaci�n en el eje X de la c�mara
float anguloCamaraY = 0.0f; // �ngulo de rotaci�n en el eje Y de la c�mara

int ultimoMouseX, ultimoMouseY; // �ltima posici�n del mouse
bool arrastrando = false; // Variable para indicar si se est� arrastrando el cubo con el mouse
bool rotacionEnCurso = false; // Variable para indicar si hay una rotaci�n en curso

// Prototipos de funciones
void mostrar();
void redimensionar(int w, int h);
void raton(int boton, int estado, int x, int y);
void movimientoRaton(int x, int y);
void inicializarCubo();
void asignarColoresCubo();
void menu(int eleccion);
void teclado(unsigned char tecla, int x, int y);
void dibujarMiniCubo(float x, float y, float z, MiniCubo::Color frente, MiniCubo::Color atras,
                     MiniCubo::Color arriba, MiniCubo::Color abajo, MiniCubo::Color derecha, MiniCubo::Color izquierda);
void mostrarTimer();

// Funci�n para asignar colores a cada cara del cubo Rubik
void asignarColoresCubo() {
    // Asigna colores fijos para cada cara del cubo Rubik
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 3; ++k) {
                if (i == 1 && j == 1 && k == 1) // El centro del cubo no tiene colores
                    continue;

                // Asigna colores seg�n la posici�n del cubo en el arreglo
                cuboRubik.cubos[i][j][k].arriba = MiniCubo::AMARILLO; // Verde
                cuboRubik.cubos[i][j][k].abajo = MiniCubo::BLANCO; // Azul
                cuboRubik.cubos[i][j][k].frente = MiniCubo::ROJO;
                cuboRubik.cubos[i][j][k].atras = MiniCubo::NARANJA;
                cuboRubik.cubos[i][j][k].derecha = MiniCubo::VERDE; // Amarillo
                cuboRubik.cubos[i][j][k].izquierda = MiniCubo::AZUL; // Blanco
            }
        }
    }
}

void dibujarMiniCubo(float x, float y, float z, MiniCubo::Color frente, MiniCubo::Color atras,
                     MiniCubo::Color arriba, MiniCubo::Color abajo, MiniCubo::Color derecha, MiniCubo::Color izquierda) {
    GLfloat colores[6][3] = {
        {0.8f, 0.8f, 0.8f}, // BLANCO
        {0.8f, 0.8f, 0.0f}, // AMARILLO
        {0.0f, 0.0f, 0.8f}, // ROJO
        {0.0f, 0.8f, 0.0f}, // AZUL
        {0.8f, 0.0f, 0.0f}, // VERDE
        {0.8f, 0.4f, 0.0f}  // NARANJA
    };

    glBegin(GL_QUADS);

    glColor3fv(colores[frente]);
    glVertex3f(x - 0.02f, y - 0.02f, z + 1.02f);
    glVertex3f(x + 1.02f, y - 0.02f, z + 1.02f);
    glVertex3f(x + 1.02f, y + 1.02f, z + 1.02f);
    glVertex3f(x - 0.02f, y + 1.02f, z + 1.02f);

    glColor3fv(colores[atras]);
    glVertex3f(x - 0.02f, y - 0.02f, z - 0.02f);
    glVertex3f(x - 0.02f, y + 1.02f, z - 0.02f);
    glVertex3f(x + 1.02f, y + 1.02f, z - 0.02f);
    glVertex3f(x + 1.02f, y - 0.02f, z - 0.02f);

    glColor3fv(colores[arriba]);
    glVertex3f(x - 0.02f, y + 1.02f, z + 1.02f);
    glVertex3f(x + 1.02f, y + 1.02f, z + 1.02f);
    glVertex3f(x + 1.02f, y + 1.02f, z - 0.02f);
    glVertex3f(x - 0.02f, y + 1.02f, z - 0.02f);

    glColor3fv(colores[abajo]);
    glVertex3f(x - 0.02f, y - 0.02f, z + 1.02f);
    glVertex3f(x + 1.02f, y - 0.02f, z + 1.02f);
    glVertex3f(x + 1.02f, y - 0.02f, z - 0.02f);
    glVertex3f(x - 0.02f, y - 0.02f, z - 0.02f);

    glColor3fv(colores[derecha]);
    glVertex3f(x + 1.02f, y - 0.02f, z + 1.02f);
    glVertex3f(x + 1.02f, y + 1.02f, z + 1.02f);
    glVertex3f(x + 1.02f, y + 1.02f, z - 0.02f);
    glVertex3f(x + 1.02f, y - 0.02f, z - 0.02f);

    glColor3fv(colores[izquierda]);
    glVertex3f(x - 0.02f, y - 0.02f, z + 1.02f);
    glVertex3f(x - 0.02f, y + 1.02f, z + 1.02f);
    glVertex3f(x - 0.02f, y + 1.02f, z - 0.02f);
    glVertex3f(x - 0.02f, y - 0.02f, z - 0.02f);

    glEnd();

    // Dibujar l�neas de separaci�n entre cubos
    glLineWidth(2.0);
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);

    // L�neas horizontales
    glVertex3f(x - 0.02f, y - 0.02f, z + 1.02f);
    glVertex3f(x + 1.02f, y - 0.02f, z + 1.02f);
    glVertex3f(x + 1.02f, y - 0.02f, z - 0.02f);
    glVertex3f(x - 0.02f, y - 0.02f, z - 0.02f);

    glEnd();

    glBegin(GL_LINE_LOOP);

    glVertex3f(x - 0.02f, y - 0.02f, z + 1.02f);
    glVertex3f(x - 0.02f, y + 1.02f, z + 1.02f);
    glVertex3f(x - 0.02f, y + 1.02f, z - 0.02f);
    glVertex3f(x - 0.02f, y - 0.02f, z - 0.02f);

    glVertex3f(x + 1.02f, y - 0.02f, z + 1.02f);
    glVertex3f(x + 1.02f, y + 1.02f, z + 1.02f);
    glVertex3f(x + 1.02f, y + 1.02f, z - 0.02f);
    glVertex3f(x + 1.02f, y - 0.02f, z - 0.02f);

    glEnd();

    glBegin(GL_LINE_LOOP);

    glVertex3f(x - 0.02f, y - 0.02f, z + 1.02f);
    glVertex3f(x + 1.02f, y - 0.02f, z + 1.02f);
    glVertex3f(x + 1.02f, y + 1.02f, z + 1.02f);
    glVertex3f(x - 0.02f, y + 1.02f, z + 1.02f);

    glVertex3f(x - 0.02f, y - 0.02f, z - 0.02f);
    glVertex3f(x + 1.02f, y - 0.02f, z - 0.02f);
    glVertex3f(x + 1.02f, y + 1.02f, z - 0.02f);
    glVertex3f(x - 0.02f, y + 1.02f, z - 0.02f);

    glEnd();
}

/**
 * Funci�n para mostrar el cubo de Rubik en la pantalla.
 * Limpia el b�fer de color y el b�fer de profundidad, ajusta la posici�n de la c�mara y dibuja el cubo de Rubik.
 */
void mostrar() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpiar el b�fer de color y el b�fer de profundidad
    glLoadIdentity(); // Reiniciar la matriz de proyecci�n

    glClearColor(0.5f, 0.5f, 0.5f, 1.0f); // Establecer el color de fondo
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpiar el b�fer de color y el b�fer de profundidad

    // Ajustar la posici�n de la c�mara para que la cara superior apunte hacia arriba
    float camaraX = radioCamara * sin(anguloCamaraY) * cos(anguloCamaraX);
    float camaraY = radioCamara * cos(anguloCamaraY);
    float camaraZ = radioCamara * sin(anguloCamaraY) * sin(anguloCamaraX);
    gluLookAt(camaraX, camaraY, camaraZ, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);

    // Dibujar cada mini cubo del cubo Rubik
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 3; ++k) {
                float x = i - 1.0f;
                float y = j - 1.0f;
                float z = k - 1.0f;

                MiniCubo::Color frente = cuboRubik.cubos[i][j][k].frente;
                MiniCubo::Color atras = cuboRubik.cubos[i][j][k].atras;
                MiniCubo::Color arriba = cuboRubik.cubos[i][j][k].arriba;
                MiniCubo::Color abajo = cuboRubik.cubos[i][j][k].abajo;
                MiniCubo::Color derecha = cuboRubik.cubos[i][j][k].derecha;
                MiniCubo::Color izquierda = cuboRubik.cubos[i][j][k].izquierda;

                dibujarMiniCubo(x, y, z, frente, atras, arriba, abajo, derecha, izquierda);
            }
        }
    }
    mostrarTimer();
    glutSwapBuffers(); // Intercambiar los b�feres
}

/**
 * Funci�n para redimensionar la ventana de visualizaci�n.
 * @param w Ancho de la ventana.
 * @param h Alto de la ventana.
 */
void redimensionar(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 100.0); // Configura la perspectiva de la c�mara
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/**
 * Funci�n de callback para el men�.
 * @param choice La opci�n seleccionada en el men�.
 */
 // Funci�n de callback para el men�
void menuCallback(int choice) {
    switch (choice) {
    case 1:
        timer.start(); // Iniciar el temporizador cuando se seleccione una opci�n del men�
        resolverCruzBlanca(cuboRubik);
    default:
        break;
    }
}

// Funci�n para mostrar el temporizador en pantalla
void mostrarTimer() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT));
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // Texto del temporizador
    glColor3f(1.0, 1.0, 1.0); // Color blanco para el texto
    std::string elapsedTime = "Tiempo: " + timer.elapsed_time();
    glRasterPos2i(glutGet(GLUT_WINDOW_WIDTH) - 180, glutGet(GLUT_WINDOW_HEIGHT) - 25);
    for (char c : elapsedTime) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    }

    // Fondo para el temporizador
    glEnable(GL_BLEND); // Habilitar el blending para que el fondo sea semitransparente
    glColor4f(0.2, 0.2, 0.2, 0.8); // Color gris oscuro con transparencia
    glBegin(GL_QUADS);
    glVertex2i(glutGet(GLUT_WINDOW_WIDTH) - 200, glutGet(GLUT_WINDOW_HEIGHT) - 40);
    glVertex2i(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT) - 40);
    glVertex2i(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
    glVertex2i(glutGet(GLUT_WINDOW_WIDTH) - 200, glutGet(GLUT_WINDOW_HEIGHT));
    glEnd();



    glDisable(GL_BLEND); // Deshabilitar el blending para restaurar el comportamiento predeterminado

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}


/**
 * Funci�n para manejar eventos del rat�n.
 * @param boton Bot�n del rat�n presionado.
 * @param estado Estado del bot�n del rat�n (presionado o liberado).
 * @param x Coordenada x del cursor en la ventana.
 * @param y Coordenada y del cursor en la ventana.
 */
void raton(int boton, int estado, int x, int y) {
    // Si el bot�n izquierdo del rat�n est� presionado
    if (boton == GLUT_LEFT_BUTTON) {
        // Si el estado es presionado
        if (estado == GLUT_DOWN) {
            // Guardar la posici�n del mouse
            ultimoMouseX = x;
            ultimoMouseY = y;
            arrastrando = true;
        }
        // Si el estado es liberado
        else if (estado == GLUT_UP) {
            arrastrando = false;
        }
    }

    // Si el bot�n derecho del rat�n est� presionado
    if (boton == GLUT_RIGHT_BUTTON && estado == GLUT_DOWN) {
        // Crear men� contextual
        int menu = glutCreateMenu(menuCallback); // Se asume que existe una funci�n menuCallback para manejar las selecciones del men�
        glutAddMenuEntry("Resolver", 1);
        glutAttachMenu(GLUT_RIGHT_BUTTON); // Adjuntar el men� al bot�n derecho del rat�n
    }
}


/**
 * Funci�n que gestiona el movimiento del rat�n para rotar la c�mara.
 * @param x Posici�n actual del cursor en el eje X.
 * @param y Posici�n actual del cursor en el eje Y.
 */
void movimientoRaton(int x, int y) {
    if (arrastrando) {
        // Calcular la diferencia de movimiento del rat�n desde la �ltima posici�n
        int deltaX = x - ultimoMouseX;
        int deltaY = y - ultimoMouseY;

        // Actualizar los �ngulos de rotaci�n de la c�mara seg�n el movimiento del rat�n
        anguloCamaraX += deltaX * 0.01f;
        anguloCamaraY += deltaY * 0.01f;

        // Actualizar la �ltima posici�n del rat�n
        ultimoMouseX = x;
        ultimoMouseY = y;

        // Forzar el redibujado de la escena para reflejar los cambios
        glutPostRedisplay();
    }
}



/**
 * Funci�n que maneja los eventos del teclado para realizar rotaciones en el cubo de Rubik.
 * @param tecla Tecla presionada por el usuario.
 * @param x Coordenada x del cursor en la ventana.
 * @param y Coordenada y del cursor en la ventana.
 */
void teclado(unsigned char tecla, int x, int y) {
    if (!rotacionEnCurso) {
        switch (tecla) {

        case 'q':
        case 'Q':
            exit(0);
            break;
        case 'b':
            rotacionEnCurso = true;
            rotarCapaInferior(cuboRubik, false);
            glutPostRedisplay();
            glutTimerFunc(20, [](int) {
                rotacionEnCurso = false;
            }, 0);
            break;
        case 'f':
            rotacionEnCurso = true;
            rotarCapaFrontal(cuboRubik, false);
            glutPostRedisplay();
            glutTimerFunc(20, [](int) {
                rotacionEnCurso = false;
            }, 0);
            break;
        case 'r':
            rotacionEnCurso = true;
            rotarCapaDerecha(cuboRubik, false);
            glutPostRedisplay();
            glutTimerFunc(20, [](int) {
                rotacionEnCurso = false;
            }, 0);
            break;
        case 'l':
            rotacionEnCurso = true;
            rotarCapaIzquierda(cuboRubik, false);
            glutPostRedisplay();
            glutTimerFunc(20, [](int) {
                rotacionEnCurso = false;
            }, 0);
            break;
        case 'u':
            rotacionEnCurso = true;
            rotarCapaSuperior(cuboRubik, false);
            glutPostRedisplay();
            glutTimerFunc(20, [](int) {
                rotacionEnCurso = false;
            }, 0);
            break;
        case 'd':
            rotacionEnCurso = true;
            rotarCapaTrasera(cuboRubik, false);
            glutPostRedisplay();
            glutTimerFunc(20, [](int){rotacionEnCurso = false;}, 0);
            break;
        case 'B':
            rotacionEnCurso = true;
            rotarCapaInferior(cuboRubik, true); // Giro inverso de la capa inferior
            glutPostRedisplay();
            glutTimerFunc(20, [](int) {
                rotacionEnCurso = false;
            }, 0);
            break;
        case 'F':
            rotacionEnCurso = true;
            rotarCapaFrontal(cuboRubik, true); // Giro inverso de la capa frontal
            glutPostRedisplay();
            glutTimerFunc(20, [](int) {
                rotacionEnCurso = false;
            }, 0);
            break;
        case 'R':
            rotacionEnCurso = true;
            rotarCapaDerecha(cuboRubik, true); // Giro inverso de la capa derecha
            glutPostRedisplay();
            glutTimerFunc(20, [](int) {
                rotacionEnCurso = false;
            }, 0);
            break;
        case 'L':
            rotacionEnCurso = true;
            rotarCapaIzquierda(cuboRubik, true); // Giro inverso de la capa izquierda
            glutPostRedisplay();
            glutTimerFunc(20, [](int) {
                rotacionEnCurso = false;
            }, 0);
            break;
        case 'U':
            rotacionEnCurso = true;
            rotarCapaSuperior(cuboRubik, true); // Giro inverso de la capa superior
            glutPostRedisplay();
            glutTimerFunc(20, [](int) {
                rotacionEnCurso = false;
            }, 0);
            break;
        case 'D':
            rotacionEnCurso = true;
            rotarCapaTrasera(cuboRubik, true); // Giro inverso de la capa trasera
            glutPostRedisplay();
            glutTimerFunc(20, [](int){rotacionEnCurso = false;}, 0);
            break;
        case 'm':
            rotacionEnCurso = true;
            rotarCapaMedia(cuboRubik, false);
            glutPostRedisplay();
            glutTimerFunc(20, [](int) {
                rotacionEnCurso = false;
            }, 0);
            break;
        case 'M':
            rotacionEnCurso = true;
            rotarCapaMedia(cuboRubik, true); // Giro inverso de la capa del medio
            glutPostRedisplay();
            glutTimerFunc(20, [](int) {
                rotacionEnCurso = false;
            }, 0);
            break;
        case 'e':
            rotacionEnCurso = true;
            rotarCapaEquatorial(cuboRubik, false);
            glutPostRedisplay();
            glutTimerFunc(20, [](int) {
                rotacionEnCurso = false;
            }, 0);
            break;
        case 'E':
            rotacionEnCurso = true;
            rotarCapaEquatorial(cuboRubik, true); // Giro inverso de la capa equatorial
            glutPostRedisplay();
            glutTimerFunc(20, [](int) {
                rotacionEnCurso = false;
            }, 0);
            break;
        case 's':
            rotacionEnCurso = true;
            rotarCapaStanding(cuboRubik, false);
            glutPostRedisplay();
            glutTimerFunc(20, [](int) {
                rotacionEnCurso = false;
            }, 0);
            break;
        case 'S':
            rotacionEnCurso = true;
            rotarCapaStanding(cuboRubik, true); // Giro inverso de la capa standing
            glutPostRedisplay();
            glutTimerFunc(20, [](int) {
                rotacionEnCurso = false;
            }, 0);
            break;
        case 'o':
        case 'O':
            asignarColoresCubo();
            glutPostRedisplay();
            break;
        default:
            break;
        }
    }
}

/**
 * Funci�n para gestionar las teclas especiales del teclado.
 * @param tecla C�digo de la tecla especial presionada.
 * @param x Posici�n del cursor en el eje X en el momento de la pulsaci�n.
 * @param y Posici�n del cursor en el eje Y en el momento de la pulsaci�n.
 */
void teclasEspeciales(int tecla, int x, int y) {
    switch (tecla) {
    case GLUT_KEY_UP:
        anguloCamaraX += 0.1f; // Ajustar el �ngulo de la c�mara hacia arriba
        glutPostRedisplay();
        break;
    case GLUT_KEY_DOWN:
        anguloCamaraX -= 0.1f; // Ajustar el �ngulo de la c�mara hacia abajo
        glutPostRedisplay();
        break;
    case GLUT_KEY_LEFT:
        anguloCamaraY -= 0.1f; // Ajustar el �ngulo de la c�mara hacia la izquierda
        glutPostRedisplay();
        break;
    case GLUT_KEY_RIGHT:
        anguloCamaraY += 0.1f; // Ajustar el �ngulo de la c�mara hacia la derecha
        glutPostRedisplay();
        break;
    default:
        break;
    }
}

/**
 * Funci�n para inicializar la configuraci�n del cubo de Rubik.
 * Configura el sombreado, la prueba de profundidad y asigna los colores iniciales del cubo.
 */
void inicializarCubo() {
    glShadeModel(GL_SMOOTH); // Configurar el sombreado suave
    glEnable(GL_DEPTH_TEST); // Habilitar la prueba de profundidad para renderizado en 3D
    asignarColoresCubo(); // Inicializar los colores del cubo
}

/**
 * Funci�n principal del programa.
 * Inicializa el cubo de Rubik, configura la ventana y los eventos de OpenGL, y comienza el bucle principal de GLUT.
 * @param argc Cantidad de argumentos de la l�nea de comandos.
 * @param argv Vector de argumentos de la l�nea de comandos.
 * @return C�digo de salida del programa.
 */
int main(int argc, char **argv) {
    inicializarCubo(); // Inicializar el cubo de Rubik

    // Inicializar GLUT y configurar la ventana
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Rubik's Cube"); // Crear una ventana con el t�tulo "Rubik's Cube"

    // Habilitar la prueba de profundidad y el blending para transparencias
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Registrar las funciones de callback para eventos de OpenGL
    glutDisplayFunc(mostrar); // Funci�n de renderizado
    glutReshapeFunc(redimensionar); // Funci�n de redimensionamiento de la ventana
    glutMouseFunc(raton); // Funci�n de manejo de eventos de rat�n
    glutMotionFunc(movimientoRaton); //Funcion de manejo de camara
    glutKeyboardFunc(teclado); // Funci�n de manejo de eventos de teclado normal
    glutSpecialFunc(teclasEspeciales); // Funci�n de manejo de eventos de teclas especiales

    // Iniciar el bucle principal de GLUT
    glutMainLoop();

    return 0; // Devolver 0 como c�digo de salida del programa
}
