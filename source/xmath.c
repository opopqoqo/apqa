
#import "xmath.h"
//
#import <stdlib.h>
#import <assert.h>
#import "math.h"

#define ARC4RANDOM_MAX      0x100000000

float xmax(float a,float b){
	if(isnan(a))return b;
	if(isnan(b))return a;
	return a>b?a:b;
}

float xmin(float a,float b){
	if(isnan(a))return b;
	if(isnan(b))return a;
	return a<b?a:b;
}

float radiansToDegrees(float a){
    return a*(180.0f/M_PI); 
}

float degreesToRadians(float a){
    return a*(M_PI/180.0f); 
}

float angularDistance(float a,float b){

	float d =(b-a);
	while(d>180){
		d-=360;
	}while(d<-180){
		d+=360;
	}
	
	return d;
	
}

float saturate(float x){
	
	if(x>1.0)return 1.0;
	if(x<0.0)return 0.0;
	return x;
	
}

float smoothstep(float edge0,float edge1,float x){
	
	assert(isfinite(x));
	
	//x = edge0+(edge1-edge0)*x;
	//return x;
	
	//x = saturate((x - edge0)/(edge1 - edge0));
	x = x*x*(3 - 2*x);
	
	return edge0+x*(edge1-edge0);
	
}

float screenRatio(float distance,float radius,float viewingAngle){

	float R=radius;
	float D=distance;
	float tan = R*2/D;
	float alpha = atanf(tan);
	float ratio = alpha/viewingAngle;
	return ratio;
	
}

float fract(float x){
	return x-floor(x);
}

int trueRandomInt(int max){
	return arc4random()%max;
}

float clamp(float x,float a,float b){
	assert(a<b);
	if(x<a)x=a;
	if(x>b)x=b;
	return x;
}

float displace(float x,float p,float f,float s){

	return x + cos(p*f)*s;
	
}

float angleDeg(float x,float y){
	float d=sqrt(x*x+y*y);
	float a=acos(x/d)*(180.0/M_PI);
	if(y>=0){
		return a;
	}else{
		return 360-a;
	}
}

float angleRad(float x,float y){
	float d=sqrt(x*x+y*y);
	float a=acos(x/d);
	if(y>=0){
		return a;
	}else{
		return (M_PI*2.0f)-a;
	}
}

float adjustRotation(float currentRotationRads,
					 float desiredRotationRads,
					 float maxRadsPerMs, 
					 int ms){

	float delta=desiredRotationRads-currentRotationRads;
	
	// if alpha is 350, prev is 10, then we don't rotate forward to 350, 
	// we should add 360 to prev and rotate back
	// if alpha is 10, prev is 350, then we don't rotate back to 10,
	// we should remove 360 from prev.
	
			if(delta>M_PI)	currentRotationRads	+=	M_PI*2.0f;
	else	if(delta<-M_PI)	currentRotationRads	-=	M_PI*2.0f;
	
	float resultingRotationRads;
	if(desiredRotationRads>currentRotationRads){
		resultingRotationRads=currentRotationRads+maxRadsPerMs*ms;
		if(resultingRotationRads>desiredRotationRads)resultingRotationRads=desiredRotationRads;
	}else{
		resultingRotationRads=currentRotationRads-maxRadsPerMs*ms;
		if(resultingRotationRads<desiredRotationRads)resultingRotationRads=desiredRotationRads;
	}

	return resultingRotationRads;
	
}

int nearestPOTAbove(float num){
	
	assert(num>=0);
	
	int pot; for(pot = 1; pot<num; pot<<=1);
	
	return pot;
	
}

int nearestPOT(float num){

	assert(num>=0);
	
	int pot1; for(pot1 = 1; pot1<num; pot1<<=1);
	
	int pot0 = pot1>>1;
	
	if( fabs(pot0-num) < fabs(pot1-num) ){
		return pot0;
	}else{
		return pot1;
	}
	
}

bool randomBit(float p){
	float val=((arc4random()*1.0)/ARC4RANDOM_MAX);
	return val<p;
}

float randomFloat(){
		
	float val=((arc4random()*1.0)/ARC4RANDOM_MAX);
	return val;
	
}

float randomSignedFloat(){
	float val=((arc4random()*1.0)/ARC4RANDOM_MAX)*2.0f-1.0f;
	return val;
}

float randomFloatInRange(float a,float b){
	return a + randomFloat()*(b-a);
}

int randomInt(int max){
	
	int val = arc4random()%max;
	assert(val<max);
	return val;
	
}