#ifndef ALGORITMOS_H
#define ALGORITMOS_H

#include "rubik.h"
#include "../Fridrich/fridich.h"

// Funciones para resolver el cubo Rubik según diferentes métodos
void resolverPrincipiante(Rubik& cuboRubik);
void resolverCapaPorCapa(Rubik& cuboRubik);
void resolverFridrichCFOP(Rubik& cuboRubik);
void resolverRoux(Rubik& cuboRubik);
void resolverPetrus(Rubik& cuboRubik);


void resolverPrincipiante(Rubik& cuboRubik)
{
    //
}

void resolverCapaPorCapa(Rubik& cuboRubik)
{
    //aa
}
void resolverFridrichCFOP(Rubik& cuboRubik)
{
    ejecutarCruz(cuboRubik);
    ejecutarF2L(cuboRubik);
    ejecutarOLL(cuboRubik);
    ejecutarPLL(cuboRubik);
}
void resolverRoux(Rubik& cuboRubik)
{
    //
}
void resolverPetrus(Rubik& cuboRubik)
{
    //
}


#endif // ALGORITMOS_H
