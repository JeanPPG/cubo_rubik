#include <windows.h>
#include <gl/glut.h>
#include <cmath>
#include <iostream>

struct RubiksCube
{
    // Colores de las caras de los cubos más pequeños
    enum Color { WHITE, YELLOW, BLUE, GREEN, RED, ORANGE };

    // Representa un cubo más pequeño del cubo de Rubik
    struct Cube
    {
        Color front, back, top, bottom, left, right;
    };

    Cube cubes[3][3][3]; // Matriz 3x3x3 de cubos más pequeños
};

RubiksCube rubiksCube; // Instancia del cubo de Rubik

float cameraRadius = 10.0f; // Radio de la cámara
float cameraAngleX = 0.0f; // Ángulo de la cámara en X
float cameraAngleY = 0.0f; // Ángulo de la cámara en Y

int lastMouseX, lastMouseY;
bool isDragging = false;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Cambiar el color de fondo a gris
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Posiciona la cámara para rotar alrededor del cubo
    float cameraX = cameraRadius * sin(cameraAngleY) * cos(cameraAngleX);
    float cameraY = cameraRadius * cos(cameraAngleY);
    float cameraZ = cameraRadius * sin(cameraAngleY) * sin(cameraAngleX);
    gluLookAt(cameraX, cameraY, cameraZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    // Definir los colores de las caras del cubo de Rubik
    glColor3f(1.0, 1.0, 1.0); // Blanco (cara superior)
    glColor3f(1.0, 1.0, 0.0); // Amarillo (cara inferior)
    glColor3f(0.0, 0.0, 1.0); // Azul (cara frontal)
    glColor3f(0.0, 1.0, 0.0); // Verde (cara trasera)
    glColor3f(1.0, 0.0, 0.0); // Rojo (cara derecha)
    glColor3f(1.0, 0.5, 0.0); // Naranja (cara izquierda)

    // Dibujar el cubo de Rubik
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 3; ++k) {
                // Coordenadas de los cubos más pequeños
                float x = i - 1.0f;
                float y = j - 1.0f;
                float z = k - 1.0f;

                // Dibujar el cubo más pequeño con colores
                glBegin(GL_QUADS);

                // Cara superior
                glColor3f(1.0, 1.0, 1.0); // Blanco
                glVertex3f(x - 0.02f, y + 1.0f, z + 1.02f);
                glVertex3f(x + 1.02f, y + 1.0f, z + 1.02f);
                glVertex3f(x + 1.02f, y + 1.0f, z - 0.02f);
                glVertex3f(x - 0.02f, y + 1.0f, z - 0.02f);

                // Cara inferior
                glColor3f(1.0, 1.0, 0.0); // Amarillo
                glVertex3f(x - 0.02f, y - 0.02f, z + 1.02f);
                glVertex3f(x + 1.02f, y - 0.02f, z + 1.02f);
                glVertex3f(x + 1.02f, y - 0.02f, z - 0.02f);
                glVertex3f(x - 0.02f, y - 0.02f, z - 0.02f);

                // Cara frontal
                glColor3f(0.0, 0.0, 1.0); // Azul
                glVertex3f(x - 0.02f, y - 0.02f, z + 1.02f);
                glVertex3f(x + 1.02f, y - 0.02f, z + 1.02f);
                glVertex3f(x + 1.02f, y + 1.02f, z + 1.02f);
                glVertex3f(x - 0.02f, y + 1.02f, z + 1.02f);

                // Cara trasera
                glColor3f(0.0, 1.0, 0.0); // Verde
                glVertex3f(x - 0.02f, y - 0.02f, z - 0.02f);
                glVertex3f(x - 0.02f, y + 1.02f, z - 0.02f);
                glVertex3f(x + 1.02f, y + 1.02f, z - 0.02f);
                glVertex3f(x + 1.02f, y - 0.02f, z - 0.02f);

                // Cara derecha
                glColor3f(1.0, 0.0, 0.0); // Rojo
                glVertex3f(x + 1.02f, y - 0.02f, z + 1.02f);
                glVertex3f(x + 1.02f, y + 1.02f, z + 1.02f);
                glVertex3f(x + 1.02f, y + 1.02f, z - 0.02f);
                glVertex3f(x + 1.02f, y - 0.02f, z - 0.02f);

                // Cara izquierda
                glColor3f(1.0, 0.5, 0.0); // Naranja
                glVertex3f(x - 0.02f, y - 0.02f, z + 1.02f);
                glVertex3f(x - 0.02f, y + 1.02f, z + 1.02f);
                glVertex3f(x - 0.02f, y + 1.02f, z - 0.02f);
                glVertex3f(x - 0.02f, y - 0.02f, z - 0.02f);

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

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Rubik's Cube");

    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);

    glutMainLoop();

    return 0;
}
