#include <math.h>
#include "headers/cidade.h"

double distancia(Cidade A, Cidade B) {
    return sqrt(pow(A.x - B.x, 2) + pow(A.y - B.y, 2));
}