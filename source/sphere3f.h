
#ifndef math_sphere3f_h
#define math_sphere3f_h

#import "vec.h"
#import "matrix.h"

typedef struct{
	
	v3f location;
	float radius;
	
}sphere3f;

#pragma mark constructors ----------------------------

sphere3f sp3fWithCentreAndRadius(const v3f* c,
								 float r);

void sp3fTransform(sphere3f* sphere, const m4f* mat);

#pragma mark operations ------------------------------

#endif