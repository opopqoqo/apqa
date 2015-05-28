// Copyright T.E.A de Souza 2012-2015 - MIT LICENSE

#ifndef math_vec_h
#define math_vec_h

// ___________________________________________________

#include <OpenGLES/ES1/gl.h>

#pragma mark common vector types ---------------------

typedef struct{
	
	GLfloat x,y;
	
}v2f;

typedef struct{
	
	GLfloat x,y,z;
	
}v3f;

typedef struct{
	
	GLfloat x,y,z,w;
	
}v4f;

typedef struct{
	
	v3f coord;
	v3f normal;
	
}v6f;

typedef struct{
	
	v3f coord;
	v3f normal;
	v2f uv;
	
}v8f;

// common vector arrays ------------------------------

typedef struct{
	
	v2f* data;
	int count;
	
}v2fv;

typedef struct{
	
	v3f* data;
	int count;
	
}v3fv;

typedef struct{
	
	v6f* data;
	int count;
	
}v6fv;

typedef struct{
	
	v6f* data;
	int count;
	
}v8fv;

#pragma mark functions -------------------------------

v2f makeVector2f(float x,float y);

v2f makeVector3f(float x,float y,float z);

void makeZeroVector(float* u, char D);

/**
 * Make a random vector constrained within a sphere of
 * radius 1.0
 */
void makeRandomVector(float* vector,char D);

float vectorLengthSquared(const float* u,char D);

// ___________________________________________________

#endif