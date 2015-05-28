
#ifndef math_mesh6f_h
#define math_mesh6f_h

#include "triangle6f.h"
#include <stdbool.h>

#pragma mark structure -------------------------------

typedef struct{
	
	triangle6f* faces;
	int count;
	
}mesh6f;

#pragma mark constructors ----------------------------

mesh6f m6fWithData( triangle6f* data, int count );

mesh6f m6fWithMaxTriangleCount( int count );

mesh6f m6fOrthoPrismWithPoints(const v3f* A,
							   const v3f* B,
							   const v3f* C,
							   float thickness);

#pragma mark operations ------------------------------

mesh6f m6fDuplicate( const mesh6f* );

mesh6f* m6fParts(const mesh6f mesh,
				 float threshold,
				 int* count);

void m6fAddTriangle(mesh6f *mesh,
					const triangle6f* t);

triangle6f m6fRemoveTriangle(mesh6f *mesh,
							 int index);

void m6fTransform(mesh6f* m, const m4f* matrix);

#pragma mark getting information ---------------------

float m6fMin(const mesh6f* m,int d);
float m6fMax(const mesh6f* m,int d);

bool m6fIsMeshContiguous(const mesh6f* m,
						 const mesh6f* that,
						 float threshold);

bool m6fIsTriangleContiguous(const mesh6f* m,
							 const triangle6f* that,
							 float threshold);

float m6fArea(const mesh6f* m);

#pragma mark debugging -------------------------------

void m6fAssert(const mesh6f m);

#endif
