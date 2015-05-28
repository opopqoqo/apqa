// Copyright T.E.A de Souza 2012-2015 - MIT LICENSE

#ifndef math_triangle6f_h
#define math_triangle6f_h

//____________________________________________________

#include <stdbool.h>
#include "vec.h"
#include "matrix.h"

#pragma mark struct ----------------------------------

typedef struct{
	
	v6f data[3];
	
}triangle6f;

#pragma mark constructors ----------------------------

triangle6f t6fFlipped(const triangle6f* t);
triangle6f t6fWithPoints(const v6f* A,
						 const v6f* B,
						 const v6f* C);

#pragma mark operations ------------------------------

void t6fTransform(triangle6f* t, const m4f* matrix);

void t6fTranslate(triangle6f* t,const v3f* u);

void t6fMakeSharpEdges(triangle6f* t);

#pragma mark getting information ---------------------

bool t6fIsInvalid(const triangle6f* t);

bool t6fIsDegenerate(const triangle6f* t);

bool t6fIsContiguous(const triangle6f* A,
					 const triangle6f* b,
					 float threshold);

bool t6fIsZero(const triangle6f* t);

float t6fArea(const triangle6f* t);

v3f t6fVector(const triangle6f* t,int i);

v3f t6fNormal(const triangle6f* t);

#pragma mark debugging -------------------------------

void t6fPrint(const triangle6f* tri);

void t6fAssertEquals(const triangle6f* A,
					 const triangle6f* B);

void t6fAssert(const triangle6f* t);

void t6fZero(triangle6f* t);

#endif