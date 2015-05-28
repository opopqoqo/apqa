// Copyright T.E.A de Souza 2012-2015 - MIT LICENSE

#include <stdlib.h>
#include <memory.h>
#include <assert.h>
#include <stdio.h>
//
#include "mesh6f.h"
#include "vector6f.h"
#include "triangle.h"
#include "vecmath3f.h"
#include "matrix.h"

// ___________________________________________________

#define for_each_triangle(t,m) \
for(triangle6f* t = m->faces; t<m->faces+m->count; t++)

#define for_each_triangle2(t,m) \
for(triangle6f* t = m.faces; t<m.faces+m.count; t++)

// ___________________________________________________

mesh6f m6fWithData( triangle6f* data, int count ){

	mesh6f m;
	m.faces = data;
	m.count = count;
	return m;
	
}

mesh6f m6fWithMaxTriangleCount( int count ){

	mesh6f m;
	m.faces = malloc(sizeof(triangle6f)*count);
	m.count = 0;
	return m;
	
}

mesh6f m6fDuplicate( const mesh6f* m0){

	int bytecount = sizeof(triangle6f) * m0->count;
	
	mesh6f m;
	
	m.faces = malloc( bytecount );
	m.count = m0->count;
	memcpy(m.faces, m0->faces, bytecount);
	
	//m6fAssert(m);
	
	return m;
	
}

mesh6f m6fOrthoPrismWithPoints(const v3f* pA,
							   const v3f* pB,
							   const v3f* pC,
							   float thickness){

	triangle3f prism[8];
	
	// create the base
	
	prism[0] = t3fWithPoints(pA,pB,pC);

	// create the top
	
	prism[1] = t3fFlipped(&prism[0]);
	v3f N = t3fNormal(&prism[1]);
	v3fMul(&N,thickness);
	t3fTranslate(&prism[1],&N);
	
	int k = 2; for(int i=0;i<3;i++){
		
		int j = (i+1)%3;
		
		v3f A = prism[0].data[i];
		v3f B = prism[1].data[2-i];
		v3f C = prism[1].data[2-j];
		v3f D = prism[0].data[j];
		
		prism[k] =
		t3fWithPoints(&A, &B, &C);
		prism[k+1] =
		t3fWithPoints(&C, &D, &A);
		
		t3fAssert(&prism[k]);
		t3fAssert(&prism[k+1]);
		
		k+=2;
		
	}
	
	triangle6f* data = malloc(sizeof(triangle6f)*8);
	
	for(int i=0;i<8;i++){
		data[i]=t6fWithTriangle3f(&prism[i]);
		t6fAssert(&data[i]);
	}
	
	mesh6f mesh = m6fWithData(data, 8);
	return mesh;
	
}

#pragma mark operations ------------------------------

triangle6f m6fRemoveTriangle(mesh6f *mesh,
							 int i){
	
	int c = mesh->count;
	assert(i<c);
	
	triangle6f T = mesh->faces[i];
	
	t6fAssert(&T);
	
	int last = c-1;
	
	mesh->faces[i]	= mesh->faces[last];
	mesh->count		= last;
	
	return T;
	
}

void m6fAddTriangle(mesh6f* m,const triangle6f* T){

	m->faces[m->count] = *T;
	m->count++;
	
}

void m6fTransform(mesh6f* m, const m4f* matrix){

	for_each_triangle(t, m){
	
		t6fTransform(t,matrix);
		
	}
	
}

float m6fMin(const mesh6f* m, int d){
	
	float min = 1000000.0f;
	
	for_each_triangle(t, m){
		
		for(int i=0;i<3;i++){
		
			float* p = (float*)&t->data[i].coord;
			
			if( p[d] < min){
				min = p[d];
			}
			
		}
		
	}return min;
	
}

float m6fMax(const mesh6f* m, int d){
	
	float min = -1000000.0f;
	
	for_each_triangle(t, m){
		
		for(int i=0;i<3;i++){
			
			float* p = (float*)&t->data[i].coord;
			
			if( p[d] > min){
				min = p[d];
			}
			
		}
		
	}return min;
	
}

mesh6f* m6fParts(const mesh6f mesh0,
				 float th,
				 int* numberOfParts){

	//m6fAssert(mesh0);
	
	mesh6f mesh = m6fDuplicate(&mesh0);
	
	m6fAssert(mesh);
	
	*numberOfParts = 0;

	mesh6f* parts = malloc(sizeof(mesh6f)*32);
	
	while(mesh.count>0){

		// init a new mesh in parts array
		
		mesh6f* part = &parts[*numberOfParts];
		*part = m6fWithMaxTriangleCount(mesh.count);
		*numberOfParts=(*numberOfParts)+1;
		
		// init part with first available triangle

		triangle6f T = m6fRemoveTriangle(&mesh, 0);
				
		m6fAddTriangle(part,&T);

		m6fAssert(*part);
		
		for(int next=0; next < part->count; next++ ){
			
			triangle6f* T = &part->faces[next];
			
			for( int i=mesh.count-1 ; i>=0 ;i--){
				
				triangle6f* C = &mesh.faces[i];
				
				if(t6fIsContiguous(T, C, th)){
					
					m6fAddTriangle(part,C);
					m6fRemoveTriangle(&mesh,i);
					
				}
				
			} //m6fAssert(*part);
			
		}
		
		printf("added to part:%i\n",part->count);
		
	}
	
	/*
	for(int i=0;i<*numberOfParts;i++){
		for(int j=i+1;j<*numberOfParts;j++){
			assert(!m6fIsMeshContiguous(parts+i, parts+j,th));
		}
	}*/
	
	printf("number of parts:%i\n",*numberOfParts);
	
	return parts;
	
}

bool m6fIsTriangleContiguous(const mesh6f* m,
							 const triangle6f* that,
							 float th){

	for_each_triangle(t,m){
		
		if(t6fIsContiguous(t,that,th)){
			
			return true;
			
		}
		
	} return false;
		  
}

bool m6fIsMeshContiguous(const mesh6f* A,
						 const mesh6f* B,
						 float t){
	
	for(int i=0; i<A->count; i++){
		
		for(int j=0; j>B->count; j++){
		
			if( t6fIsContiguous(&A->faces[i],
								&B->faces[j],
								t) ){
			
				return true;
				
			}
			
		}
		
	} return false;
	
}

float m6fArea(const mesh6f* m){

	float area = 0;
	
	for_each_triangle(t,m){
	
		area+=t6fArea(t);
		
	} return area;
	
}

void m6fAssert(const mesh6f m){

	assert(m.count>0);
	
	for_each_triangle2(t,m){
		t6fAssert(t);
	}
	
}
