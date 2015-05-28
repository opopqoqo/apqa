
#import "vec.h"

/**
 * Column major matrix math
 * (glMultMatrix, glTranslatef, ...)
 */

#pragma mark OpenGL style operators ------------------

/** like glMultMatrixf */
void mMultMatrixf(float* m4x4,
				  const float* arg4x4);

/** like glLoadIdentity */
void mLoadIdentity(float* m4x4);

/** like glLoadMatrix */
void mLoadMatrix(float* m4x4,
				 const float* arg4x4);

/** like glTranslate */
void mTranslatef(float* m,
				 float x,float y,float z);

/** like glScale */
void mScalef(float* m,
			 float x,float y,float z);

/** like glRotate */
void mRotatef(float* m,
			  float angleDeg,float x,float y,float z);

#pragma mark other operators -------------------------

void mTransformV3f(float* v3f, const float* m4x4);

void mMultVector4f(float* v4f, const float* m4x4);

// component extraction

float* mTranslationComponent(float* m4x4);

// non standard, but useful

v3f mBasisX(const float* m);
v3f mBasisY(const float* m);
v3f mBasisZ(const float* m);

void mRotateXf(float* m,const float angleDeg);

void mRotateYf(float* m,const float angleDeg);

void mRotateZf(float* m,const float angleDeg);

void mLoadTranslation(float* m4x4,float x,float y,float z);

void mLoadScale(float* m4x4,float x,float y,float z);

void mLoadRotation(float* m,const float angleDeg,float x,float y,float z);

void mLoadPerspective(float* m,
					  float fovYInDegrees,
					  float aspect,
					  float zNear,
					  float zfar);

void mLoadRotationX(float* m4x4,float A);

void mLoadRotationY(float* m4x4,float A);

void mLoadRotationZ(float* m4x4,float A);

void mTranspose(float* m);

void mInverse(float* m);

// debugging

void mPrint(float* m4x4);

// debugging

void mCheckAgainstGLState(float* m4x4);
