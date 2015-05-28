
#import "vec.h"
#import "xmath.h"
#import <stdbool.h>

#pragma mark constructors ----------------------------

v2f makeVector2f(float x,float y){

	v2f p = {x,y};
	return p;
	
}

v2f makeVector3f(float x,float y,float z){
	
	v2f p = {x,y};
	return p;
	
}

void makeZeroVector(float* u,
					char D){
	
	for(int i=0;i<D;i++){
	
		u[i] = 0;

	}return;
	
}

void makeRandomVector(float* u,
					  char D){
		
	while(true){
		
		for(int i=0;i<D;i++){
			u[i] = randomSignedFloat();
		}
		
		float lsq = vectorLengthSquared(u, D);
		
		if(lsq<1.0f){
			return;
		}
	}
	
}

float vectorLengthSquared(const float* u,char D){
	
	float l = 0;
	
	for(int i=0;i<D;i++){
		l+=u[i]*u[i];
	}
	
	return l;
	
}