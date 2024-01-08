#include <cstdlib>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

#include "cabecera.h"

int main(int argc, char const *argv[]) {
  source fuente;
  fuente.p.assign(-3, 0, 0); // Punto
  fuente.createRay(2, 1, 0); // Rayo
  fuente.changeEnergy(1000);
  fuente.NRAYS = 10;
  printf("Datos de la fuente:(Posicion inicial: (%f,%f,%f)\nEnergia la fuente: %f\n Número de rayos: %f\nDireccion de partida: (%f,%f,%f)",
    fuente.p.x,fuente.p.y,fuente.p.z,
    fuente.eF,
    fuente.NRAYS,
    fuente.Rays->x,fuente.Rays->y,fuente.Rays->z
    );
  return 0;
}
