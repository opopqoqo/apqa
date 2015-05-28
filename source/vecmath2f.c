
#import "math.h"
#import "xmath.h"
#import "vecmath2f.h"
#import <assert.h>

#pragma mark factory methods

v2f v2fMakeByOffset(v2f* P, v2f* u){
	v2f P1={
		P->x+u->x,
		P->y+u->y,
	};
	return P1;
}

v2f v2fMake(const v2f* a, const v2f* b){
	v2f u={
		b->x-a->x,
		b->y-a->y,
	};
	return u;
}

v2f v2fMidpoint(v2f* a, v2f* b){
	
	v2f u={
		(b->x+a->x)*0.5f,
		(b->y+a->y)*0.5f,
	};
	return u;
	
}

void v2fDisplace(v2f* u,float f,float s){
	
	v2f v = {
		displace(u->x, u->y, f, s),
		displace(u->y, u->x, f, s)
	};
	
	u->x = v.x;
	u->y = v.y;
	
}

v2f v2fFromAngleDeg(float angle){

	float rad = degreesToRadians(angle);
	v2f u = {
			cos(rad),
			sin(rad)
	};
	return u;
}

#pragma mark arithmetics

void v2fMul(v2f* u,float s){
	u->x=(u->x)*s;
	u->y=(u->y)*s;
}

void v2fAdd(v2f* u,const v2f* v){
	u->x+=v->x;
	u->y+=v->y;
}

void v2fSub(v2f* u,const v2f* v){
	u->x-=v->x;
	u->y-=v->y;
}

void v2fFract(v2f* u){
	
	u->x=u->x - floor(u->x);
	u->y=u->y - floor(u->y);
	
}

void v2fNeg(v2f* u){
	u->x=-u->x;
	u->y=-u->y;
}

char v2fEquals(v2f u,v2f v){
	if(u.x!=v.x)return 0;
	if(u.y!=v.y)return 0;
	return 1;
}

void v2fSet(v2f* dst,const v2f* src){
	dst->x=src->x;
	dst->y=src->y;
}

void v2fZero(v2f* u){
	u->x=0;
	u->y=0;
}

void v2fFreeFall(v2f* P,v2f* u,float R,float G,float t){
	P->x+=u->x*t;
	P->y+=u->y*t;
	v2fFreeFallSpeed(u, R, G, t);
}

void v2fFreeFallSpeed(v2f* u,float R,float G,float t){
	u->x -=   R*u->x      * t;
	u->y -= ( R*u->y + G) * t ;
}

char v2fIsNormalizable(v2f* u){
	float l=v2fLength(u);
	float a=u->x/l;
	if(isnan(a))return 0;
	a=u->y/l;
	if(isnan(a))return 0;
	return 1;
}

void v2fSetLength(v2f* dst,float l){
	
	v2fNormalize(dst);
	v2fMul(dst,l);
	
}

#pragma mark operations

void v2fTranslate(v2f* u,float x,float y){
	u->x+=x;
	u->y+=y;
}


void v2fNormalize(v2f* u){
	float l=v2fLength(u);
	u->x/=l;
	u->y/=l;
}

float v2fDot(const v2f* a,const v2f* b){
	return	a->x*b->x + a->y*b->y;
}

float v2fDistanceSquared(const v2f* a,const v2f* b){
	float x=b->x-a->x;
	float y=b->y-a->y;
	return x*x+y*y;
}

char v2fIsZero(v2f* u){
	if(u->x!=0)return 0;
	if(u->y!=0)return 0;
	return 1;
}

float v2fDistance(const v2f* a,const v2f* b){
	return sqrt(v2fDistanceSquared(a,b));
}

float v2fLength(const v2f* u){
	return sqrt( u->x*u->x + u->y*u->y );
}

float v2fAngleRad(const v2f* a,const v2f* b){
	
	float la=v2fLength(a);
	float lb=v2fLength(b);
	float dot=v2fDot(a,b);
	float cos=dot/(la*lb);
	double val=acos(cos);
	return (float)val;
	
}

float v2fSignedAngleDegCCW(const v2f* u,const v2f* v){

	return radiansToDegrees(v2fSignedAngleRadCCW(u, v));
	
}

float v2fSignedAngleRadCCW2(const v2f* u,const v2f* v){
	
	return 0.0f;
	
}

float v2fSignedAngleRadCCW(const v2f* u,const v2f* v){
	
	float alpha = v2fAngleRadRelativeToXAxis(u);
	float beta  = v2fAngleRadRelativeToXAxis(v);
	
	float angle = beta-alpha;
	while( angle < -M_PI )angle += 2*M_PI;
	while( angle >  M_PI )angle -= 2*M_PI;	
	
	return angle;
	
}

float v2fAngleRadRelativeToXAxis(const v2f* u){
	
	float l = v2fLength(u);
	assert(l>0.99f);
	assert(l<1.01f);
	
	float angle = acos(u->x);
	
	return  ( u->y > 0 ) ? angle : -angle;
	
}

float v2fAngleDeg(const v2f* a,const v2f* b){
	return v2fAngleRad(a,b)*180.0f/M_PI;
}

void v2fRotateRad(v2f* u,float alpha){
    
    float cosAlpha=cos(alpha);
    float sinAlpha=sin(alpha);
    
    float x=u->x*cosAlpha-u->y*sinAlpha;
    float y=u->y*cosAlpha+u->x*sinAlpha;
    
    u->x=x;
    u->y=y;
    
}

void v2fRotateDeg(v2f* u,float alpha){
    v2fRotateRad(u,alpha/180.0f*M_PI);
}

void v2fInterpolate(v2f* p,v2f* a,v2f* b,float pos){
	float k=1-pos;
	p->x=a->x*k + b->x*pos;
	p->y=a->y*k + b->y*pos;
}
