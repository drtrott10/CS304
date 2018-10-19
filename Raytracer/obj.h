#ifndef OBJ_H
#define OBJ_H
#include "sphere.h"
#include "rt.h"

typedef struct OBJ_T{
	SPHERE_T sphere;
	COLOR_T color;
	struct OBJ_T *next;
}OBJ_T;


#endif
