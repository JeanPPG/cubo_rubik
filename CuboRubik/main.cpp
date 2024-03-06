#include "include/rotaciones.h"
#include "include/rubik.h"
#include "include/cubito.h"
#include "include/algoritmos.h"

#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <sstream>

Rubik cuboRubik; // Objeto de la clase Rubik que representa el cubo de Rubik

float radioCamara = 10.0f; // Radio de la cámara para visualizar el cubo
float anguloCamaraX = 0.0f; // Ángulo de rotación en el eje X de la cámara
float anguloCamaraY = 0.0f; // Ángulo de rotación en el eje Y de la cámara

int ultimoMouseX, ultimoMouseY; // Última posición del mouse
bool arrastrando = false; // Variable para indicar si se está arrastrando el cubo con el mouse
bool rotacionEnCurso = false; // Variable para indicar si hay una rotación en curso

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
void barajarCuboRubik();

// Función para asignar colores a cada cara del cubo Rubik
void asignarColoresCubo()
{
    // Asigna colores fijos para cada cara del cubo Rubik
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            for (int k = 0; k < 3; ++k)
            {
                if (i == 1 && j == 1 && k == 1) // El centro del cubo no tiene colores
                    continue;

                // Asigna colores según la posición del cubo en el arreglo
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
                     MiniCubo::Color arriba, MiniCubo::Color abajo, MiniCubo::Color derecha, MiniCubo::Color izquierda)
{
    GLfloat colores[6][3] =
    {
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

    // Dibujar líneas de separación entre cubos
    glLineWidth(2.0);
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);

    // Líneas horizontales
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
 * Función para mostrar el cubo de Rubik en la pantalla.
 * Limpia el búfer de color y el búfer de profundidad, ajusta la posición de la cámara y dibuja el cubo de Rubik.
 */
void mostrar()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpiar el búfer de color y el búfer de profundidad
    glLoadIdentity(); // Reiniciar la matriz de proyección

    glClearColor(0.5f, 0.5f, 0.5f, 1.0f); // Establecer el color de fondo
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpiar el búfer de color y el búfer de profundidad

    // Ajustar la posición de la cámara para que la cara superior apunte hacia arriba
    float camaraX = radioCamara * sin(anguloCamaraY) * cos(anguloCamaraX);
    float camaraY = radioCamara * cos(anguloCamaraY);
    float camaraZ = radioCamara * sin(anguloCamaraY) * sin(anguloCamaraX);
    gluLookAt(camaraX, camaraY, camaraZ, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);

    // Dibujar cada mini cubo del cubo Rubik
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            for (int k = 0; k < 3; ++k)
            {
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

    glutSwapBuffers(); // Intercambiar los búferes
}

/**
 * Función para redimensionar la ventana de visualización.
 * @param w Ancho de la ventana.
 * @param h Alto de la ventana.
 */
void redimensionar(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 100.0); // Configura la perspectiva de la cámara
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/**
 * Función de callback para el menú.
 * @param choice La opción seleccionada en el menú.
 */
void menuCallback(int choice)
{
    switch (choice)
    {
    case 1:
        resolverPrincipiante(cuboRubik); // Resuelve el cubo usando el método principiante
        break;
    case 2:
        resolverCapaPorCapa(cuboRubik); // Resuelve el cubo usando el método capa por capa
        break;
    case 3:
        resolverFridrichCFOP(cuboRubik); // Resuelve el cubo usando el método Fridrich CFOP
        break;
    case 4:
        resolverRoux(cuboRubik); // Resuelve el cubo usando el método Roux
        break;
    case 5:
        resolverPetrus(cuboRubik); // Resuelve el cubo usando el método Petrus
        break;
    default:
        break;
    }
}

/**
 * Función para manejar eventos del ratón.
 * @param boton Botón del ratón presionado.
 * @param estado Estado del botón del ratón (presionado o liberado).
 * @param x Coordenada x del cursor en la ventana.
 * @param y Coordenada y del cursor en la ventana.
 */
void raton(int boton, int estado, int x, int y)
{
    // Si el botón izquierdo del ratón está presionado
    if (boton == GLUT_LEFT_BUTTON)
    {
        // Si el estado es presionado
        if (estado == GLUT_DOWN)
        {
            // Guardar la posición del mouse
            ultimoMouseX = x;
            ultimoMouseY = y;
            arrastrando = true;
        }
        // Si el estado es liberado
        else if (estado == GLUT_UP)
        {
            arrastrando = false;
        }
    }

    // Si el botón derecho del ratón está presionado
    if (boton == GLUT_RIGHT_BUTTON && estado == GLUT_DOWN)
    {
        // Crear menú contextual
        int menu = glutCreateMenu(menuCallback); // Se asume que existe una función menuCallback para manejar las selecciones del menú
        glutAddMenuEntry("Resolver Principiante", 1);
        glutAddMenuEntry("Resolver Capa por Capa", 2);
        glutAddMenuEntry("Resolver Fridrich (CFOP)", 3);
        glutAddMenuEntry("Resolver Roux", 4);
        glutAddMenuEntry("Resolver Petrus", 5);
        glutAttachMenu(GLUT_RIGHT_BUTTON); // Adjuntar el menú al botón derecho del ratón
    }
}


/**
 * Función que gestiona el movimiento del ratón para rotar la cámara.
 * @param x Posición actual del cursor en el eje X.
 * @param y Posición actual del cursor en el eje Y.
 */
void movimientoRaton(int x, int y)
{
    if (arrastrando)
    {
        // Calcular la diferencia de movimiento del ratón desde la última posición
        int deltaX = x - ultimoMouseX;
        int deltaY = y - ultimoMouseY;

        // Actualizar los ángulos de rotación de la cámara según el movimiento del ratón
        anguloCamaraX += deltaX * 0.01f;
        anguloCamaraY += deltaY * 0.01f;

        // Actualizar la última posición del ratón
        ultimoMouseX = x;
        ultimoMouseY = y;

        // Forzar el redibujado de la escena para reflejar los cambios
        glutPostRedisplay();
    }
}

/**
 * Función que maneja los eventos del teclado para realizar rotaciones en el cubo de Rubik.
 * @param tecla Tecla presionada por el usuario.
 * @param x Coordenada x del cursor en la ventana.
 * @param y Coordenada y del cursor en la ventana.
 */
void teclado(unsigned char tecla, int x, int y)
{
    if (!rotacionEnCurso)
    {
        switch (tecla)
        {

        case 'q':
        case 'Q':
            exit(0);
            break;
        case 'b':
            rotacionEnCurso = true;
            rotarCapaInferior(cuboRubik, false);
            glutPostRedisplay();
            glutTimerFunc(20, [](int){rotacionEnCurso = false;}, 0);
            break;
        case 'f':
            rotacionEnCurso = true;
            rotarCapaFrontal(cuboRubik, false);
            glutPostRedisplay();
            glutTimerFunc(20, [](int){rotacionEnCurso = false;}, 0);
            break;
        case 'r':
            rotacionEnCurso = true;
            rotarCapaDerecha(cuboRubik, false);
            glutPostRedisplay();
            glutTimerFunc(20, [](int){rotacionEnCurso = false;}, 0);
            break;
        case 'l':
            rotacionEnCurso = true;
            rotarCapaIzquierda(cuboRubik, false);
            glutPostRedisplay();
            glutTimerFunc(20, [](int){rotacionEnCurso = false;}, 0);
            break;
        case 'u':
            rotacionEnCurso = true;
            rotarCapaSuperior(cuboRubik, false);
            glutPostRedisplay();
            glutTimerFunc(20, [](int){rotacionEnCurso = false;}, 0);
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
            glutTimerFunc(20, [](int){rotacionEnCurso = false;}, 0);
            break;
        case 'F':
            rotacionEnCurso = true;
            rotarCapaFrontal(cuboRubik, true); // Giro inverso de la capa frontal
            glutPostRedisplay();
            glutTimerFunc(20, [](int){rotacionEnCurso = false;}, 0);
            break;
        case 'R':
            rotacionEnCurso = true;
            rotarCapaDerecha(cuboRubik, true); // Giro inverso de la capa derecha
            glutPostRedisplay();
            glutTimerFunc(20, [](int){rotacionEnCurso = false;}, 0);
            break;
        case 'L':
            rotacionEnCurso = true;
            rotarCapaIzquierda(cuboRubik, true); // Giro inverso de la capa izquierda
            glutPostRedisplay();
            glutTimerFunc(20, [](int){rotacionEnCurso = false;}, 0);
            break;
        case 'U':
            rotacionEnCurso = true;
            rotarCapaSuperior(cuboRubik, true); // Giro inverso de la capa superior
            glutPostRedisplay();
            glutTimerFunc(20, [](int){rotacionEnCurso = false;}, 0);
            break;
//        case 'D':
//            rotacionEnCurso = true;
//            rotarCapaTrasera(cuboRubik, true); // Giro inverso de la capa trasera
//            glutPostRedisplay();
//            glutTimerFunc(20, [](int){rotacionEnCurso = false;}, 0);
//            break;
        case 'm':
            rotacionEnCurso = true;
            rotarCapaMedia(cuboRubik, false);
            glutPostRedisplay();
            glutTimerFunc(20, [](int){rotacionEnCurso = false;}, 0);
            break;
        case 'M':
            rotacionEnCurso = true;
            rotarCapaMedia(cuboRubik, true); // Giro inverso de la capa del medio
            glutPostRedisplay();
            glutTimerFunc(20, [](int){rotacionEnCurso = false;}, 0);
            break;
        case 'e':
            rotacionEnCurso = true;
            rotarCapaEquatorial(cuboRubik, false);
            glutPostRedisplay();
            glutTimerFunc(20, [](int){rotacionEnCurso = false;}, 0);
            break;
        case 'E':
            rotacionEnCurso = true;
            rotarCapaEquatorial(cuboRubik, true); // Giro inverso de la capa equatorial
            glutPostRedisplay();
            glutTimerFunc(20, [](int){rotacionEnCurso = false;}, 0);
            break;
        case 's':
            rotacionEnCurso = true;
            rotarCapaStanding(cuboRubik, false);
            glutPostRedisplay();
            glutTimerFunc(20, [](int){rotacionEnCurso = false;}, 0);
            break;
        case 'S':
            rotacionEnCurso = true;
            rotarCapaStanding(cuboRubik, true); // Giro inverso de la capa standing
            glutPostRedisplay();
            glutTimerFunc(20, [](int){rotacionEnCurso = false;}, 0);
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
 * Función para gestionar las teclas especiales del teclado.
 * @param tecla Código de la tecla especial presionada.
 * @param x Posición del cursor en el eje X en el momento de la pulsación.
 * @param y Posición del cursor en el eje Y en el momento de la pulsación.
 */
void teclasEspeciales(int tecla, int x, int y)
{
    switch (tecla)
    {
    case GLUT_KEY_UP:
        anguloCamaraX += 0.1f; // Ajustar el ángulo de la cámara hacia arriba
        glutPostRedisplay();
        break;
    case GLUT_KEY_DOWN:
        anguloCamaraX -= 0.1f; // Ajustar el ángulo de la cámara hacia abajo
        glutPostRedisplay();
        break;
    case GLUT_KEY_LEFT:
        anguloCamaraY -= 0.1f; // Ajustar el ángulo de la cámara hacia la izquierda
        glutPostRedisplay();
        break;
    case GLUT_KEY_RIGHT:
        anguloCamaraY += 0.1f; // Ajustar el ángulo de la cámara hacia la derecha
        glutPostRedisplay();
        break;
    default:
        break;
    }
}

/**
 * Función para inicializar la configuración del cubo de Rubik.
 * Configura el sombreado, la prueba de profundidad y asigna los colores iniciales del cubo.
 */
void inicializarCubo()
{
    glShadeModel(GL_SMOOTH); // Configurar el sombreado suave
    glEnable(GL_DEPTH_TEST); // Habilitar la prueba de profundidad para renderizado en 3D
    asignarColoresCubo(); // Inicializar los colores del cubo
}

/**
 * Función principal del programa.
 * Inicializa el cubo de Rubik, configura la ventana y los eventos de OpenGL, y comienza el bucle principal de GLUT.
 * @param argc Cantidad de argumentos de la línea de comandos.
 * @param argv Vector de argumentos de la línea de comandos.
 * @return Código de salida del programa.
 */
int main(int argc, char **argv)
{
    inicializarCubo(); // Inicializar el cubo de Rubik

    // Inicializar GLUT y configurar la ventana
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Rubik's Cube"); // Crear una ventana con el título "Rubik's Cube"

    // Habilitar la prueba de profundidad y el blending para transparencias
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Registrar las funciones de callback para eventos de OpenGL
    glutDisplayFunc(mostrar); // Función de renderizado
    glutReshapeFunc(redimensionar); // Función de redimensionamiento de la ventana
    glutMouseFunc(raton); // Función de manejo de eventos de ratón
    glutKeyboardFunc(teclado); // Función de manejo de eventos de teclado normal
    glutSpecialFunc(teclasEspeciales); // Función de manejo de eventos de teclas especiales

    // Iniciar el bucle principal de GLUT
    glutMainLoop();

    return 0; // Devolver 0 como código de salida del programa
}
