// Copyright T.E.A de Souza 2012-2015 - MIT LICENSE

#import "vecmathf.h"
#import <stdlib.h>
#import <math.h>
#import "xmath.h"

#define forall(x) for(int x=0;x<size;x++)

#pragma mark constructors ----------------------------

void vfMake(const float* A,
			const float* B,
			float* result,
			dimension size){

	forall(i) result[i]=B[i]-A[i];
	
}

float* vfNew(dimension size){

	float* value=malloc(size*sizeof(float));
	
	forall(i)value[i]=0.0f;
	
	return value;
	
}

#pragma mark getting information ---------------------

float vfDistance(const float* A,const float* B,
				 dimension size){

	float d2 = vfDistanceSquared(A, B, size);
	
	if(d2==0){
		return 0;
	}
	
	return sqrt(d2);
	
}

float vfLength(const float* u,
					  dimension size){
	
	float d2 = vfLengthSquared(u, size);
	
	return sqrt(d2);
	
}

float vfDistanceSquared(const float* A,
						const float* B,
						dimension size){
	
	float sum = 0.0f; forall(i){
		
		float x = B[i]-A[i];
		sum += x*x;
		
	}return sum;
	
}

float vfLengthSquared(const float* u,
					  dimension size){
	
	float l = 0; forall(i){
		l+=u[i]*u[i];
	}
	
	return l;
	
}

#pragma mark operations ------------------------------

void vfNormalize(float* u,
				  dimension size){

	float s = 1.0f/vfLength(u, size);
	
	vfScale(u,s,size);
	
}

void vfScale(float* u,
			  float factor,
			  dimension size){

	forall(i) u[i]*=factor;
	
}

void vfOffset(float* u,
			  float factor,
			  dimension size){
	
	forall(i) u[i]+=factor;
	
}

void vfAdd(float* u,
		   const float* v,
		   dimension size){

	forall(i) u[i]+=v[i];
	
}

void vfSub(float* u,
		   const float* v,
		   dimension size){
	
	forall(i) u[i]-=v[i];
	
}

void vfMul(float* u,
		   const float* v,
		   dimension size){
	
	forall(i) u[i]*=v[i];
	
}

void vfDiv(float* u,
		   const float* v,
		   dimension size){
	
	forall(i) u[i]/=v[i];
	
}

void vfsmoothstep(const float* e0,
				  const float* e1,
				  float x,
				  float *dst,
				  dimension size){
	
	forall(i) dst[i] = smoothstep(e0[i], e1[i], x);
	
}
