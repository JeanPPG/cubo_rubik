#ifndef ALGORITMOS_H
#define ALGORITMOS_H

#include "cubito.h"
#include "rubik.h"
#include "rotaciones.h"
#include <iostream>

using namespace std;

void resolverCruzBlanca(Rubik& cubo) {
   // Buscar el centro blanco en el cubo
   MiniCubo::Color centro = MiniCubo::BLANCO;
   MiniCubo* cubo_centro = nullptr;
   for (int i = 0; i < 3; ++i) {
       for (int j = 0; j < 3; ++j) {
           for (int k = 0; k < 3; ++k) {
               if (cubo.cubos[i][j][k].centro == centro) {
                   cubo_centro = &cubo.cubos[i][j][k];
                   break;
               }
           }
           if (cubo_centro) break;
       }
       if (cubo_centro) break;
   }

   // Buscar edges blancas en todas las caras
   MiniCubo* cubo_edge = nullptr;
   for (int i = 0; i < 3; ++i) {
       for (int j = 0; j < 3; ++j) {
           for (int k = 0; k < 3; ++k) {
               MiniCubo& cubo_actual = cubo.cubos[i][j][k];
               if (cubo_actual.centro != centro && cubo_actual.arriba == centro &&
                   (cubo_actual.derecha == centro || cubo_actual.izquierda == centro)) {
                   cubo_edge = &cubo_actual;
                   break;
               }
           }
           if (cubo_edge) break;
       }
       if (cubo_edge) break;
   }

   // Si no se encuentra ninguna arista blanca, salir del algoritmo
   if (!cubo_edge) return;

   // Determinar la orientación de la arista blanca
   MiniCubo::Color color_opuesto = (cubo_edge->derecha == centro) ? cubo_edge->izquierda : cubo_edge->derecha;
   bool orientacion_correcta = (cubo_edge->arriba == color_opuesto);

   // Girar la capa apropiada para alinear la arista con el centro blanco

   // Mover la arista al borde inferior del centro blanco
}
#endif

