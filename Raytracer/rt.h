//Reeves Trott
#ifndef RT_H
#define RT_H
#include "vec.h"
//#include "obj.h"
//#include "light.h"


typedef struct{
  VEC_T origin;
  VEC_T direction;
} RAY_T;

typedef struct{
  double r;
  double g;
  double b;
} COLOR_T;

//COLOR_T trace(RAY_T ray, OBJ_T *list, LIGHT_T light);

#endif
