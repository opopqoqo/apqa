// Copyright T.E.A de Souza 2012-2015 - MIT LICENSE

#import "vec.h"
#import <stdbool.h>

#pragma mark factory methods

v2f v2fMake(const v2f* a,const v2f* b);
v2f v2fMidpoint(v2f* a, v2f* b);
v2f v2fMakeByOffset(v2f* P, v2f* u);
v2f v2fFromAngleDeg(float angle);

#pragma mark arithmetics

void v2fMul(v2f* u,float s);
void v2fAdd(v2f* u,const v2f* v);
void v2fSub(v2f* u,const v2f* v);
void v2fSet(v2f* dst,const v2f* src);
void v2fSetLength(v2f* dst,float l);
void v2fZero(v2f* u);
void v2fNeg(v2f* u);
void v2fFract(v2f* u);

#pragma mark operations

void v2fDisplace(v2f* u,float f,float s);
void v2fInterpolate(v2f* p,v2f* a,v2f* b,float pos);
void v2fNormalize(v2f* u);
void v2fRotateRad(v2f* u,float alpha);
void v2fRotateDeg(v2f* u,float alpha);
void v2fTranslate(v2f* u,float x,float y);

#pragma mark measurements

float v2fAngleRadRelativeToXAxis(const v2f* u);
char v2fIsNormalizable(v2f* u);
char v2fIsZero(v2f* u);
float v2fXZDistance(v2f* a,v2f* b);

float v2fXZDistanceSquared(v2f* a,v2f* b);
float v2fDot(const v2f* a,const v2f* b);
char v2fEquals(v2f u,v2f v);
float v2fAngleRad(const v2f* a,const v2f* b);
float v2fSignedAngleRadCCW(const v2f* a,const v2f* b);
float v2fSignedAngleDegCCW(const v2f* a,const v2f* b);
float v2fAngleDeg(const v2f* a,const v2f* b);
float v2fOrientationRad(v2f* u);
float v2fOrientationDeg(v2f* u);
float v2fLength(const v2f* u);
float v2fDistance(const v2f* a,const v2f* b);
float v2fDistanceSquared(const v2f* a,const v2f* b);

#pragma mark physics

void v2fFreeFall(v2f* P,v2f* u,float R,float G,float t);
void v2fFreeFallSpeed(v2f* u,float R,float G,float t);