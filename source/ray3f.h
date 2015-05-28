
#ifndef math_ray_h
#define math_ray_h

// ___________________________________________________

#include "vec.h"
#include "plane3f.h"
#include "sphere3f.h"

// ---------------------------------------------------

// anything that avoids division overflow
#define SMALL_NUM  1e-5
#define dot(u,v)   ((u).x * (v).x + (u).y * (v).y + (u).z * (v).z)

#define qcross(a,b,c,ux,uy,uz,vx,vy,vz) \
float a=uy*vz-vy*uz;					       \
float b=uz*vx-vz*ux;					       \
float c=ux*vy-vx*uy

#define qcross2(u,v,w) \
w.x=u.y*v.z-v.y*u.z;   \
w.y=u.z*v.x-v.z*u.x;   \
w.z=u.x*v.y-v.x*u.y

#pragma mark struct ----------------------------------

typedef struct{

	v3f origin;
	v3f direction;
	
}ray3f;

#pragma mark constructors ----------------------------

#pragma mark operations ------------------------------

v3f r3fIntersectPlane(const ray3f* ray,
					  const p3f* plane);

v3f r3fIntersectSphere(const ray3f* ray,
					   const sphere3f* plane);

v3f r3fProject(const v3f* P,const ray3f* r);

// ___________________________________________________

#endif