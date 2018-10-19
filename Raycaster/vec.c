//Reeves Trott
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
