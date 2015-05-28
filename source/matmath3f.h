// Copyright T.E.A de Souza 2012-2015 - MIT LICENSE

#import "matrix.h"
#import <stdbool.h>

#pragma mark factory ---------------------------------

m3f m3fDuplicate(const m3f* m);
m3f m3fMakeIdentity();
m3f m3fMakeInverse(const m3f* m);
m3f m3fMakeProduct(const m3f* a,const m3f* b);
m3f m3fMakeTranspose(const m3f* m);
m3f m3fMakeRotationRad(float a,float x,float y,float z);
m3f m3fMakeRotationDeg(float a,float x,float y,float z);
m3f m3fMakeMatrixFromArray(const float* arr);

#pragma mark operations ------------------------------

void m3fInvert(m3f *m);
void m3fInvertAndTranspose(m3f *m);
void m3fTranspose(m3f* m);
void m3fScale(m3f* m,float x,float y,float z);

#pragma mark getting information ---------------------

bool m3fIsIdentity(const m3f* m);
bool m3fIsIdentityWithTolerance(const m3f* m,float t);
bool m3fIsEqual(const m3f* a,const m3f* b);
bool m3fIsEqualWithTolerance(const m3f* a,const m3f* b,float t);