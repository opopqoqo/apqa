
#ifndef math_math4f_h
#define math_math4f_h

// ___________________________________________________

#import "matrix.h"
#import <stdbool.h>

/**
 * Basic 4x4 matrix math
 */

#pragma mark creating matrices -----------------------

m4f m4fMakeIdentity();

m4f m4fMakeInverse(const m4f* ofMatrix);

m4f m4fMakeInverseMESA(const m4f* ofMatrix);

m4f m4fMakePerspectiveDeg(float fovYInDegrees,
						  float aspect,
						  float zNear,
						  float zFar);

m4f m4fMakePerspectiveRad(float fovYInRad,
						  float aspect,
						  float zNear,
						  float zFar);

m4f m4fMakeProduct(const m4f* a,const m4f* b);

m4f m4fMakeRotationDeg(float a,
					   float x,float y,float z);

m4f m4fMakeRotationRad(float a,
					   float x,float y,float z);

m4f m4fMakeScale(float x,float y,float z);

m4f m4fMakeTranslation(float x,float y,float z);

m4f m4fMakeTranspose(const m4f* ofMatrix);

#pragma mark getting information ---------------------

bool m4fIsIdentity(const m4f* m);
bool m4fIsIdentityWithTolerance(const m4f* m,float t);
bool m4fIsEqual(const m4f* a,const m4f* b);
bool m4fIsEqualWithTolerance(const m4f* a,const m4f* b,float t);

#pragma mark transformations -------------------------

void m4fMultiply(m4f* m,const m4f* n);

void m4fInvert(m4f* m);

void m4fTranslate(m4f* mat,
				  float x,float y,float z);

void m4fScale(m4f* mat,
			  float x,float y,float z);

void m4fRotateDeg(m4f* mat,
			   float a,
			   float x, float y, float z);

void m4fRotateXDeg(m4f* mat, float angle );

void m4fRotateYDeg(m4f* mat, float angle );

void m4fRotateZDeg(m4f* mat, float angle );

void m4fRotateRad(m4f* mat,
				  float a,
				  float x, float y, float z);

#pragma mark transform vectors and vertices ----------

void m4fTransformVertex3f(const m4f* mat,v3f* P);

void m4fTransformVector3f(const m4f* mat,v3f* u);

void m4fProjectVertex3f(const m4f* mat,v3f* u);

/* @deprecated */
void m4fMultiplyV3f(const m4f* mat, v3f* p);

/* @deprecated */
void m4fMultiplyV3fWithTranslation(const m4f* mat, v3f* p);

/* @deprecated */
void m4fMultiplyAndProjectV3f(const m4f* mat, v3f* p);

#pragma mark other operations ------------------------

void m4fTranspose(m4f* mat);

m3f m4fToM3f(const m4f* m);

m4f m4fDuplicate(const float* val);

#pragma mark end -------------------------------------

#endif
