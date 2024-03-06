#ifndef ALGORITMOS_H
#define ALGORITMOS_H

#include "rubik.h"
#include "principiante.h"
#include "fridich.h"

// Funciones para resolver el cubo Rubik según diferentes métodos
void resolverPrincipiante(Rubik& cuboRubik);
void resolverCapaPorCapa(Rubik& cuboRubik);
void resolverFridrichCFOP(Rubik& cuboRubik);
void resolverRoux(Rubik& cuboRubik);
void resolverPetrus(Rubik& cuboRubik);


void resolverPrincipiante(Rubik& cuboRubik)
{
    construirCruzBlanca(cuboRubik);
}

void resolverCapaPorCapa(Rubik& cuboRubik)
{
    //aa
}
void resolverFridrichCFOP(Rubik& cuboRubik)
{
    solveFridich(cuboRubik);
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
