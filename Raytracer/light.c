#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "light.h"
#include "vec.h"
#include "obj.h"



COLOR_T illuminate(RAY_T ray, LIGHT_T light, OBJ_T *list, COLOR_T surface_col, VEC_T int_pt, VEC_T normal){

    VEC_T loc;
	COLOR_T color;
    normal = normalize(normal);
	//ambient lighting 
	color.r = 0.2 * surface_col.r;
	color.g = 0.2 * surface_col.g;
    color.b = 0.2 * surface_col.b;

    //Diffuse lighting
    VEC_T L;
    L.x = (light.loc.x - int_pt.x);
    L.y = (light.loc.y - int_pt.y);
    L.z = (light.loc.z - int_pt.z);
    L = normalize(L);
    double dot3 = dot(L, normal);

    if(dot3 > 0){
    color.r += dot3 * surface_col.r;
    color.g += dot3 * surface_col.g;
    color.b += dot3 * surface_col.b;
    
    VEC_T R;
    R.x = L.x - (normal.x * dot3 * 2);
    R.y = L.y - (normal.y * dot3 * 2);
    R.z = L.z - (normal.z * dot3 * 2);
    R = normalize(R);

    double dot2 = dot(R, ray.direction);

        if(dot2 > 0){
            color.r += pow(dot2,200);
            color.g += pow(dot2,200);
            color.b += pow(dot2,200);
        }
    }

	return color;


}

