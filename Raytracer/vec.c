//Reeves Trott
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "vec.h"

//self-explanitory... normalizes v
VEC_T normalize(VEC_T v){
    double divider;
    divider = sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));

    VEC_T norm;
    norm.x = (v.x / divider);
    norm.y = (v.y / divider);
    norm.z = (v.z / divider);

    return norm;
}
double dot(VEC_T v1, VEC_T v2) {
	double dotProduct = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    return dotProduct;
}
