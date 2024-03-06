#ifndef FRIDICH_H
#define FRIDICH_H

#include "rubik.h"
#include "rotaciones.h"

#include <iostream>
// Función para resolver la cruz en la primera capa
void solveCross(Rubik& rubiksCube) {

}

// Función para resolver el F2L (First Two Layers)
void solveF2L(Rubik& rubik) {
    // Paso 1: Buscar y emparejar las esquinas con los bordes correspondientes
    for (int i = 0; i < 4; ++i) {
        MiniCubo::Color colorEsquina = MiniCubo::BLANCO;
        MiniCubo::Color colorBorde1 = MiniCubo::BLANCO;
        MiniCubo::Color colorBorde2 = MiniCubo::BLANCO;

        switch (i) {
            case 0: // Esquina 1
                colorEsquina = rubik.cubos[2][0][0].abajo;
                colorBorde1 = rubik.cubos[1][0][2].derecha;
                colorBorde2 = rubik.cubos[0][2][2].atras;
                break;
            case 1: // Esquina 2
                colorEsquina = rubik.cubos[2][0][2].abajo;
                colorBorde1 = rubik.cubos[0][2][0].atras;
                colorBorde2 = rubik.cubos[1][0][0].izquierda;
                break;
            case 2: // Esquina 3
                colorEsquina = rubik.cubos[0][0][2].abajo;
                colorBorde1 = rubik.cubos[1][0][0].derecha;
                colorBorde2 = rubik.cubos[2][0][0].frente;
                break;
            case 3: // Esquina 4
                colorEsquina = rubik.cubos[0][0][0].abajo;
                colorBorde1 = rubik.cubos[2][0][2].frente;
                colorBorde2 = rubik.cubos[1][0][2].izquierda;
                break;
        }

        // Comprobamos si la esquina está ya emparejada con los bordes correspondientes
        if ((colorEsquina == MiniCubo::BLANCO && colorBorde1 == MiniCubo::BLANCO) ||
            (colorEsquina == MiniCubo::BLANCO && colorBorde2 == MiniCubo::BLANCO)) {
            // Emparejamos la esquina con los bordes correspondientes
            if (colorEsquina == MiniCubo::BLANCO && colorBorde1 == MiniCubo::BLANCO) {
                // Rotamos la capa inferior para emparejar la esquina con el borde 1
                rotarCapaInferior(rubik, true);
            }

            // Insertamos la esquina en su posición correcta
            rotarCapaDerecha(rubik, true);
            rotarCapaInferior(rubik, false);
            rotarCapaDerecha(rubik, false);
            rotarCapaInferior(rubik, true);
            rotarCapaDerecha(rubik, true);
            rotarCapaInferior(rubik, false);
            rotarCapaInferior(rubik, false);
        }
    }

    // Paso 2: Emparejar las esquinas restantes con los bordes correspondientes
    while (!(rubik.cubos[0][0][2].abajo == MiniCubo::BLANCO && rubik.cubos[0][2][0].abajo == MiniCubo::BLANCO &&
             rubik.cubos[2][0][0].abajo == MiniCubo::BLANCO && rubik.cubos[2][2][2].abajo == MiniCubo::BLANCO)) {
        rotarCapaInferior(rubik, true);
    }

    // Paso 3: Colocar las esquinas restantes en su posición correcta
    for (int i = 0; i < 4; ++i) {
        while (!(rubik.cubos[0][0][2].frente == MiniCubo::BLANCO && rubik.cubos[0][2][2].frente == MiniCubo::BLANCO)) {
            rotarCapaInferior(rubik, true);
        }
        rotarCapaFrontal(rubik, true);
        rotarCapaInferior(rubik, true);
        rotarCapaInferior(rubik, true);
    }
}


// Función para resolver el OLL (Orient Last Layer)
void solveOLL(Rubik& rubik) {
    // Aquí iría la lógica para resolver el OLL
}

// Función para resolver el PLL (Permute Last Layer)
void solvePLL(Rubik& rubik) {
    // Aquí iría la lógica para resolver el PLL
}

// Función que resuelve todo el cubo usando el método Fridrich
void solveFridich(Rubik& rubik) {
    solveCross(rubik);
    solveF2L(rubik);
    solveOLL(rubik);
    solvePLL(rubik);
}

#endif // FRIDICH_H

