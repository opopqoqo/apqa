
#import "matmath4f.h"
//
#import "matmath4f_raw.h"
#import "invert_matrix4x4.h"
#import "vecmath3f.h"
#import "xmath.h"
#import <math.h>

m4f m4fMakeIdentity(){
	
	m4f m;
	mLoadIdentity((float*)&m);
	return m;
	
}

m4f m4fMakeInverse(const m4f* m){

	m4f out;
	
	inverseMatrix4x4(
					 (float*)m,
					 (float*)&out);
	
	return out;
	
}

m4f m4fMakeInverseMESA(const m4f* m){
	
	m4f out;
	
	inverseMatrix4x4_mesa((float*)m, (float*)&out);
	
	return out;
	
}

m4f m4fMakeTranspose(const m4f* m0){

	m4f m;
	mLoadMatrix((float*)&m, (float*)m0);
	mTranspose((float*)&m);
	
	return m;
	
}

m4f m4fMakeTranslation(float x,float y,float z){
	
	m4f m;
	mLoadTranslation((float*)&m, x, y, z);
	return m;
	
}

m4f m4fMakeScale(float x,float y,float z){
	
	m4f m;
	mLoadScale( (float*)&m, x, y, z );
	return m;
	
}

m4f m4fMakeRotationDeg(float a,float x,float y,float z){

	m4f m;
	mLoadRotation( (float*)&m, a, x, y, z );
	return m;
	
}

m4f m4fMakeRotationRad(float a,float x,float y,float z){
	
	m4f m;
	mLoadRotation( (float*)&m, radiansToDegrees(a), x, y, z);
	return m;
	
}

m4f m4fMakePerspectiveDeg( float fovYInDegrees,
						   float aspect,
						   float zNear,
						   float zFar){
	m4f m;
	mLoadPerspective((float*)&m,
					 fovYInDegrees,
					 aspect, zNear, zFar);
	return m;
}

m4f m4fMakePerspectiveRad( float fovYInRad,
						   float aspect,
						   float zNear,
						   float zFar){
	
	m4f m;
	mLoadPerspective((float*)&m,
					 radiansToDegrees(fovYInRad),
					 aspect, zNear, zFar);
	return m;
	
}

m4f m4fMakeProduct(const m4f* a,const m4f* b){

	m4f m = *a;
	m4fMultiply(&m, b);
	
	return m;
	
}

void m4fInvert(m4f* m){

	m4f m1 = m4fMakeInverse(m);
	*m = m1;
	
}

#pragma mark getting information ---------------------

bool m4fIsEqual(const m4f* a,const m4f* b){
	
	float* Ma = (float*)a;
	float* Mb = (float*)b;
	
	for(int i=0;i<16;i++){
	
		if(Ma[i]!=Mb[i])return false;
		
	}
	return true;
	
}

bool m4fIsEqualWithTolerance(const m4f* a,const m4f* b,float t){
	
	float* Ma = (float*)a;
	float* Mb = (float*)b;
	
	for(int i=0;i<16;i++){
		
		float d = fabs(Mb[i]-Ma[i]);
		if(d>t)return false;
		
	}
	return true;
	
}

bool m4fIsIdentity(const m4f* m){
	
	m4f k = m4fMakeIdentity();
	return m4fIsEqual(m, &k);
	
}

bool m4fIsIdentityWithTolerance(const m4f* m,float t){
	
	m4f k = m4fMakeIdentity();
	return m4fIsEqualWithTolerance(m, &k,t);
	
}

#pragma mark transformations -------------------------

void m4fMultiply(m4f* m,const m4f* n){

	mMultMatrixf((float*)m, (float*)n);
	
}

void m4fTranslate(m4f* mat,
				  float x,float y,float z){

	mTranslatef((float*)mat, x, y, z);
	
}

void m4fScale(m4f* mat,
			  float x,float y,float z){

	mScalef((float*)mat, x, y , z);
	
}

void m4fRotateDeg(m4f* mat,
			   float a,
			   float x, float y, float z){

	mRotatef((float*)mat, a, x, y, z);
	
}

void m4fRotateXDeg(m4f* mat, float a ){

	mRotatef((float*)mat, a, 1, 0, 0);
	
}

void m4fRotateYDeg(m4f* mat, float a ){

	mRotatef((float*)mat, a, 0, 1, 0);
	
}

void m4fRotateZDeg(m4f* mat, float a ){

	mRotatef((float*)mat, a, 0, 0, 1);
	
}

void m4fRotateRad(m4f* mat,
				  float rads,
				  float x, float y, float z){
	
	float degs = radiansToDegrees(rads);
	
	mRotatef((float*)mat, degs, x, y, z);
	
}

#pragma mark other operations ------------------------

void m4fTransformVertex3f(const m4f* mat,v3f* P){

	v4f vec = { P->x, P->y, P->z, 1.0f };
	mMultVector4f((float*)&vec, (float*)mat);
	
	P->x = vec.x;
	P->y = vec.y;
	P->z = vec.z;
	
}

void m4fTransformVector3f(const m4f* mat,v3f* u){

	v4f vec = { u->x, u->y, u->z, 0.0f };
	mMultVector4f((float*)&vec, (float*)mat);
	
	u->x = vec.x;
	u->y = vec.y;
	u->z = vec.z;
	
}

void m4fProjectVertex3f(const m4f* mat,v3f* P){

	v4f vec = { P->x, P->y, P->z, 1.0f };
	mMultVector4f((float*)&vec, (float*)mat);
	
	P->x = vec.x;
	P->y = vec.y;
	P->z = vec.z;
	
	v3fMul(P, 1.0/vec.w);

}

m4f m4fDuplicate(const float* val){

	m4f m;
	m = *((m4f*)val);
	return m;
	
}

void m4fTranspose(m4f* m){

	mTranspose((float*)m);
	
}

m3f m4fToM3f(const m4f* m){

	m3f m3 ={
	
		{m->x.x,m->x.y,m->x.z},
		{m->y.x,m->y.y,m->y.z},
		{m->z.x,m->z.y,m->z.z}
		
	};
	
	return m3;
	
}

void m4fMultiplyV3fWithTranslation(const m4f* mat, v3f* p){

	v4f vec = { p->x, p->y, p->z, 1.0f };
	mMultVector4f((float*)&vec, (float*)mat);
	
	p->x = vec.x;
	p->y = vec.y;
	p->z = vec.z;
	
}

void m4fMultiplyV3f(const m4f* mat, v3f* p){
	
	v4f vec = { p->x, p->y, p->z, 0.0f };
	mMultVector4f((float*)&vec, (float*)mat);
	
	p->x = vec.x;
	p->y = vec.y;
	p->z = vec.z;
	
}

void m4fMultiplyAndProjectV3f(const m4f* mat, v3f* p){

	v4f vec = { p->x, p->y, p->z, 1.0f };
	mMultVector4f((float*)&vec, (float*)mat);
	
	p->x = vec.x;
	p->y = vec.y;
	p->z = vec.z;
	
	v3fMul(p, 1.0/vec.w);
	
}

#pragma mark end -------------------------------------
