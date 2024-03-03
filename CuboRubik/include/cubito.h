#ifndef CUBITO_H
#define CUBITO_H

struct MiniCube {
    enum Color { WHITE, YELLOW, BLUE, GREEN, RED, ORANGE };

    Color frente, atras, top, bottom, left, right;
};

void assignColors(MiniCube& cube, MiniCube::Color frente, MiniCube::Color atras,
    MiniCube::Color top, MiniCube::Color bottom, MiniCube::Color right, MiniCube::Color left) {
    cube.frente = frente;
    cube.atras = atras;
    cube.top = top;
    cube.bottom = bottom;
    cube.right = right;
    cube.left = left;
}

void rotateFrontFace(MiniCube& cube) {
    MiniCube::Color temp_front = cube.frente;
    cube.frente = cube.bottom;
    cube.bottom = cube.atras;
    cube.atras = cube.top;
    cube.top = temp_front;
}

void rotateBackFace(MiniCube& cube) {
    MiniCube::Color temp_back = cube.atras;
    cube.atras = cube.bottom;
    cube.bottom = cube.frente;
    cube.frente = cube.top;
    cube.top = temp_back;
}

void rotateTopFace(MiniCube& cube) {
    MiniCube::Color temp_top = cube.top;
    cube.top = cube.right;
    cube.right = cube.bottom;
    cube.bottom = cube.left;
    cube.left = temp_top;
}

void rotateBottomFace(MiniCube& cube) {
    MiniCube::Color temp_bottom = cube.bottom;
    cube.bottom = cube.right;
    cube.right = cube.top;
    cube.top = cube.left;
    cube.left = temp_bottom;
}

void rotateRightFace(MiniCube& cube) {
    MiniCube::Color temp_right = cube.right;
    cube.right = cube.atras;
    cube.atras = cube.left;
    cube.left = cube.frente;
    cube.frente = temp_right;
}

void rotateLeftFace(MiniCube& cube) {
    MiniCube::Color temp_left = cube.left;
    cube.left = cube.atras;
    cube.atras = cube.right;
    cube.right = cube.frente;
    cube.frente = temp_left;
}

#endif // CUBITO_H
