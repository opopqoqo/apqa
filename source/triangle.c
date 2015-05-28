
#include "triangle.h"
#import "vecmath3f.h"

triangle3f t3fWithTriangle6f(const triangle6f* t){

	return t3fWithPoints(&t->data[0].coord,
						 &t->data[1].coord,
						 &t->data[2].coord);
	
}

triangle6f t6fWithTriangle3f(const triangle3f* t){
	
	v3f n = t3fNormal(t);
	
	return t6fWithTriangle3fAndNormal(t,&n);
	
}

triangle6f t6fWithTriangle3fAndNormal(const triangle3f* tri,
									  const v3f* n){
	
	triangle6f t;
	
	for(int i=0;i<3;i++){
		t.data[i].coord = tri->data[i];
		t.data[i].normal = *n;
	}
	
	return t;
	
}
