//Reeves Trott
//CS304 Assignment 5
//Prof Davis
//This is a program in C that implements a ray casting renderer and produces
//a 2D image of spheres. A file of sphere information will be provided.
//My code produces a PPM image of 1000x1000 pixels

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "rc.h"

//iterates through linked list; finds closest intersection using
//intersect_sphere; returns color of closest sphere
COLOR_T cast(RAY_T ray, OBJ_T *list) {
      OBJ_T *curr;
	    double min_t = 1000.0;
	    double t;
	    COLOR_T color;
	    color.r = 1.0;
	    color.g = 1.0;
	    color.b = 1.0;
	    for (curr = list; curr != NULL; curr = curr->next) {
	        if (intersect_sphere(ray, curr->sphere, &t)) {
	            if (t < min_t) {
	                color = curr->color;
	                min_t = t;
	            }
	        }
	    }
	    return color;
	}
//Return 1 if an intersection is found. Returns 0 if no intersection found
//sets  *t to the smaller of the intersections found if 2 intersections are found
int intersect_sphere(RAY_T ray, SPHERE_T sphere, double *t) {
	    double A = 1.0;
	    double B = 2 * ((ray.direction.x * (ray.origin.x - sphere.center.x)) +
	                    (ray.direction.y * (ray.origin.y - sphere.center.y)) +
	                    (ray.direction.z * (ray.origin.z - sphere.center.z)));

	    double C = (ray.origin.x - sphere.center.x) * (ray.origin.x - sphere.center.x) +
                 (ray.origin.y - sphere.center.y) * (ray.origin.y - sphere.center.y) +
	               (ray.origin.z - sphere.center.z) * (ray.origin.z - sphere.center.z) -
	               (sphere.radius * sphere.radius);

	    double discrim = (B * B) - 4*A*C;
	    if (discrim < 0) {
	        return 0;
	    }
	    float t0 = (-B + sqrt(discrim)) / 2*A;
	    float t1 = (-B - sqrt(discrim)) / 2*A;
	    if (t0 < 0 && t1 < 0) {
	        return 0;
	    }
      if(t0 < t1) {
        *t = t0;
      }
      else {
        *t = t1;
      }
      return 1;
	}
//reads spheres from stdin; creates linked list using dynamic memory
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
        ray.direction.z = 1;

        ray.direction = normalize(ray.direction);
        curr = list;
        pxl = cast(ray, list);

        printf("%c%c%c", (unsigned char)(pxl.r*255),
                         (unsigned char)(pxl.g*255),
                         (unsigned char)(pxl.b*255));
    }
}
  while (list != NULL) {
      curr = list;
      list = list->next;
      free(curr);
  }
}
