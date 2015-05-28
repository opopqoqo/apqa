// Copyright T.E.A de Souza 2012-2015 - MIT LICENSE

#include "sphere3f.h"
#include "matmath4f.h"
#include "vecmath3f.h"

sphere3f sp3fWithCentreAndRadius(const v3f* c,
								 float r){

	sphere3f s = {*c,r};
	return s;
	
}

void sp3fTransform(sphere3f* sphere, const m4f* mat){

	v3f O = sphere->location;
	
	m4fTransformVertex3f(mat,&O);
	
	float r = sphere->radius;
	
	v3f P[3] = {
		{r,0,0},
		{0,r,0},
		{0,0,r}
	};
	
	float l = 0.0f;
	
	for(int i=0;i<3;i++){
		m4fTransformVector3f(mat,&P[i]);
		float k = v3fLength(&P[i]);
		if(k>l)l=k;
	}
	
	sphere3f s = { O,l };
	
	*sphere = s;
	
}
