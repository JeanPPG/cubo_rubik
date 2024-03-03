#ifndef ROTACIONES_H
#define ROTACIONES_H

#include "rubik.h"
#include "cubito.h" // Incluimos el archivo que contiene las funciones para rotar los cubitos

void rotateTopLayer(RubiksCube& rubiksCube, bool clockwise)
{
    MiniCube temp_layer[3][3]; // Creamos una capa temporal para guardar los cubitos

    // Guardar la capa superior en la capa temporal
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            temp_layer[i][j] = rubiksCube.cubes[0][i][j];
        }
    }

    // Rotar los cubitos en la capa superior
    if (clockwise) {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                rubiksCube.cubes[0][i][j] = temp_layer[2 - j][i];
                // Rotar el cubito individual
                rotateFrontFace(rubiksCube.cubes[0][i][j]);
            }
        }
    } else {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                rubiksCube.cubes[0][i][j] = temp_layer[j][2 - i];
                // Rotar el cubito individual
                rotateBackFace(rubiksCube.cubes[0][i][j]);
            }
        }
    }
}

void rotateBottomLayer(RubiksCube& rubiksCube, bool clockwise) {
    MiniCube temp_layer[3][3];

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            temp_layer[i][j] = rubiksCube.cubes[2][i][j];
        }
    }

    if (clockwise) {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                rubiksCube.cubes[2][i][j] = temp_layer[j][2 - i];
                rotateBackFace(rubiksCube.cubes[2][i][j]);
            }
        }
    } else {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                rubiksCube.cubes[2][i][j] = temp_layer[2 - j][i];
                rotateFrontFace(rubiksCube.cubes[2][i][j]);
            }
        }
    }
}

void rotateFrontLayer(RubiksCube& rubiksCube, bool clockwise) {
    MiniCube temp_layer[3][3];

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            temp_layer[i][j] = rubiksCube.cubes[i][j][2];
        }
    }

    if (clockwise) {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                rubiksCube.cubes[i][j][2] = temp_layer[j][2 - i];
                rotateTopFace(rubiksCube.cubes[i][j][2]);
            }
        }
    } else {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                rubiksCube.cubes[i][j][2] = temp_layer[2 - j][i];
                rotateBottomFace(rubiksCube.cubes[i][j][2]);
            }
        }
    }
}

void rotateRightLayer(RubiksCube& rubiksCube, bool clockwise) {
    MiniCube temp_layer[3][3];

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            temp_layer[i][j] = rubiksCube.cubes[j][2][i];
        }
    }

    if (clockwise) {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                rubiksCube.cubes[j][2][i] = temp_layer[j][2 - i];
                rotateRightFace(rubiksCube.cubes[j][2][i]);
            }
        }
    } else {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                rubiksCube.cubes[j][2][i] = temp_layer[2 - j][i];
                rotateLeftFace(rubiksCube.cubes[j][2][i]);
            }
        }
    }
}

void rotateLeftLayer(RubiksCube& rubiksCube, bool clockwise) {
    MiniCube temp_layer[3][3];

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            temp_layer[i][j] = rubiksCube.cubes[j][0][i];
        }
    }

    if (clockwise) {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                rubiksCube.cubes[j][0][i] = temp_layer[j][2 - i];
                rotateLeftFace(rubiksCube.cubes[j][0][i]);
            }
        }
    } else {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                rubiksCube.cubes[j][0][i] = temp_layer[2 - j][i];
                rotateRightFace(rubiksCube.cubes[j][0][i]);
            }
        }
    }
}

void rotateBackLayer(RubiksCube& rubiksCube, bool clockwise) {
    MiniCube temp_layer[3][3];

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            temp_layer[i][j] = rubiksCube.cubes[i][j][0];
        }
    }

    if (clockwise) {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                rubiksCube.cubes[i][j][0] = temp_layer[j][2 - i];
                rotateBottomFace(rubiksCube.cubes[i][j][0]);
            }
        }
    } else {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                rubiksCube.cubes[i][j][0] = temp_layer[2 - j][i];
                rotateTopFace(rubiksCube.cubes[i][j][0]);
            }
        }
    }
}

void rotateMiddleLayer(RubiksCube& rubiksCube, bool clockwise) {
    MiniCube temp_layer[3][3];

    // Guardar la capa del medio en la capa temporal
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            temp_layer[i][j] = rubiksCube.cubes[j][1][i];
        }
    }

    // Rotar los cubitos en la capa del medio
    if (clockwise) {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                rubiksCube.cubes[j][1][i] = temp_layer[j][2 - i];
                rotateRightFace(rubiksCube.cubes[j][1][i]);
            }
        }
    } else {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                rubiksCube.cubes[j][1][i] = temp_layer[2 - j][i];
                rotateLeftFace(rubiksCube.cubes[j][1][i]);
            }
        }
    }
}

void rotateEquatorialLayer(RubiksCube& rubiksCube, bool clockwise) {
    MiniCube temp_layer[3][3];

    // Guardar la capa equatorial en la capa temporal
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            temp_layer[i][j] = rubiksCube.cubes[1][j][i];
        }
    }

    // Rotar los cubitos en la capa equatorial
    if (clockwise) {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                rubiksCube.cubes[1][j][i] = temp_layer[j][2 - i];
                rotateFrontFace(rubiksCube.cubes[1][j][i]);
            }
        }
    } else {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                rubiksCube.cubes[1][j][i] = temp_layer[2 - j][i];
                rotateBackFace(rubiksCube.cubes[1][j][i]);
            }
        }
    }
}

void rotateStandingLayer(RubiksCube& rubiksCube, bool clockwise) {
    MiniCube temp_layer[3][3];

    // Guardar la capa standing en la capa temporal
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            temp_layer[i][j] = rubiksCube.cubes[i][j][1];
        }
    }

    // Rotar los cubitos en la capa standing
    if (clockwise) {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                rubiksCube.cubes[i][j][1] = temp_layer[j][2 - i];
                rotateBottomFace(rubiksCube.cubes[i][j][1]);
            }
        }
    } else {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                rubiksCube.cubes[i][j][1] = temp_layer[2 - j][i];
                rotateTopFace(rubiksCube.cubes[i][j][1]);
            }
        }
    }
}
#endif // ROTACIONES_H
