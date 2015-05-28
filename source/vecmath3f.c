
#import "math.h"
#import "vecmath2f.h"
#import "vecmath3f.h"
#import "xmath.h"
#import <stdio.h>
#import <assert.h>

// factory methods ----------------------------------------------

/**
 * Decompose u into u0,u1 so that:
 * u0 = k * v
 * u = u0+u1
 * u1 is normal to u0
 */
void decomposeOrtho(vector3f u,vector3f v,
						vector3f* u0,vector3f* u1){

	float normOfU0=v3fProjectOrtho(&u, &v);
	v3fSet(u0, v);
	v3fSetLength(u0, normOfU0);
	
	v3fSet(u1,u);
	v3fSub(u1,u0);
	
}

bool v3fIsUnit(const vector3f* u){

	if(u->x!=1)return false;
	if(u->y!=1)return false;
	if(u->z!=1)return false;
	return true;
	
}

/*
vector3f v3fYPRDeg(const vector3f* u){
	
	vector3f ypr = v3fYPRrad(u);
	v3fToDegrees(&ypr);
	
	return ypr;
	
}
 */

float v3fPitchDeg(const vector3f* u){
	return radiansToDegrees(v3fPitchRad(u));
}

float v3fYawDeg(const vector3f* u){
	return radiansToDegrees(v3fYawRad(u));
}

float v3fPitchRad(const vector3f* u){
	float l=v3fLength(u);
	float b=v3fZXLength(u);
	return acos(l/b);
}

float v3fYawRad(const vector3f* u){
	float l=v3fLength(u);
	float b=v3fXYLength(u);
	return acos(l/b);
}

bool _v3fIsAlmostUnit(float x){
	int y = (int) (x * 100000);
	return y == 100000;
}

bool v3fIsAlmostUnit(const vector3f* u){
	
	if(!_v3fIsAlmostUnit(u->x))return false;
	if(!_v3fIsAlmostUnit(u->y))return false;
	if(!_v3fIsAlmostUnit(u->z))return false;
	return true;
	
}

/**
 * Orthographically Project P on a line defined by A and u.
 */
vector3f v3fProjectPointOnLine(const vector3f* P,
							const vector3f* A,
							const vector3f* u){
    
    vector3f v=v3fMake(A,P);
    float x=v3fProjectOrtho(&v, u);
    vector3f w=v3fDuplicate(*u);
    v3fSetLength(&w,x);
    v3fAdd(&w, A);
    
    return w;
}

/** 
 * Orthographically project u onto v
 * and return the signed norm of the resulting vector.
 * If you want the resulting vector itself just duplicate
 * v and call v3fSetLength(w,n)
 * where 'n' is the signed norm.
 * Starting from the same point this tells us 'how far we moved along v' when 
 * moving along u; using the signed norm also tells us if we're going in the
 * opposite or same direction, so it feels useful.
 * 
 * I think this is a good start for decomposing a vector in a different base.
 * Anyway I wrote that while working on the walking algorithms. For one thing
 * this makes it easy to project a point on a line.
 *
 * For one thing this can be used to project a point on a line, telling
 * us how far the point lies from the line.
 */
float v3fProjectOrtho(const vector3f* u,const vector3f* v){
    
	float l=v3fLength(v);
	float dot=v3fDot(u,v);
    float norm=dot/l;
    return norm;
    
}

vector3f* arrayAsV3f(float* float_x3){
	return (vector3f*)float_x3;
}

float* v3fAsArray(vector3f* u){
	return (float*)u;
}

vector3f v3fDuplicate(vector3f u){
	vector3f v={u.x,u.y,u.z};
	return v;
}

vector3f v3fMakeByOffset(const vector3f* P, const vector3f* u){
	vector3f P1={
		P->x+u->x,
		P->y+u->y,
		P->z+u->z
	};
	return P1;
}

vector3f v3fMake(const vector3f* a, const vector3f* b){
	
	vector3f u={
		b->x - a->x,
		b->y - a->y,
		b->z - a->z
	};
	
	return u;
	
}

vector3f v3fMidpoint(const vector3f* a, const vector3f* b){
	vector3f u={
		(b->x+a->x)*0.5f,
		(b->y+a->y)*0.5f,
		(b->z+a->z)*0.5f
	};
	return u;
}

vector3f v3fNormal(const vector3f* u,
				   const vector3f* v){
	
	vector3f w=v3fCross(u, v);
	v3fNormalize(&w);
	return w;
	
}

vector3f v3fNaN(){
	vector3f u={NAN,NAN,NAN};
	return u;
}

// arithmetics ---------------------------------------

void v3fMul(vector3f* u,float s){
	u->x=(u->x)*s;
	u->y=(u->y)*s;
	u->z=(u->z)*s;
}

void v3fAdd(vector3f* u,const vector3f* v){
	u->x+=v->x;
	u->y+=v->y;
	u->z+=v->z;
}

void v3fSub(vector3f* u,const vector3f* v){
	u->x-=v->x;
	u->y-=v->y;
	u->z-=v->z;
}

void v3fNeg(vector3f* u){
	u->x=-u->x;
	u->y=-u->y;
	u->z=-u->z;
}

char v3fEquals(const vector3f* u,
			   const vector3f* v){
	
	if(u->x!=v->x)return false;
	if(u->y!=v->y)return false;
	if(u->z!=v->z)return false;
	return true;
	
}

bool v3fIsNaN(const vector3f* u){
	
	if(isnan(u->x))return true;
	if(isnan(u->y))return true;
	if(isnan(u->z))return true;
	return  false;
	
}

bool v3fIsInf(const vector3f* u){
	if(isinf(u->x))return true;
	if(isinf(u->y))return true;
	if(isinf(u->z))return true;
	return  false;
}

bool v3fIsDegenerate(const vector3f* u){
	
	if(v3fIsNaN(u))return true;
	if(v3fIsInf(u))return true;
	return  false;
	
}

void v3fSet(vector3f* dst,vector3f src){
	dst->x=src.x;
	dst->y=src.y;
	dst->z=src.z;
}

void v3fZero(vector3f* u){
	u->x=0;
	u->y=0;
	u->z=0;
}

float v3fOrientationRad(vector3f* u){
	return angleRad(u->x,u->z);
}

float v3fOrientationDeg(vector3f* u){
	return angleDeg(u->x, u->z);
}

void v3fFreeFall(vector3f* P,vector3f* u,float R,float G,float t){
	P->x+=u->x*t;
	P->y+=u->y*t;
	P->z+=u->z*t;
	v3fFreeFallSpeed(u, R, G, t);
}

void v3fFreeFallSpeed(vector3f* u,float R,float G,float t){
	u->x -=   R*u->x       * t;
	u->y -= ( R*u->y + G ) * t;
	u->z -=   R*u->z*t;	
}

bool v3fIsNormalizable(vector3f u){
	float l=v3fLength(&u);
	float a=u.x/l;
	if(isnan(a))return 0;
	a=u.y/l;
	if(isnan(a))return 0;
	a=u.z/l;
	if(isnan(a))return 0;
	return 1;
}

void v3fSetLength(vector3f* dst,float l){

	v3fNormalize(dst);
	v3fMul(dst,l);

}

// geometry ----------------------------------------

void v3fTranslate(vector3f* u,float x,float y,float z){
	u->x+=x;
	u->y+=y;
	u->z+=z;
}

void v3fRotateDeg(vector3f* u,float x,float y,float z){
    v3fRotateDegX(u,x);
    v3fRotateDegY(u,y);
    v3fRotateDegZ(u,z);
}

void v3fRotateRad(vector3f* u,float x,float y,float z){
    v3fRotateRadX(u,x);
    v3fRotateRadY(u,y);
    v3fRotateRadZ(u,z);
}

void v3fScale(vector3f* u,float x,float y,float z){
    u->x*=x;
    u->y*=y;
    u->z*=z;
}

void v3fUntranslate(vector3f* u,float x,float y,float z){
	u->x-=x;
	u->y-=y;
	u->z-=z;
}

void v3fUnrotateDeg(vector3f* u,float x,float y,float z){
    v3fRotateDegZ(u,x);
    v3fRotateDegY(u,y);
    v3fRotateDegX(u,z);
}

void v3fUnrotateRad(vector3f* u,float x,float y,float z){
    v3fRotateRadZ(u,z);
    v3fRotateRadY(u,y);
    v3fRotateRadX(u,x);
}

void v3fUnscale(vector3f* u,float x,float y,float z){
    u->x/=x;
    u->y/=y;
    u->z/=z;
}

void v3fRotateDegX(vector3f* u,float angle){

    float rad=angle/180.0f*M_PI; 
    float cosrad=cos(rad);
    float sinrad=sin(rad);
 
    float z = cosrad*u->z - sinrad*u->y;
    float y = sinrad*u->z + cosrad*u->y;
    
    u->z = z;
    u->y = y;
    
}
 
void v3fRotateDegY(vector3f* u,float angle){
 
 float rad=angle*M_PI/180.0f;
 
 float cosrad=cos(rad);
 float sinrad=sin(rad);
 
 float x = cosrad*u->x - sinrad*u->z;
 float z = sinrad*u->x + cosrad*u->z;
 
 u->x = x;
 u->z = z;

}

void v3fRotateDegZ(vector3f* u,float angle){
    
    float rad=angle*M_PI/180.0f;
    float cosrad=cos(rad);
    float sinrad=sin(rad);
 
    float x = cosrad*u->x - sinrad*u->y;
    float y = sinrad*u->x + cosrad*u->y;

    u->x = x;
    u->y = y;
    
}

void v3fRotateRadX(vector3f* u,float rad){

    float cosrad=cos(rad);
    float sinrad=sin(rad);
    
    float z = cosrad*u->z - sinrad*u->y;
    float y = sinrad*u->z + cosrad*u->y;
    
    u->z = z;
    u->y = y;
    
}

void v3fRotateRadY(vector3f* u,float rad){

    float cosrad=cos(rad);
    float sinrad=sin(rad);
    
    float x = cosrad*u->x - sinrad*u->z;
    float z = sinrad*u->x + cosrad*u->z;
    
    u->x = x;
    u->z = z;
    
}

void v3fRotateRadZ(vector3f* u,float rad){
 
    float cosrad=cos(rad);
    float sinrad=sin(rad);
    
    float x = cosrad*u->x - sinrad*u->y;
    float y = sinrad*u->x + cosrad*u->y;
    
    u->x = x;
    u->y = y;
    
}

void v3fToRadians(vector3f* u){

	u->x = degreesToRadians(u->x);
	u->y = degreesToRadians(u->y);
	u->z = degreesToRadians(u->z);
	
}

void v3fToDegrees(vector3f* u){
	
	u->x = radiansToDegrees(u->x);
	u->y = radiansToDegrees(u->y);
	u->z = radiansToDegrees(u->z);
	
}

void v3fNormalize(vector3f* u){
	float l=v3fLength(u);
	u->x/=l;
	u->y/=l;
	u->z/=l;
}

float v3fMaxComponentNorm(const vector3f* u){
	float m = fabs(u->x);
	m = fmaxf(m,fabs(u->y));
	m = fmaxf(m,fabs(u->z));
	return m;
}

float v3fDot(const vector3f* a,const vector3f* b){
	return	a->x*b->x + a->y*b->y + a->z*b->z;
}

void v3fSetNaN(vector3f* u){

	u->x = NAN;
	u->y = NAN;
	u->z = NAN;
	
}

void v3fSetXYZ(vector3f* u,float x,float y,float z){
	u->x=x;
	u->y=y;
	u->z=z;
}

void v3fMinimize(vector3f* u,const vector3f* v){
	u->x = xmin(u->x, v->x);
	u->y = xmin(u->y, v->y);
	u->z = xmin(u->z, v->z);
}

void v3fMaximize(vector3f* u,const vector3f* v){
	u->x = xmax(u->x, v->x);
	u->y = xmax(u->y, v->y);
	u->z = xmax(u->z, v->z);
}

vector3f v3fLerp(const vector3f* u,
				 const vector3f* v, float t){

	//return this.plus(a.minus(this).times(t));
	v3f w={
		u->x + (v->x - u->x)*t,
		u->y + (v->y - u->y)*t,
		u->z + (v->z - u->z)*t
	};
	
	return w;
	
}

float v3fDistanceSquared(const vector3f* a,const vector3f* b){
	float x=b->x-a->x;
	float y=b->y-a->y;
	float z=b->z-a->z;
	return x*x+y*y+z*z;
}
float v3fXZDistanceSquared(const vector3f* a,const vector3f* b){
	float x=b->x-a->x;
	float z=b->z-a->z;
	return x*x+z*z;
}

bool v3fIsZero(const vector3f* u){
	if(u->x!=0)return 0;
	if(u->y!=0)return 0;
	if(u->z!=0)return 0;
	return 1;
}

float v3fDistance(const vector3f* a,const vector3f* b){
	return sqrt(v3fDistanceSquared(a,b));
}

/* @deprecated */
float v3fDistance2(vector3f a,vector3f b){
	return sqrt(v3fDistanceSquared(&a,&b));
}

float v3fXZDistance(vector3f* a,vector3f* b){
	return sqrt(v3fXZDistanceSquared(a,b));
}

float v3fLength(const vector3f* u){
	return sqrt( u->x*u->x + u->y*u->y + u->z*u->z);
}

float v3fXYLength(const vector3f* u){
	return sqrt( u->x*u->x + u->y*u->y );
}

float v3fYZLength(const vector3f* u){
	return sqrt( u->y*u->y + u->z*u->z);
}

float v3fZXLength(const vector3f* u){
	return sqrt( u->z*u->z + u->x*u->x );
}

float v3fPlanarLength(vector3f* u){
	return sqrt( u->x*u->x + u->z*u->z);
}

float v3fAngleRad(const vector3f* a,const vector3f* b){
	float la=v3fLength(a);
	float lb=v3fLength(b);
	float dot=v3fDot(a,b);
	float cos=dot/(la*lb);
	double val=acos(cos);
	return (float)val;
}

float v3fAngleDeg(const vector3f* a,const vector3f* b){
	return v3fAngleRad(a,b)*(180.0f/M_PI);
}

vector3f v3fInterpolate(vector3f src,vector3f dst,float pos){
	vector3f w;
    float k=1-pos;
	w.x=src.x*k + dst.x*pos;
	w.y=src.y*k + dst.y*pos;
	w.z=src.z*k + dst.z*pos;
    return w;
}

/*yu*zv - yv*zu , zu*xv - zv*xu , xu*yv - xV*yu*/
vector3f v3fCross(const vector3f* u,const vector3f* v){

	vector3f w={
		u->y * v->z - v->y * u->z,
		u->z * v->x - v->z * u->x,
		u->x * v->y - v->x * u->y
	};
	
	return w;
	
}

float v3fMax(const vector3f* u){

	float n = fabs(u->x);
	n = fmaxf(n,fabs(u->y));
	n = fmaxf(n,fabs(u->z));
	//
	return n;
	
}

float v3fMin(const vector3f* u){

	float n = fabs(u->x);
	n = fminf(n,fabs(u->y));
	n = fminf(n,fabs(u->z));
	//
	return n;
	
}

vector3f v3fAdjustDirection(vector3f* currentDirection,
						 vector3f* desiredDirection,
						 float maxRadsPerMillisecond,int ms){
	
	float currentRotation=angleRad(currentDirection->x, currentDirection->z);
	float desiredRotation=angleRad(desiredDirection->x, desiredDirection->z);

	// if current/desired direction is near zero, no rotation can be inferred.
	// fail gracefully.
	
	if(isnan(currentRotation)){
		vector3f result={0,0,0};
		v3fSet(&result, *desiredDirection);
		return result;
	}
	if(isnan(desiredRotation)){
		vector3f result={0,0,0};
		return result;
	}
	
	// adjust the rotation and return the result.
	
	float nextRotation=adjustRotation(currentRotation, desiredRotation, 
									  maxRadsPerMillisecond, ms);
	
	vector3f result = {cos(nextRotation),desiredDirection->y,sin(nextRotation)};
	
	return result;
	
}

float v3fComponent(const vector3f* u,int i){

	assert(i>=0);
	assert(i<3);
	if(i==0)return u->x;
	else if(i==1)return u->y;
	else return u->z;
	
}

#pragma mark debugging -------------------------------

void v3fPrint(vector3f u){
	printf("< %.3f %.3f %.3f >",u.x,u.y,u.z);
}

void v3fAssertEquals(const vector3f* u,const vector3f* v){
	
	assert(u!=NULL);
	assert(v!=NULL);
	
	assert( u->x == v->x );
	assert( u->y == v->y );
	assert( u->z == v->z );
	
}

void v3fAssert(const vector3f* u){
	
	assert(isfinite(u->x));
	assert(isfinite(u->y));
	assert(isfinite(u->z));

}

/*
vector3f nearestPointOnSegment(vector3f P,segment3f s){
    
    vector3f A=s.A;
    vector3f B=s.B;
    vector3f u=v3fMake(&B,&A);
    vector3f Q=projectPointOnLine(&P, &A, &u);
    
    vector3f AQ=v3fMake(&A,&Q);
    vector3f BQ=v3fMake(&B,&Q);
    
    float wA=v3fDot(&u,&AQ);
    float wB=-v3fDot(&u,&BQ);
    
    if(wA>0){
        return s.A;
    }
    
    if(wB>0){
        return s.B;
    }
    
    return Q;
    
}
 */

// ANGLE MEASUREMENTS

/*
 float v3fSignedAngleRad(const vector3f* u,
 const vector3f* v,
 const vector3f* up){
 
 vector3f w = v3fCross(u, v);
 
 float j = v3fDot(up,&w);
 float k = v3fDot(u,v);
 
 return atan2(j, k);
 
 }
 */

/*
vector3f v3fAngle3fDeg(const vector3f* u,const vector3f* v){
	
	vector3f w = v3fAngle3fRad(u, v);
	v3fToDegrees(&w);	
	return w;
	
}

vector3f v3fAngle3fRad(const vector3f* u,const vector3f* v){
	
	vector3f u0 = v3fYPRrad(u);
	vector3f v0 = v3fYPRrad(v);
	
	vector3f w=v3fMake(&u0, &v0);
	
	while( w.y < -M_PI ) w.y += M_PI*2.0f; 
	while( w.y >  M_PI ) w.y -= M_PI*2.0f;
	
	while( w.x < -M_PI ) w.x += M_PI*2.0f; 
	while( w.x >  M_PI ) w.x -= M_PI*2.0f;
	
	return w;
	
}
*/

/**
 * This formula evaluates the deflection component when we already know the direction of the deflection
 * and the velocity of an incoming object.
 * The translation and deflection component are orthogonal; for example if a ball is bouncing on the ground, 
 * it's motion in the horizontal plane is unchanged, but
 * when colliding with the ground it is deflected along the vertical axis.
 *
 * Here, v is the velocity and u is the direction of the deflection.
 * We consider a triangle ABC such that:
 * AB = v
 * BC = u
 * Given the rule of squares (a2 + b2 = c2), we can evaluate a parameter k
 * such that BC = k*u
 *
 * Note: given the deflection vector:
 * - the translation vector is translation = v + deflection
 * so that:
 * - resulting velocity is 2*deflection+v if the collider is not affected by the collision.
 *
 */
/*
 vector3f evalDeflection(vector3f* v,vector3f* u){
 
 if(v3fIsZero(u)){
 vector3f def={0,0,0};
 return def;
 }
 
 if(v3fIsZero(v)){
 vector3f def={0,0,0};
 return def;
 }
 
 float a = u->x*u->x + u->y*u->y + u->z*u->z;
 float b = u->x*v->x + u->y*v->y + u->z*v->z;
 
 float k = -b/a;
 
 vector3f deflection={k*u->x,k*u->y,k*u->z};
 
 return deflection;
 
 }
 */
