
#ifndef math_triangle_h
#define math_triangle_h

// ___________________________________________________

#include "vec.h"
#include "triangle6f.h"
#include "triangle3f.h"
#include "triangle3us.h"

#pragma mark array types -----------------------------

typedef struct{
	
	triangle6f* data;
	int count;
	
}triangle6fv;

typedef struct{
	
	triangle3us* data;
	int count;
	
}triangle3usv;

#pragma mark additional operations -------------------

triangle6f t6fWithTriangle3f(const triangle3f* t);

triangle6f t6fWithTriangle3fAndNormal(const triangle3f* t,
									  const v3f* normal);

// ___________________________________________________

#endif