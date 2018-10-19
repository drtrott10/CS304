#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "sphere.h"

//as before, but also computes intersection point and normal
int intersect_sphere(RAY_T ray, SPHERE_T sphere, double *t,VEC_T *int_pt, VEC_T *normal) {
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


    int_pt->x = (ray.origin.x + (ray.direction.x * *t));
    int_pt->y = (ray.origin.y + (ray.direction.y * *t));
    int_pt->z = (ray.origin.z + (ray.direction.z * *t));
    //double int_pointer = int_pt->x + int_pt->y + int_pt->z;
    normal->x = (int_pt->x - sphere.center.x)/sphere.radius;
    normal->y = (int_pt->y - sphere.center.y)/sphere.radius;
    normal->z = (int_pt->z - sphere.center.z)/sphere.radius;
    //*normal = normalize(*normal);
    //double norm = (normal->x + normal->y + normal->z);

    return 1;
}
