// Copyright T.E.A de Souza 2012-2015 - MIT LICENSE

#include "triangle6f.h"
#include <stdio.h>
#include "vecmath3f.h"
#include "vector6f.h"

#define for_each_vertex(v,t) \
for(v6f* v = t->data; v<t->data+3; v++)

#pragma mark constructors ----------------------------

triangle6f t6fWithPoints(const v6f* A0,
						 const v6f* B0,
						 const v6f* C0){
	
	triangle6f t;
	t.data[0] = *A0;
	t.data[1] = *B0;
	t.data[2] = *C0;
	
	return t;
	
}

triangle6f t6fFlipped(const triangle6f* t){

	triangle6f r; for(int i=0;i<3;i++){
	
		r.data[i] = t->data[2-i];
		v3fNeg(&r.data[i].normal);
	
	}return r;
	
}

#pragma mark operations ------------------------------

void t6fTransform(triangle6f* t, const m4f* matrix){
	
	for_each_vertex(v, t){
		v6fTransform(v,matrix);
	}
	
}

void t6fTranslate(triangle6f* t,const v3f* u){

	for(v6f* P=t->data;P<t->data+3;P++){
	
		v3fAdd(&P->coord,u);
		
	}
	
}

void t6fZero(triangle6f* t){

	for(int i=0;i<3;i++){
	
		v3fZero( &t->data[i].coord );
		
	}
	
}

void t6fMakeSharpEdges(triangle6f* t){

	v3f N = t6fNormal(t);

	for_each_vertex(v, t){
	
		v->normal = N;
		
	}
	
}

bool t6fIsDegenerate(const triangle6f* t){
	
	v3f N = t6fNormal(t);
	return v3fIsNaN(&N);
	
}

bool t6fIsInvalid(const triangle6f* t){
	
	for(int i=0;i<3;i++){
		
		if(v3fIsDegenerate(&t->data[i].coord))return true;
		if(v3fIsDegenerate(&t->data[i].normal))return true;
		
	} return false;
	
}

#pragma mark getting information ---------------------

v3f t6fNormal(const triangle6f* t){
	
	v3f u = t6fVector(t,0);
	v3f v = t6fVector(t,1);
	v3f w = v3fCross(&u, &v);
	
	v3fNormalize(&w);
	v3fMul(&w, 1.0);
	
	return w;
	
}

bool t6fIsContiguous(const triangle6f* A,
					 const triangle6f* B,
					 float t){

	for(int i=0;i<3;i++){
	
		for(int j=0;j<3;j++){
		
			const v3f* a = &A->data[i].coord;
			const v3f* b = &B->data[j].coord;
			
			if( v3fEquals( a,b) )	 return true;
			
			if( v3fDistance(a,b)<t ) return true;
			
		}
		
	} return false;
	
}

bool t6fIsZero(const triangle6f* t){
	
	for(int i=0;i<3;i++){
		
		if( !v3fIsZero(&t->data[i].coord) ){
			return false;
		}
		
	}return true;
	
}

float t6fArea(const triangle6f* t){

	//((p0 - p1).cross(p0 - p2)).length() * 0.5f;

	v3f u = t6fVector(t,0);
	v3f v = t6fVector(t,1);

	v3f w=v3fCross(&u, &v);
	return v3fLength(&w)*0.5;
	
	return 0;
	
}

v3f t6fVector(const triangle6f* t,int i){
	
	return v3fMake(&t->data[i].coord,
				   &t->data[(i+1)%3].coord);
	
}

#pragma mark debugging -------------------------------

void t6fPrint(const triangle6f* tri){
	
	printf("triangle6f{\n");
	
	for(int i=0;i<3;i++){
		
		printf("\tco{%f %f %f}",
			   tri->data[i].coord.x,
			   tri->data[i].coord.y,
			   tri->data[i].coord.z);
		
		printf("no{%f %f %f}\n",
			   tri->data[i].normal.x,
			   tri->data[i].normal.y,
			   tri->data[i].normal.z);
		
	}printf("}\n");
	
}

void t6fAssert(const triangle6f* t){

	for(int i=0;i<3;i++){
		v6fAssert(&t->data[i]);
	}
	
}

void t6fAssertEquals(const triangle6f* A,const triangle6f* B){
	
	for(int i=0;i<3;i++){
		
		v3fAssertEquals(&A->data[i].coord, &B->data[i].coord);
		v3fAssertEquals(&A->data[i].normal, &B->data[i].normal);
		
	}
	
}
