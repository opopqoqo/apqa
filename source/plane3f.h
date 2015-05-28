// Copyright T.E.A de Souza 2012-2015 - MIT LICENSE

#ifndef math_plane3f
#define math_plane3f

// ___________________________________________________

#include "vec.h"

// ___________________________________________________

typedef struct{

	v3f origin,u,v;
	
}p3f;

#pragma mark constructors ----------------------------

p3f p3fWithOriginAndVectors(const v3f* a,
							const v3f* b,
							const v3f* c);

#pragma mark operations ------------------------------

void p3fTranslate(p3f* p,const v3f* u);

#pragma mark getting information ---------------------


#endif
