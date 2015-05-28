
#import <stdbool.h>

#ifndef math_vecmath3f_h
#define math_vecmath3f_h

#ifndef vector3f
#define vector3f v3f
#endif

#pragma mark factory methods -------------------------

vector3f v3fMake(const vector3f* a, const vector3f* b);
vector3f v3fMidpoint(const vector3f* a,const vector3f* b);
vector3f v3fNormal(const vector3f* u,const vector3f* v);
vector3f v3fMakeByOffset(const vector3f* P, const vector3f* u);
vector3f v3fDuplicate(vector3f u);
vector3f v3fInterpolate(vector3f src,vector3f dst,float pos);
vector3f v3fCross(const vector3f* u,const vector3f* v);
vector3f v3fNaN();

void v3fSetNaN(vector3f* u);
void v3fSetXYZ(vector3f* u,float x,float y,float z);

#pragma mark type conversions

float* v3fAsArray(vector3f* u);
vector3f* arrayAsV3f(float* float_x3);

#pragma mark arithmetics

void v3fMul(vector3f* u,float s);
void v3fAdd(vector3f* u,const vector3f* v);
void v3fSub(vector3f* u,const vector3f* v);
void v3fSet(vector3f* dst,const vector3f src);
void v3fSetLength(vector3f* dst,float l);
void v3fZero(vector3f* u);
void v3fNeg(vector3f* u);
void v3fMinimize(vector3f* u,const vector3f* v);
void v3fMaximize(vector3f* u,const vector3f* v);
vector3f v3fLerp(const vector3f* u,
				 const vector3f* v, float t);

#pragma mark measurements

bool v3fIsNormalizable(const vector3f u);
bool v3fIsZero(const vector3f* u);
bool v3fIsNaN(const vector3f* u);
bool v3fIsInf(const vector3f* u);
bool v3fIsDegenerate(const vector3f* u);

float v3fDistance(const vector3f* a,const vector3f* b);
float v3fXZDistance(vector3f* a,vector3f* b);
float v3fDistance2(vector3f a,vector3f b);
float v3fDistanceSquared(const vector3f* a,const vector3f* b);
float v3fXZDistanceSquared(const vector3f* a,const vector3f* b);
float v3fDot(const vector3f* a,const vector3f* b);
char v3fEquals(const vector3f* u,const vector3f* v);
float v3fLength(const vector3f* u);
float v3fXYLength(const vector3f* u);
float v3fYZLength(const vector3f* u);
float v3fZXLength(const vector3f* u);
float v3fPlanarLength(vector3f* u);
bool v3fIsUnit(const vector3f* u);
bool v3fIsAlmostUnit(const vector3f* u);
float v3fMaxComponentNorm(const vector3f* u);
float v3fMax(const vector3f* u);
float v3fMin(const vector3f* u);

#pragma mark angles

void v3fToRadians(vector3f* u);
void v3fToDegrees(vector3f* u);

float v3fPitchDeg(const vector3f* u);
float v3fPitchRad(const vector3f* u);
float v3fYawDeg(const vector3f* u);
float v3fYawRad(const vector3f* u);

/**
 * return the unsigned angle (u,v).
 * range: [0,M_PI]
 * @test - range boundaries are untested.
 */
float v3fAngleRad(const vector3f* a,const vector3f* b);

/**
 * return the unsigned angle (u,v).
 * range: [0,180]
 * @test - range boundaries are untested.
 */
float v3fAngleDeg(const vector3f* a,const vector3f* b);

float v3fOrientationRad(vector3f* u);
float v3fOrientationDeg(vector3f* u);

#pragma mark geometry

void v3fTranslate(vector3f* u,float x,float y,float z);
void v3fScale(vector3f* u,float x,float y,float z);
void v3fRotateDeg(vector3f* u,float x,float y,float z);
void v3fRotateRad(vector3f* u,float x,float y,float z);

void v3fUntranslate(vector3f* u,float x,float y,float z);
void v3fUnscale(vector3f* u,float x,float y,float z);
void v3fUnrotateDeg(vector3f* u,float x,float y,float z);
void v3fUnrotateRad(vector3f* u,float x,float y,float z);

void v3fRotateDegX(vector3f* u,float angle);
void v3fRotateDegY(vector3f* u,float angle);
void v3fRotateDegZ(vector3f* u,float angle);
void v3fRotateRadX(vector3f* u,float angle);
void v3fRotateRadY(vector3f* u,float angle);
void v3fRotateRadZ(vector3f* u,float angle);

vector3f v3fProjectPointOnLine(const vector3f* P,
							const vector3f* A,
							const vector3f* u);

void v3fNormalize(vector3f* u);

// return the component at 'index'
// index = 0 => return x
// index = 1 => return y
// index = 2 => return z
float v3fComponent(const vector3f* u,int component);

void decomposeOrtho(vector3f u,vector3f v,
					vector3f* u0,vector3f* u1);

float v3fProjectOrtho(const vector3f* u,
					  const vector3f* v);

// physics

void v3fFreeFall(vector3f* P,vector3f* u,float R,float G,float t);
void v3fFreeFallSpeed(vector3f* u,float R,float G,float t);

/**
 * Given the current direction, a desired direction and a stepped rotational 
 * constraint around the y axis, return an adjusted direction.
 * Note that the returned x/z subvector is normalized; the y component
 * is preserved.
 * If the current direction is zero, return the desired direction immediately.
 * if the desired direction is zero, return zero.
 */
vector3f v3fAdjustDirection(vector3f* currentDirection,
							vector3f* desiredDirection,
							float maxRadsPerMillisecond,int ms);

#pragma mark debugging

void v3fAssert(const vector3f* u);
void v3fAssertEquals(const vector3f* u,const vector3f* v);
void v3fPrint(vector3f u);

#endif
