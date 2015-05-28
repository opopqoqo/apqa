// Copyright T.E.A de Souza 2012-2015 - MIT LICENSE

#include "vector6f.h"
#include "vecmath3f.h"
#include "matmath4f.h"

void v6fAssert(const v6f* u){

	v3fAssert(&u->coord);
	v3fAssert(&u->normal);
	
}

void v6fTransform(v6f* v, const m4f* matrix){

	m4fMultiplyV3fWithTranslation(matrix, &v->coord);
	m4fMultiplyV3f(matrix, &v->normal);
	
}