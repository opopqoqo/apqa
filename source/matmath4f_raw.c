
#import "matmath4f_raw.h"
//
#import <math.h>
#import <stdio.h>
#import <stdlib.h>
#import <memory.h>
#import <OpenGLES/ES1/glext.h>
//
#import "vecmath3f.h"
#import "xmath.h"

#include "invert_matrix4x4.h"

/*
 Sources:
 mathisfun.com
 http://www.mathsisfun.com/algebra/matrix-multiplying.html
 
 matrix44.net
 http://www.matrix44.net/cms/notes/opengl-3d-graphics/basic-3d-math-matrices
 
 Matrix elements
 
 0	1	2	3
 4	5	6	7
 8	9	10	11
 12	13	14	15
 
 These functions can be tested against GPU code. Example:
 
 float m0[16]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
 float m1[16]={17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32};
 float m2[16];
 
 glMatrixMode(GL_MODELVIEW);
 glPushMatrix();
 glLoadMatrixf(m0);
 glMultMatrixf(m1);
 glGetFloatv(GL_MODELVIEW_MATRIX, m2);
 glPopMatrix();
 mPrint(m2);
 
 The above gives a matrix multiplication result that can be reproduced
 using:
 
 mMultMatrixf(m0,m1)
 
 */

float* mTranslationComponent(float* m){
	return &m[12];
}

void mLoadMatrix(float* m4x4, const float* arg4x4){
	
	memcpy(m4x4, arg4x4, sizeof(float)*16);
	
}

void mLoadIdentity(float* m){
	
	float T[16]={
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};
	
	for(int i=0;i<16;i++)m[i]=T[i];
	
}

#define dot_product(c,v) ( c[0]* v[0] + c[1]*v[1] + c[2] * v[2] )

/**
 * @see http://www.gamespp.com/tutorials/matrixTransformationTutorial04.html
 */
void mTransformV3f(float* p, const float* m){
	
	float col0[3]={m[0],m[4],m[8]};
	float col1[3]={m[1],m[5],m[9]};
	float col2[3]={m[2],m[6],m[10]};
	
	float dotX = dot_product(col0,p);
	float dotY = dot_product(col1,p);
	float dotZ = dot_product(col2,p);
	
	float x = dotX + m[12];
	float y = dotY + m[13];
	float z = dotZ + m[14];
	
	p[0]=x;
	p[1]=y;
	p[2]=z;
	
}

void mMultVector4f(float* u,const float* m){

	float x[] = {
		m[0] * u[0] + m[4] * u[1] + m[8] * u[2] + m[12] * u[3],
		m[1] * u[0] + m[5] * u[1] + m[9] * u[2] + m[13] * u[3],
		m[2] * u[0] + m[6] * u[1] + m[10] * u[2] + m[14] * u[3],
		m[3] * u[0] + m[7] * u[1] + m[11] * u[2] + m[15] * u[3]
	};
	
	memcpy(u,x,sizeof(float)*4);
	
}

#undef dot_product

void mMultMatrixf(float* B, const float* A){
	
	// 1st row
	
#define a 0
#define b 1
#define c 2
#define d 3
	
	float k0 = A[a]*B[0] + A[b]*B[4] + A[c]*B[8] + A[d]*B[12];
	float k1 = A[a]*B[1] + A[b]*B[5] + A[c]*B[9] + A[d]*B[13];
	float k2 = A[a]*B[2] + A[b]*B[6] + A[c]*B[10] + A[d]*B[14];
	float k3 = A[a]*B[3] + A[b]*B[7] + A[c]*B[11] + A[d]*B[15];
	
	// 2nd row
	
#undef a
#undef b
#undef c
#undef d
#define a 4
#define b 5
#define c 6
#define d 7
	
	float k4 = A[a]*B[0] + A[b]*B[4] + A[c]*B[8] + A[d]*B[12];
	float k5 = A[a]*B[1] + A[b]*B[5] + A[c]*B[9] + A[d]*B[13];
	float k6 = A[a]*B[2] + A[b]*B[6] + A[c]*B[10] + A[d]*B[14];
	float k7 = A[a]*B[3] + A[b]*B[7] + A[c]*B[11] + A[d]*B[15];
	
	// 3rd row
	
#undef a
#undef b
#undef c
#undef d
#define a 8
#define b 9
#define c 10
#define d 11
	
	float k8 = A[a]*B[0] + A[b]*B[4] + A[c]*B[8] + A[d]*B[12];
	float k9 = A[a]*B[1] + A[b]*B[5] + A[c]*B[9] + A[d]*B[13];
	float k10 = A[a]*B[2] + A[b]*B[6] + A[c]*B[10] + A[d]*B[14];
	float k11 = A[a]*B[3] + A[b]*B[7] + A[c]*B[11] + A[d]*B[15];
	
	// 4th row
	
#undef a
#undef b
#undef c
#undef d
#define a 12
#define b 13
#define c 14
#define d 15
	
	float k12 = A[a]*B[0] + A[b]*B[4] + A[c]*B[8] + A[d]*B[12];
	float k13 = A[a]*B[1] + A[b]*B[5] + A[c]*B[9] + A[d]*B[13];
	float k14 = A[a]*B[2] + A[b]*B[6] + A[c]*B[10] + A[d]*B[14];
	float k15 = A[a]*B[3] + A[b]*B[7] + A[c]*B[11] + A[d]*B[15];
	
	// Hurray!
	
#define R B
	
	R[0]=k0;
	R[1]=k1;
	R[2]=k2;
	R[3]=k3;
	R[4]=k4;
	R[5]=k5;
	R[6]=k6;
	R[7]=k7;
	R[8]=k8;
	R[9]=k9;
	R[10]=k10;
	R[11]=k11;
	R[12]=k12;
	R[13]=k13;
	R[14]=k14;
	R[15]=k15;
	
}

void mLoadTranslation(float* m,float x,float y,float z){
	
	float T[16]={
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		x,y,z,1
	};
	
	for(int i=0;i<16;i++)m[i]=T[i];
	
}

void mLoadScale(float* m,float x,float y,float z){
	
	float T[16]={
		x,0,0,0,
		0,y,0,0,
		0,0,z,0,
		0,0,0,1
	};
	
	for(int i=0;i<16;i++)m[i]=T[i];
	
}

/* @test */
void mTranspose(float* m){
	
	float T[16]={
		m[0],m[4],m[8 ],m[12],
		m[1],m[5],m[9 ],m[13],
		m[2],m[6],m[10],m[14],
		m[3],m[7],m[11],m[15]
	};
	
	for(int i=0;i<16;i++){
		m[i]=T[i];
	}
	
}

void mInverse(float* m){
	
	float m1[16];
	
	inverseMatrix4x4( (float*) m, (float*) m1 );
	m=m1;
	
}

void mPrint(float* m){
	
	printf("| %.2f %.2f %.2f %.2f |\n",
		   m[0],m[1],m[2],m[3]);
	printf("| %.2f %.2f %.2f %.2f |\n",
		   m[4],m[5],m[6],m[7]);
	printf("| %.2f %.2f %.2f %.2f |\n",
		   m[8],m[9],m[10],m[11]);
	printf("| %.2f %.2f %.2f %.2f |\n",
		   m[12],m[13],m[14],m[15]);
	
}

void mLoadRotationX(float* m,float A){
	
	A*=(M_PI/180.0f);
	
	float T[16]={
		1,	0,			0,		0,
		0,	cos(A),		sin(A),	0,
		0,	-sin(A),	cos(A),	0,
		0,	0,			0,		1
	};
	
	for(int i=0;i<16;i++)m[i]=T[i];
	
}

void mLoadRotationY(float* m,float A){
	
	A*=(M_PI/180.0f);
	
	float T[16]={
		cos(A),	0,	-sin(A),	0,
		0,		1,	0,			0,
		sin(A),	0,	cos(A),		0,
		0,		0,	0,			1
	};
	
	for(int i=0;i<16;i++)m[i]=T[i];
	
}

void mLoadRotationZ(float* m,float A){
	
	A*=(M_PI/180.0f);
	
	float T[16]={
		cos(A),	sin(A),	0,	0,
		-sin(A),cos(A),	0,	0,
		0,		0,		1,	0,
		0,		0,		0,	1
	};
	
	for(int i=0;i<16;i++)m[i]=T[i];
	
}

void mLoadRotation(float* m,float angle, float x, float y, float z){
	
	v3f u = {x,y,z};
	v3fNormalize(&u);
	x = u.x; y = u.y; z = u.z;
	
	float rad = degreesToRadians(angle);
	
	float cos  = cosf(rad);
	float cosp = 1.0f - cos;
	float sin  = sinf(rad);
		
	float T[16] = {
		
		cos + cosp * (x*x),
		cosp * x*y + z * sin,
		cosp * x*z - y * sin,
		0.0f,
		
		cosp * x*y - z * sin,
		cos + cosp * (y*y),
		cosp * y*z + x * sin,
		0.0f,
		
		cosp * x*z + y * sin,
		cosp * y*z - x * sin,
		cos + cosp * (z*z),
		0.0f,
		
		0.0f,
		0.0f,
		0.0f,
		1.0f
	};
	
	for(int i=0;i<16;i++)m[i]=T[i];
	
}

void mLoadPerspective(float* m,
					  float fovYInDegrees,
					  float aspect,
					  float nearZ,
					  float farZ){
	
	float fovYInRadians = degreesToRadians(fovYInDegrees);
	
	float cotan = 1.0f / tanf(fovYInRadians / 2.0f);
		
	float T[16] =
	{
		cotan/aspect, 0.0f, 0.0f, 0.0f,
		0.0f, cotan, 0.0f, 0.0f,
		0.0f, 0.0f, (farZ + nearZ) / (nearZ - farZ), -1.0f,
		0.0f, 0.0f, (2.0f * farZ * nearZ) / (nearZ - farZ), 0.0f
	};
		
	for(int i=0;i<16;i++)m[i]=T[i];

}

void mTranslatef(float* m,float x,float y,float z){
	
	float T[16];
	mLoadTranslation(T, x, y, z);
	mMultMatrixf(m, T);
	
}

void mScalef(float* m,float x,float y,float z){
	
	float T[16];
	mLoadScale(T, x, y, z);
	mMultMatrixf(m, T);
	
}

void mRotatef(float* m,float angleDeg,float x,float y,float z){
	
	float T[16];
	mLoadRotation(T, angleDeg, x, y, z);
	mMultMatrixf(m, T);
	
}

void mRotateXf(float* m,const float angleDeg){
	
	float T[16];
	mLoadRotationX(T,angleDeg);
	mMultMatrixf(m, T);
	
}

void mRotateYf(float* m,const float angleDeg){
	
	float T[16];
	mLoadRotationY(T, angleDeg);
	mMultMatrixf(m, T);
	
}

void mMultVector4(float* u, const float* m){
	
	v4f v = {
		m[0]*u[0] +  m[4]*u[1] + m[8]*u[2] + m[12] * u[3],
		m[1]*u[0] +  m[5]*u[1] + m[9]*u[2] + m[13] * u[3],
		m[2]*u[0] +  m[6]*u[1] + m[10]*u[2] + m[14] * u[3],
		m[3]*u[0] +  m[7]*u[1] + m[11]*u[2] + m[15] * u[3] };
	
    u[0]=v.x;
    u[1]=v.y;
    u[2]=v.z;
    u[3]=v.w;
	
}

void mRotateZf(float* m,const float angleDeg){
	
	float T[16];
	mLoadRotationZ(T, angleDeg);
	mMultMatrixf(m, T);
	
}

v3f mBasisX(const float* m){
	v3f u = {m[0],m[1],m[2]};
	return u;
}

v3f mBasisY(const float* m){
	v3f u = {m[4],m[5],m[6]};
	return u;
}

v3f mBasisZ(const float* m){
	v3f u = {m[2],m[6],m[10]};
	return u;
}

void mCheckAgainstGLState(float* m){
	
	float glMatrix[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, glMatrix);
	
	char mismatch=0;
	for(int i=0;i<16;i++){
		
		if(m[i]!=glMatrix[i]){
			printf("m[%i] does not match gl state: %.2f instead of %.2f\n",
				   i,m[i],glMatrix[i]);
			mismatch=1;
		}
		
	}
	
	if(mismatch){
		printf("matrix mismatch");
	}
}