#include "include/rotaciones.h"
#include "include/rubik.h"
#include "include/cubito.h"

#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include <ctime>

RubiksCube rubiksCube;

float cameraRadius = 10.0f;
float cameraAngleX = 0.0f;
float cameraAngleY = 0.0f;

int lastMouseX, lastMouseY;
bool isDragging = false;

void display();
void reshape(int w, int h);
void mouse(int button, int state, int x, int y);
void motion(int x, int y);
void initCube();
void initCubeColors();
void keyboard(unsigned char key, int x, int y);
void drawMiniCube(float x, float y, float z, MiniCube::Color front, MiniCube::Color back,
    MiniCube::Color top, MiniCube::Color bottom, MiniCube::Color right, MiniCube::Color left);

void initCubeColors()
{
    // Asignar colores fijos para cada cara del cubo Rubik
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 3; ++k) {
                if (i == 1 && j == 1 && k == 1) // El centro del cubo no tiene colores
                    continue;

                // Asignar colores según la posición del cubo en el arreglo
                rubiksCube.cubes[i][j][k].top = MiniCube::WHITE;
                rubiksCube.cubes[i][j][k].bottom = MiniCube::YELLOW;
                rubiksCube.cubes[i][j][k].frente = MiniCube::RED;
                rubiksCube.cubes[i][j][k].atras = MiniCube::ORANGE;
                rubiksCube.cubes[i][j][k].right = MiniCube::GREEN;
                rubiksCube.cubes[i][j][k].left = MiniCube::BLUE;
            }
        }
    }
}

void drawMiniCube(float x, float y, float z, MiniCube::Color front, MiniCube::Color back,
    MiniCube::Color top, MiniCube::Color bottom, MiniCube::Color right, MiniCube::Color left)
{
    GLfloat colors[6][3] = {
        {0.8f, 0.8f, 0.8f}, // WHITE
        {0.8f, 0.8f, 0.0f}, // YELLOW
        {0.0f, 0.0f, 0.8f}, // RED
        {0.0f, 0.8f, 0.0f}, // BLUE
        {0.8f, 0.0f, 0.0f}, // GREEN
        {0.8f, 0.4f, 0.0f}  // ORANGE
    };

    glBegin(GL_QUADS);

    glColor3fv(colors[front]);
    glVertex3f(x - 0.02f, y - 0.02f, z + 1.02f);
    glVertex3f(x + 1.02f, y - 0.02f, z + 1.02f);
    glVertex3f(x + 1.02f, y + 1.02f, z + 1.02f);
    glVertex3f(x - 0.02f, y + 1.02f, z + 1.02f);

    glColor3fv(colors[back]);
    glVertex3f(x - 0.02f, y - 0.02f, z - 0.02f);
    glVertex3f(x - 0.02f, y + 1.02f, z - 0.02f);
    glVertex3f(x + 1.02f, y + 1.02f, z - 0.02f);
    glVertex3f(x + 1.02f, y - 0.02f, z - 0.02f);

    glColor3fv(colors[top]);
    glVertex3f(x - 0.02f, y + 1.02f, z + 1.02f);
    glVertex3f(x + 1.02f, y + 1.02f, z + 1.02f);
    glVertex3f(x + 1.02f, y + 1.02f, z - 0.02f);
    glVertex3f(x - 0.02f, y + 1.02f, z - 0.02f);

    glColor3fv(colors[bottom]);
    glVertex3f(x - 0.02f, y - 0.02f, z + 1.02f);
    glVertex3f(x + 1.02f, y - 0.02f, z + 1.02f);
    glVertex3f(x + 1.02f, y - 0.02f, z - 0.02f);
    glVertex3f(x - 0.02f, y - 0.02f, z - 0.02f);

    glColor3fv(colors[right]);
    glVertex3f(x + 1.02f, y - 0.02f, z + 1.02f);
    glVertex3f(x + 1.02f, y + 1.02f, z + 1.02f);
    glVertex3f(x + 1.02f, y + 1.02f, z - 0.02f);
    glVertex3f(x + 1.02f, y - 0.02f, z - 0.02f);

    glColor3fv(colors[left]);
    glVertex3f(x - 0.02f, y - 0.02f, z + 1.02f);
    glVertex3f(x - 0.02f, y + 1.02f, z + 1.02f);
    glVertex3f(x - 0.02f, y + 1.02f, z - 0.02f);
    glVertex3f(x - 0.02f, y - 0.02f, z - 0.02f);

    glEnd();

    glLineWidth(2.0);
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);

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

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    float cameraX = cameraRadius * sin(cameraAngleY) * cos(cameraAngleX);
    float cameraY = cameraRadius * cos(cameraAngleY);
    float cameraZ = cameraRadius * sin(cameraAngleY) * sin(cameraAngleX);
    gluLookAt(cameraX, cameraY, cameraZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 3; ++k) {
                float x = i - 1.0f;
                float y = j - 1.0f;
                float z = k - 1.0f;

                MiniCube::Color frente = rubiksCube.cubes[i][j][k].frente;
                MiniCube::Color atras = rubiksCube.cubes[i][j][k].atras;
                MiniCube::Color top = rubiksCube.cubes[i][j][k].top;
                MiniCube::Color bottom = rubiksCube.cubes[i][j][k].bottom;
                MiniCube::Color right = rubiksCube.cubes[i][j][k].right;
                MiniCube::Color left = rubiksCube.cubes[i][j][k].left;

                drawMiniCube(x, y, z, frente, atras, top, bottom, right, left);
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

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'q':
    case 'Q':
        exit(0);
        break;
    case 'b':
    case 'B':
       rotateBottomLayer(rubiksCube, false);
        glutPostRedisplay();
        break;
    case 'f':
    case 'F':
  rotateFrontLayer(rubiksCube, false);
        glutPostRedisplay();
        break;
    case 'r':
    case 'R':
    rotateRightLayer(rubiksCube, false);
        glutPostRedisplay();
        break;
    case 'l':
  case 'L':
    rotateLeftLayer(rubiksCube, false);
        glutPostRedisplay();
        break;
    case 't':
    case 'T':
    rotateTopLayer(rubiksCube, false);
        glutPostRedisplay();
        break;
    case 'a':
    case 'A':
        rotateBackLayer(rubiksCube, false);
        glutPostRedisplay();
        break;
    case 'm':
    case 'M':
        initCubeColors();
        glutPostRedisplay();
        break;
    default:
        break;
    }
}

void initCube()
{
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    initCubeColors(); // Inicializa los colores del cubo
}

int main(int argc, char **argv)
{
    initCube();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Rubik's Cube");
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
