//Reeves Trott
//CS304 Assignment 8
//Prof Davis
//a program in C that extends your ray casting code from Assignment 5 to a ray tracer,
//which will render an image of 3D spheres with lighting. The previous file of sphere 
//information will also be used for this project. Your code should produce a PPM image of 
//1000x1000 pixels with a black background.

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "rt.h"
#include "obj.h"
#include "light.h"

//as before, but keeps closest intersection point and closest normal; 
//calls illuminate method for light and returns lighted color of closest sphere
COLOR_T trace(RAY_T ray, OBJ_T *list, LIGHT_T light) {
      OBJ_T *curr;
	    double min_t = 1000.0;
	    double t;
      COLOR_T surface_col;
      COLOR_T color;
      VEC_T int_pt;
      VEC_T closest_int_pt;
      VEC_T normal;
      VEC_T closest_normal;
      OBJ_T *closest_obj = NULL;
	    color.r = 0.0;
	    color.g = 0.0;
	    color.b = 0.0;
	    for (curr = list; curr != NULL; curr = curr->next) {
	        if (intersect_sphere(ray, curr->sphere, &t, &int_pt, &normal)) {
	            if (t < min_t) {
	                color = curr->color;
	                min_t = t;
                  closest_obj = curr;
                  closest_int_pt = int_pt;
                  closest_normal = normal;
	            }
	        }
	    }
      if (closest_obj != NULL){
        color = illuminate(ray, light, list, color, closest_int_pt, closest_normal);
      }
  return color;
}
void read_objs(OBJ_T **list) {
	    double ctr_x, ctr_y, ctr_z;
	    double radius;
	    double r, g, b;
	    OBJ_T *node;

	    while (scanf("%lf %lf %lf %lf %lf %lf %lf",
                    &ctr_x, &ctr_y, &ctr_z, &radius, &r, &g, &b) == 7) {

          node = (OBJ_T *)malloc(sizeof(OBJ_T));

          node->sphere.center.x = ctr_x;
	        node->sphere.center.y = ctr_y;
	        node->sphere.center.z = ctr_z;
	        node->sphere.radius = radius;

          node->color.r = r;
	        node->color.g = g;
	        node->color.b = b;

          node->next = *list;
	        *list = node;
	    }
	}

//Goes through every pixel, normalizes it and makes the resolution 1000x10000 pixels
//Then sets the color of that pixel, then frees the memory in the linked list
int main() {
   RAY_T ray;
   OBJ_T *curr;
   OBJ_T *list = NULL;
   COLOR_T pxl;
   double t;
   int x, y;
   LIGHT_T light;
    light.loc.x = 5.0;
    light.loc.y = 10.0;
    light.loc.z = 0.0;

   read_objs(&list);

   printf("P6\n");
   printf("1000 1000\n");
   printf("255\n");

	 for (y = 0; y <= 999; y++) {
      for (x = 0; x <= 999; x++) {


        ray.origin.x = 0;
        ray.origin.y = 0;
        ray.origin.z = 0;

        ray.direction.x = -0.5 + x / 1000.0;
        ray.direction.y = 0.5 - y / 1000.0;
        ray.direction.z = 1.0;

        ray.direction = normalize(ray.direction);
        //curr = list;
        pxl = trace(ray, list, light);

        
        if (pxl.r > 1.0){
            pxl.r = 1.0;
        }
        if (pxl.g > 1.0){
            pxl.g = 1.0;
        }
        if (pxl.b > 1.0){
            pxl.b = 1.0;
        }


        printf("%c%c%c", (unsigned char)(pxl.r * 255.0),
                         (unsigned char)(pxl.g * 255.0),
                         (unsigned char)(pxl.b * 255.0));
    }
}
  while (list != NULL) {
      curr = list;
      list = list->next;
      free(curr);
  }
}


