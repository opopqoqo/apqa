
#include "plane3f.h"
#include "vecmath3f.h"

#pragma mark constructors ----------------------------

p3f p3fWithOriginAndVectors(const v3f* P,
							const v3f* u,
							const v3f* v){

	p3f p;
	p.origin = *P;
	p.u = *u;
	p.v = *v;
	return p;
	
}

#pragma mark operations ------------------------------

void p3fTranslate(p3f* p,const v3f* u){

	v3fAdd(&p->origin, u);
	
}