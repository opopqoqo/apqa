
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "mesh.h"
#include "vecmath3f.h"

imesh6fus im6fWithMesh6f(const mesh6f* m,float th){

	imesh6fus imesh =
	im6fusWithCapacity( m->count*3, m->count );
	
	for(triangle6f* t=m->faces;
		t<m->faces+m->count;
		t++){
	
		im6fusAddTriangle6f(&imesh, t, th);
		
	} return imesh;
	
}

imesh6fus im6fWithMesh6f_2(const mesh6f* m,float th){
	
	float min = m6fMin(m, 0);
	float max = m6fMax(m, 0);
	
	x100 map = x100WithRange(min, max,th);
	
	imesh6fus imesh =
	im6fusWithCapacity( m->count*3, m->count );
	
	for(triangle6f* t=m->faces;
		t<m->faces+m->count;
		t++){
		
		im6fusAddTriangle6f_2(&imesh, t, &map, th);
		
	} return imesh;
	
}

mesh6f m6fWithIMesh6f(const imesh6fus* m){
	
	int F = m->faceCount;
	
	mesh6f M = m6fWithMaxTriangleCount(F);
	
	int degenCount=0;
	
	for(int i=0;i<F;i++){
	
		triangle6f T = im6fusGetTriangle6f(m,i);
		if(!t6fIsDegenerate(&T)){
			t6fMakeSharpEdges(&T);
		}else{
			degenCount++;
		}
		t6fAssert(&T);
		m6fAddTriangle(&M, &T);
		
	} if(degenCount){
	
		printf("degenerate triangles:%i",degenCount);
	
	} return M;
	
}