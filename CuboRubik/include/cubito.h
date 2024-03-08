#ifndef CUBITO_H
#define CUBITO_H
#include <string>

// Definición de la estructura MiniCubo
struct MiniCubo {
    enum Color { BLANCO, AMARILLO, AZUL, VERDE, ROJO, NARANJA };
    enum corner {urf, ubr, dlf, dfr, ulb, ufl, drb, dbl};
    enum edge {uf, ur, ub, ul, df, dr, db, dl, fr, br, bl, fl};
    Color frente, atras, arriba, abajo, izquierda, derecha, centro, color_opuesto;
};

// Función para asignar colores a un MiniCubo
void asignarColores(MiniCubo& cubo, MiniCubo::Color frente, MiniCubo::Color atras,

                    MiniCubo::Color arriba, MiniCubo::Color abajo, MiniCubo::Color derecha, MiniCubo::Color izquierda) {

    cubo.frente = frente;
    cubo.atras = atras;
    cubo.arriba = arriba;
    cubo.abajo = abajo;
    cubo.derecha = derecha;
    cubo.izquierda = izquierda;
}

// Función para rotar la cara frontal de un MiniCubo
void rotarCaraFrontal(MiniCubo& cubo) {
    MiniCubo::Color temp_frontal = cubo.frente;
    cubo.frente = cubo.abajo;
    cubo.abajo = cubo.atras;
    cubo.atras = cubo.arriba;
    cubo.arriba = temp_frontal;
}

// Función para rotar la cara trasera de un MiniCubo
void rotarCaraTrasera(MiniCubo& cubo) {
    MiniCubo::Color temp_trasera = cubo.atras;
    cubo.atras = cubo.abajo;
    cubo.abajo = cubo.frente;
    cubo.frente = cubo.arriba;
    cubo.arriba = temp_trasera;
}

// Función para rotar la cara superior de un MiniCubo
void rotarCaraSuperior(MiniCubo& cubo) {
    MiniCubo::Color temp_superior = cubo.arriba;
    cubo.arriba = cubo.derecha;
    cubo.derecha = cubo.abajo;
    cubo.abajo = cubo.izquierda;
    cubo.izquierda = temp_superior;
}

// Función para rotar la cara inferior de un MiniCubo
void rotarCaraInferior(MiniCubo& cubo) {
    MiniCubo::Color temp_inferior = cubo.abajo;
    cubo.abajo = cubo.derecha;
    cubo.derecha = cubo.arriba;
    cubo.arriba = cubo.izquierda;
    cubo.izquierda = temp_inferior;
}

// Función para rotar la cara derecha de un MiniCubo
void rotarCaraDerecha(MiniCubo& cubo) {
    MiniCubo::Color temp_derecha = cubo.derecha;
    cubo.derecha = cubo.atras;
    cubo.atras = cubo.izquierda;
    cubo.izquierda = cubo.frente;
    cubo.frente = temp_derecha;
}

// Función para rotar la cara izquierda de un MiniCubo
void rotarCaraIzquierda(MiniCubo& cubo) {
    MiniCubo::Color temp_izquierda = cubo.izquierda;
    cubo.izquierda = cubo.atras;
    cubo.atras = cubo.derecha;
    cubo.derecha = cubo.frente;
    cubo.frente = temp_izquierda;
}

#endif // CUBITO_H
