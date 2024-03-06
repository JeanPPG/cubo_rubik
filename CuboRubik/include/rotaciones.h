#ifndef ROTACIONES_H
#define ROTACIONES_H

#include "rubik.h"
#include "cubito.h" // Incluimos el archivo que contiene las funciones para rotar los cubitos

void rotarCapaDerecha(Rubik& cuboRubik, bool sentidoHorario)
{
    MiniCubo temp_capa[3][3]; // Creamos una capa temporal para guardar los cubitos

    // Guardar la capa superior en la capa temporal
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            temp_capa[i][j] = cuboRubik.cubos[0][i][j];
        }
    }

    // Rotar los cubitos en la capa superior
    if (sentidoHorario) {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                cuboRubik.cubos[0][i][j] = temp_capa[2 - j][i];
                // Rotar el cubito individual
                rotarCaraFrontal(cuboRubik.cubos[0][i][j]);
            }
        }
    } else {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                cuboRubik.cubos[0][i][j] = temp_capa[j][2 - i];
                // Rotar el cubito individual
                rotarCaraTrasera(cuboRubik.cubos[0][i][j]);
            }
        }
    }
}

void rotarCapaIzquierda(Rubik& cuboRubik, bool sentidoHorario) {
    MiniCubo temp_capa[3][3];

    // Guardar la capa inferior en la capa temporal
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            temp_capa[i][j] = cuboRubik.cubos[2][i][j];
        }
    }

    // Rotar los cubitos en la capa inferior
    if (sentidoHorario) {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                cuboRubik.cubos[2][i][j] = temp_capa[j][2 - i];
                rotarCaraTrasera(cuboRubik.cubos[2][i][j]);
            }
        }
    } else {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                cuboRubik.cubos[2][i][j] = temp_capa[2 - j][i];
                rotarCaraFrontal(cuboRubik.cubos[2][i][j]);
            }
        }
    }
}

void rotarCapaFrontal(Rubik& cuboRubik, bool sentidoHorario) {
    MiniCubo temp_capa[3][3];

    // Guardar la capa frontal en la capa temporal
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            temp_capa[i][j] = cuboRubik.cubos[i][j][2];
        }
    }

    // Rotar los cubitos en la capa frontal
    if (sentidoHorario) {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                cuboRubik.cubos[i][j][2] = temp_capa[j][2 - i];
                rotarCaraSuperior(cuboRubik.cubos[i][j][2]);
            }
        }
    } else {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                cuboRubik.cubos[i][j][2] = temp_capa[2 - j][i];
                rotarCaraInferior(cuboRubik.cubos[i][j][2]);
            }
        }
    }
}

void rotarCapaSuperior(Rubik& cuboRubik, bool sentidoHorario) {
    MiniCubo temp_capa[3][3];

    // Guardar la capa derecha en la capa temporal
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            temp_capa[i][j] = cuboRubik.cubos[j][2][i];
        }
    }

    // Rotar los cubitos en la capa derecha
    if (sentidoHorario) {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                cuboRubik.cubos[j][2][i] = temp_capa[j][2 - i];
                rotarCaraDerecha(cuboRubik.cubos[j][2][i]);
            }
        }
    } else {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                cuboRubik.cubos[j][2][i] = temp_capa[2 - j][i];
                rotarCaraIzquierda(cuboRubik.cubos[j][2][i]);
            }
        }
    }
}

void rotarCapaInferior(Rubik& cuboRubik, bool sentidoHorario) {
    MiniCubo temp_capa[3][3];

    // Guardar la capa izquierda en la capa temporal
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            temp_capa[i][j] = cuboRubik.cubos[j][0][i];
        }
    }

    // Rotar los cubitos en la capa izquierda
    if (sentidoHorario) {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                cuboRubik.cubos[j][0][i] = temp_capa[j][2 - i];
                rotarCaraIzquierda(cuboRubik.cubos[j][0][i]);
            }
        }
    } else {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                cuboRubik.cubos[j][0][i] = temp_capa[2 - j][i];
                rotarCaraDerecha(cuboRubik.cubos[j][0][i]);
            }
        }
    }
}

void rotarCapaTrasera(Rubik& cuboRubik, bool sentidoHorario) {
    MiniCubo temp_capa[3][3];

    // Guardar la capa trasera en la capa temporal
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            temp_capa[i][j] = cuboRubik.cubos[i][j][0];
        }
    }

    // Rotar los cubitos en la capa trasera
    if (sentidoHorario) {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                cuboRubik.cubos[i][j][0] = temp_capa[j][2 - i];
                rotarCaraInferior(cuboRubik.cubos[i][j][0]);
            }
        }
    } else {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                cuboRubik.cubos[i][j][0] = temp_capa[2 - j][i];
                rotarCaraSuperior(cuboRubik.cubos[i][j][0]);
            }
        }
    }
}

void rotarCapaMedia(Rubik& cuboRubik, bool sentidoHorario) {
    MiniCubo temp_capa[3][3];

    // Guardar la capa del medio en la capa temporal
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            temp_capa[i][j] = cuboRubik.cubos[j][1][i];
        }
    }

    // Rotar los cubitos en la capa del medio
    if (sentidoHorario) {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                cuboRubik.cubos[j][1][i] = temp_capa[j][2 - i];
                rotarCaraDerecha(cuboRubik.cubos[j][1][i]);
            }
        }
    } else {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                cuboRubik.cubos[j][1][i] = temp_capa[2 - j][i];
                rotarCaraIzquierda(cuboRubik.cubos[j][1][i]);
            }
        }
    }
}

void rotarCapaEquatorial(Rubik& cuboRubik, bool sentidoHorario) {
    MiniCubo temp_capa[3][3];

    // Guardar la capa equatorial en la capa temporal
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            temp_capa[i][j] = cuboRubik.cubos[1][j][i];
        }
    }

    // Rotar los cubitos en la capa equatorial
    if (sentidoHorario) {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                cuboRubik.cubos[1][j][i] = temp_capa[j][2 - i];
                rotarCaraFrontal(cuboRubik.cubos[1][j][i]);
            }
        }
    } else {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                cuboRubik.cubos[1][j][i] = temp_capa[2 - j][i];
                rotarCaraTrasera(cuboRubik.cubos[1][j][i]);
            }
        }
    }
}

void rotarCapaStanding(Rubik& cuboRubik, bool sentidoHorario) {
    MiniCubo temp_capa[3][3];

    // Guardar la capa standing en la capa temporal
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            temp_capa[i][j] = cuboRubik.cubos[i][j][1];
        }
    }

    // Rotar los cubitos en la capa standing
    if (sentidoHorario) {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                cuboRubik.cubos[i][j][1] = temp_capa[j][2 - i];
                rotarCaraInferior(cuboRubik.cubos[i][j][1]);
            }
        }
    } else {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                cuboRubik.cubos[i][j][1] = temp_capa[2 - j][i];
                rotarCaraSuperior(cuboRubik.cubos[i][j][1]);
            }
        }
    }
}
#endif // ROTACIONES_H
