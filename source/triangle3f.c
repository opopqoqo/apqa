
#include "triangle3f.h"
#import "vecmath3f.h"
//
#include <stdio.h>

// ___________________________________________________

#define A data[0]
#define B data[1]
#define C data[2]

#pragma mark constructors ----------------------------

triangle3f t3fWithPoints(const v3f* A0,
						 const v3f* B0,
						 const v3f* C0){
	
	triangle3f t;
	
	t.A = *A0;
	t.B = *B0;
	t.C = *C0;
	
	return t;
	
}

triangle3f t3fFlipped(const triangle3f* t){

	triangle3f r;
	
	r.A = t->C;
	r.B = t->B;
	r.C = t->A;
	
	return r;
	
}

#pragma mark operations ------------------------------

void t3fTranslate(triangle3f* t,const v3f* u){

	for(v3f* P = t->data; P < t->data+3; P++){
	
		v3fAdd(P, u);
		
	}
	
}

#pragma mark getting information ---------------------

v3f t3fNormal(const triangle3f* t){

	v3f u = t3fVector(t,0);
	v3f v = t3fVector(t,1);
	v3f w = v3fCross(&u, &v);
	
	v3fNormalize(&w);
	v3fMul(&w, 1.0);
	
	return w;
	
}

v3f t3fVector(const triangle3f* t,int i){

	return v3fMake(&t->data[i], &t->data[(i+1)%3]);
	
}

bool t3fIsInvalid(const triangle3f* t){
	
	for(int i=0;i<3;i++){
		
		if(v3fIsDegenerate(t->data))return true;
		
	} return false;
	
}

#pragma mark debug -----------------------------------

void t3fPrint(const triangle3f* tri){
	
	printf("triangle3f{\n");
	
	for(int i=0;i<3;i++){
		
		printf("\tco{%f %f %f}\n",
			   tri->data[i].x,
			   tri->data[i].y,
			   tri->data[i].z);
		
	}printf("}\n");
	
}

void t3fAssert(const triangle3f* T){

	for(int i=0;i<3;i++){
		v3fAssert(&T->data[i]);
	}
	
}

void t3fAssertEquals(const triangle3f* t0,
					 const triangle3f* t1){
	
	for(int i=0;i<3;i++){
		v3fAssertEquals(&t0->data[i], &t1->data[i]);
	}
	
}