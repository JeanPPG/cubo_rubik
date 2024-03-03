#ifndef RUBIK_H
#define RUBIK_H

// Elimina la inclusión de cubito.h aquí

#include "cubito.h" // Incluye cubito.h después de la declaración de MiniCube

struct RubiksCube {
    MiniCube cubes[3][3][3];
};

#endif // RUBIK_H

