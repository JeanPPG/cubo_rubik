#include <windows.h>
#include <GL/glew.h>
#include <gl/glut.h>

#include <cmath>
#include <iostream>
#include <ctime> // Para la generaci�n de n�meros aleatorios
#include <string>


struct RubiksCube
{
    // Colores de las caras de los cubos m�s peque�os
    enum Color { WHITE, YELLOW, BLUE, GREEN, RED, ORANGE };

    // Representa un cubo m�s peque�o del cubo de Rubik
    struct Cube
    {
        Color front, back, top, bottom, left, right;
    };

    Cube cubes[3][3][3]; // Matriz 3x3x3 de cubos m�s peque�os
};

// Prototipos de funciones
void display();
void reshape(int w, int h);
void mouse(int button, int state, int x, int y);
void motion(int x, int y);
void initCube(); // Inicializa el cubo de Rubik
void initRandomCubeColors();

RubiksCube rubiksCube; // Instancia del cubo de Rubik

float cameraRadius = 10.0f; // Radio de la c�mara
float cameraAngleX = 0.0f; // �ngulo de la c�mara en X
float cameraAngleY = 0.0f; // �ngulo de la c�mara en Y

int lastMouseX, lastMouseY;
bool isDragging = false;

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Rubik's Cube");

    glEnable(GL_DEPTH_TEST);

    // Inicializar colores aleatorios para los minicubos
    initRandomCubeColors();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);

    glutMainLoop();

    return 0;
}

void initRandomCubeColors()
{
    srand(time(NULL)); // Semilla aleatoria basada en el tiempo actual

    // Colores disponibles
    RubiksCube::Color availableColors[] = {
        RubiksCube::WHITE, RubiksCube::YELLOW, RubiksCube::BLUE,
        RubiksCube::GREEN, RubiksCube::RED, RubiksCube::ORANGE
    };

    int numColors = 6;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 3; ++k) {
                // Barajar los colores disponibles
                for (int m = 0; m < numColors; ++m) {
                    int randomIndex = rand() % numColors;
                    std::swap(availableColors[m], availableColors[randomIndex]);
                }

                // Asignar colores �nicos a cada lado del minicubo
                rubiksCube.cubes[i][j][k].front = availableColors[0];
                rubiksCube.cubes[i][j][k].back = availableColors[1];
                rubiksCube.cubes[i][j][k].top = availableColors[2];
                rubiksCube.cubes[i][j][k].bottom = availableColors[3];
                rubiksCube.cubes[i][j][k].left = availableColors[4];
                rubiksCube.cubes[i][j][k].right = availableColors[5];
            }
        }
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Cambiar el color de fondo a gris
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Posiciona la c�mara para rotar alrededor del cubo
    float cameraX = cameraRadius * sin(cameraAngleY) * cos(cameraAngleX);
    float cameraY = cameraRadius * cos(cameraAngleY);
    float cameraZ = cameraRadius * sin(cameraAngleY) * sin(cameraAngleX);
    gluLookAt(cameraX, cameraY, cameraZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    // Definir los colores en formato GLfloat con una intensidad reducida
    GLfloat colors[6][3] = {
        {0.8f, 0.8f, 0.8f},  // Blanco
        {0.8f, 0.8f, 0.0f},  // Amarillo
        {0.0f, 0.0f, 0.8f},  // Azul
        {0.0f, 0.8f, 0.0f},  // Verde
        {0.8f, 0.0f, 0.0f},  // Rojo
        {0.8f, 0.4f, 0.0f}   // Naranja
    };

    // Dibujar el cubo de Rubik
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 3; ++k) {
                // Coordenadas de los cubos m�s peque�os
                float x = i - 1.0f;
                float y = j - 1.0f;
                float z = k - 1.0f;

                // Dibujar el cubo m�s peque�o con colores aleatorios
                glBegin(GL_QUADS);

                // Cara frontal
                glColor3fv(colors[rubiksCube.cubes[i][j][k].front]);
                glVertex3f(x - 0.02f, y - 0.02f, z + 1.02f);
                glVertex3f(x + 1.02f, y - 0.02f, z + 1.02f);
                glVertex3f(x + 1.02f, y + 1.02f, z + 1.02f);
                glVertex3f(x - 0.02f, y + 1.02f, z + 1.02f);

                // Cara trasera
                glColor3fv(colors[rubiksCube.cubes[i][j][k].back]);
                glVertex3f(x - 0.02f, y - 0.02f, z - 0.02f);
                glVertex3f(x - 0.02f, y + 1.02f, z - 0.02f);
                glVertex3f(x + 1.02f, y + 1.02f, z - 0.02f);
                glVertex3f(x + 1.02f, y - 0.02f, z - 0.02f);

                // Cara superior
                glColor3fv(colors[rubiksCube.cubes[i][j][k].top]);
                glVertex3f(x - 0.02f, y + 1.02f, z + 1.02f);
                glVertex3f(x + 1.02f, y + 1.02f, z + 1.02f);
                glVertex3f(x + 1.02f, y + 1.02f, z - 0.02f);
                glVertex3f(x - 0.02f, y + 1.02f, z - 0.02f);

                // Cara inferior
                glColor3fv(colors[rubiksCube.cubes[i][j][k].bottom]);
                glVertex3f(x - 0.02f, y - 0.02f, z + 1.02f);
                glVertex3f(x + 1.02f, y - 0.02f, z + 1.02f);
                glVertex3f(x + 1.02f, y - 0.02f, z - 0.02f);
                glVertex3f(x - 0.02f, y - 0.02f, z - 0.02f);

                // Cara derecha
                glColor3fv(colors[rubiksCube.cubes[i][j][k].right]);
                glVertex3f(x + 1.02f, y - 0.02f, z + 1.02f);
                glVertex3f(x + 1.02f, y + 1.02f, z + 1.02f);
                glVertex3f(x + 1.02f, y + 1.02f, z - 0.02f);
                glVertex3f(x + 1.02f, y - 0.02f, z - 0.02f);

                // Cara izquierda
                glColor3fv(colors[rubiksCube.cubes[i][j][k].left]);
                glVertex3f(x - 0.02f, y - 0.02f, z + 1.02f);
                glVertex3f(x - 0.02f, y + 1.02f, z + 1.02f);
                glVertex3f(x - 0.02f, y + 1.02f, z - 0.02f);
                glVertex3f(x - 0.02f, y - 0.02f, z - 0.02f);

                glEnd();
                // Dibujar los bordes negros en direcci�n X
                glLineWidth(2.0); // Grosor de la l�nea
                glColor3f(0.0, 0.0, 0.0);
                glBegin(GL_LINE_LOOP);

                glVertex3f(x - 0.02f, y - 0.02f, z + 1.02f);
                glVertex3f(x + 1.02f, y - 0.02f, z + 1.02f);
                glVertex3f(x + 1.02f, y - 0.02f, z - 0.02f);
                glVertex3f(x - 0.02f, y - 0.02f, z - 0.02f);

                glEnd();

                // Dibujar los bordes negros en direcci�n Y
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

                // Dibujar los bordes negros en direcci�n Z
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
        }
    }

    glutSwapBuffers();
}


void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            lastMouseX = x;
            lastMouseY = y;
            isDragging = true;
        }
        else if (state == GLUT_UP)
        {
            isDragging = false;
        }
    }
}

void motion(int x, int y)
{
    if (isDragging)
    {
        int deltaX = x - lastMouseX;
        int deltaY = y - lastMouseY;

        cameraAngleX += deltaX * 0.01f;
        cameraAngleY += deltaY * 0.01f;

        lastMouseX = x;
        lastMouseY = y;

        glutPostRedisplay();
    }
}
