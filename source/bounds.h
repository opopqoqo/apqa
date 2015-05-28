// Copyright T.E.A de Souza 2012-2015 - MIT LICENSE

#import <stdbool.h>
#import "vec.h"

typedef struct{

	float x[2];
	float y[2];
	
}bounds2f;

bounds2f makeBounds2f(float x,float y,
					  float w,float h);

void b2fClamp(GLfloat* x,GLfloat*y,
			  const bounds2f* bounds);

bool b2fIsOutside(const v2f* point,
				  const bounds2f* bounds);

float b2fWidth(const bounds2f* bounds);

float b2fHeight(const bounds2f* bounds);