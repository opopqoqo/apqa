// Copyright T.E.A de Souza 2012-2015 - MIT LICENSE

#import "bounds.h"

bounds2f makeBounds2f(GLfloat x,GLfloat y,
						GLfloat w,GLfloat h){

	bounds2f b = {x,x+w,y,y+h};
	return b;
}

void b2fClamp(GLfloat* x,GLfloat* y,const bounds2f* bounds){

	if ( *x < bounds->x[0] ) *x = bounds->x[0];
	if ( *x > bounds->x[1] ) *x = bounds->x[1];

	if ( *y < bounds->y[0] ) *y = bounds->y[0];
	if ( *y > bounds->y[1] ) *y = bounds->y[1];
	
}

bool b2fIsOutside(const v2f* p,
				  const bounds2f* bounds){

	if(p->x < bounds->x[0]) return true;
	if(p->x > bounds->x[1]) return true;
	if(p->y < bounds->y[0]) return true;
	if(p->y > bounds->y[1]) return true;
	
	return false;
	
}

float b2fWidth(const bounds2f* b){

	return b->x[1]-b->x[0];
	
}

float b2fHeight(const bounds2f* b){
	return b->y[1]-b->y[0];
}