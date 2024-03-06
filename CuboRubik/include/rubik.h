#ifndef RUBIK_H
#define RUBIK_H

#include "cubito.h" // Incluir el archivo de cabecera de la clase MiniCubo

/**
 * Estructura que representa un cubo de Rubik.
 */
struct Rubik {
    MiniCubo cubos[3][3][3]; // Arreglo tridimensional de MiniCubos para representar el cubo de Rubik
};

#endif // RUBIK_H
