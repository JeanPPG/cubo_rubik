#ifndef RUBIK_H
#define RUBIK_H

// Elimina la inclusi�n de cubito.h aqu�

#include "cubito.h" // Incluye cubito.h despu�s de la declaraci�n de MiniCube

struct RubiksCube {
    MiniCube cubes[3][3][3];
};

#endif // RUBIK_H

