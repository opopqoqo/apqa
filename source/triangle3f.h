
#ifndef math_triangle3f_h
#define math_triangle3f_h

// ___________________________________________________

#include "vec.h"
#include <stdbool.h>

#pragma mark definition ------------------------------

typedef struct{
	
	v3f data[3];
	
}triangle3f;

#pragma mark constructors ----------------------------

triangle3f t3fWithPoints(const v3f* A,
						 const v3f* B,
						 const v3f* C);

triangle3f t3fFlipped(const triangle3f* t);

#pragma mark getting information ---------------------

v3f t3fVector(const triangle3f* t,int i);
v3f t3fNormal(const triangle3f* t);

bool t3fIsInvalid(const triangle3f* t);

#pragma mark operations ------------------------------

void t3fTranslate(triangle3f* t,const v3f* u);

#pragma mark debugging -------------------------------

void t3fPrint(const triangle3f* T);

void t3fAssert(const triangle3f* T);

void t3fAssertEquals(const triangle3f* A,
					 const triangle3f* B);

#endif