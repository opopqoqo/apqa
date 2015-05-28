
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <math.h>

#include "imesh6f.h"
#include "vecmath3f.h"
#include "util.h"

#define MAX_PARTS (32)

// ___________________________________________________

typedef unsigned short ushort;

// ___________________________________________________


#define for_each_triangle(t,m) \
for(triangle3us* t = m->faces; t<m->faces+m->faceCount; t++)

#define for_each_vertex_index(i,m) \
for(ush* i = (ush*)m->faces; i < ((ush*)(m->faces+m->faceCount))+3; i++)

// ___________________________________________________

imesh6fus im6fusWith(v6f* vertices,int vCount,
					 triangle3us* faces,int fCount ){

	imesh6fus m;
	m.faces = faces;
	m.vertices = vertices;
	m.faceCount = fCount;
	m.vertexCount = vCount;
	
	return m;
	
}

imesh6fus im6fusDuplicate( const imesh6fus* m0 ){

	imesh6fus m;
	
	size_t faceBytes = sizeof(triangle3us)*m0->faceCount ;
	size_t vertexBytes = sizeof(v6f)*m0->vertexCount;
	
	m.faces = malloc(faceBytes);
	m.vertices = malloc(vertexBytes);
	m.faceCount = m0->faceCount;
	m.vertexCount = m0->vertexCount;
	
	memcpy(m.faces, m0->faces, faceBytes);
	memcpy(m.vertices, m0->vertices, vertexBytes);
	
	return m;
	
}

bool t3usEquals(const triangle3us* A,
				const triangle3us* B){

	for(int i=0;i<3;i++){
	
		if(A->data[i]!=B->data[i]) return false;
		
	} return true;
	
}

#pragma mark operations ------------------------------

imesh6fus im6fusWithCapacity( int v, int t ){

	imesh6fus m;
	
	m.vertices = malloc( sizeof(v6f) * v );
	m.faces = malloc( sizeof(triangle3us) * t );
	//
	m.vertexCount = 0;
	m.faceCount = 0;
	
	return m;
	
}

triangle3us* im6fusAddTriangle6f(imesh6fus* m,
						 const triangle6f* t,
						 float th){

	unsigned int A = im6fusAddVertex( m, &t->data[0] ,th );
	unsigned int B = im6fusAddVertex( m, &t->data[1] ,th  );
	unsigned int C = im6fusAddVertex( m, &t->data[2] ,th  );
	
	return im6fusAddIndexedTriangle( m, A, B, C );
	
}

triangle3us* im6fusAddTriangle6f_2(imesh6fus* m,
								 const triangle6f* t,
								   x100* map,
								 float th){
	
	unsigned int A = im6fusAddVertex2( m, &t->data[0] , map, th );
	unsigned int B = im6fusAddVertex2( m, &t->data[1] , map, th  );
	unsigned int C = im6fusAddVertex2( m, &t->data[2] , map, th  );
	
	return im6fusAddIndexedTriangle( m, A, B, C );
	
}

triangle3us* im6fusAddTriangle3us(imesh6fus* m,
						  const triangle3us* t){

	int i = m->faceCount;
	m->faces[i] = *t;
	m->faceCount++;
	
	return &m->faces[i];
	
}

void v6fRoundCoord(v6f* u,float threshold){

	v3f c=u->coord;
	v3fMul(&c, 1.0/threshold);
	
	int x = c.x;
	int y = c.y;
	int z = c.z;
	
	c.x = x * threshold;
	c.y = y * threshold;
	c.z = z * threshold;
	
	u->coord = c;
	
}

triangle3us* im6fusAddIndexedTriangle(imesh6fus* m,
							  ushort A,
							  ushort B,
							  ushort C){

	int i = m->faceCount;
	m->faces[i].data[0] = A;
	m->faces[i].data[1] = B;
	m->faces[i].data[2] = C;
	m->faceCount++;
	
	return &m->faces[i];
	
}

vertexIndex im6fusAddVertex(imesh6fus* m,
							 const v6f* P,
							 float th){
	
	for(unsigned int i=0 ; i<m->vertexCount ; i++){
	
		const v3f* Q = &m->vertices[i].coord;
		
		if( v3fDistance( Q, &P->coord ) < th ){
			return i;
		}
		
	}
	
	int i = m->vertexCount;
	
	assert(i<65536);
	m->vertices[i] = *P;
	m->vertexCount++;
	
	return i;
	
}

bool im6fMatchVertexUsingSlot(const v6f* P,
									 vertexList* slot,
									 const imesh6fus* m,
									 float th,
							  vertexIndex* index){
	
	vertexIndex c;
	
	for(int i=0 ; i < slot->count ; i++){
		
		c = slot->vertices[i];
		
		const v3f* Q = &m->vertices[c].coord;
		
		if( v3fDistance( Q, &P->coord ) < th ){
			*index = c;
			return true;
		}
		
	} return false;
	
}

vertexIndex im6fusAddVertex2(imesh6fus* m,
							  const v6f* P,
							  x100* map,
							  float th){

	// try to match the specified vertex to an already
    // mapped vertex.
	
	x100_dual slots = x100MapDualSlot(P, map);

	vertexIndex index;

	bool found =
	im6fMatchVertexUsingSlot(P, slots.A, m, th,&index);
	
	if(!found)if(slots.B){
		found = im6fMatchVertexUsingSlot(P, slots.B, m, th,&index);
		if(found){
			printf("found in auxiliary slot\n");
		}
	}
	
	if(found)return index;
	
	// if we didn't match to an existing vertex,
	// add this vertex to the mesh and also
	// add it to the slots.
	
	index = m->vertexCount;
	
	m->vertices[index] = *P;
	m->vertexCount++;
	
	vertexListAdd(index,slots.A);
	if(slots.B){
		vertexListAdd(index,slots.B);
	}
	
	return index;
	
}

unsigned int im6fusAddVertex2unsafe(imesh6fus* m,
							  const v6f* P,
							  x100* map,
							  float th){
	
	vertexList* slot = x100MapSlot(P, map);
	vertexIndex index;
	
	for(int i=0 ; i < slot->count ; i++){
		
		index = slot->vertices[i];
		
		const v3f* Q = &m->vertices[index].coord;
		
		if( v3fDistance( Q, &P->coord ) < th ){
			return index;
		}
		
	} index = m->vertexCount;
	
	m->vertices[index] = *P;
	m->vertexCount++;
	
	vertexListAdd(index,slot);
	
	return index;
	
}

vertexIndex im6fusAddVertexFast(imesh6fus* m,
							 const v6f* P0,
							 float th){
	
	v6f P = *P0;
	v6fRoundCoord(&P,th);
	
	for(unsigned int i=0 ; i<m->vertexCount ; i++){
		
		const v3f* Q = &m->vertices[i].coord;
		
		if( v3fEquals(Q, &P.coord ) ){
			
			return i;
			
		}
		
	}
	
	int i = m->vertexCount;
	
	assert(i<65536);
	
	m->vertices[i] = P;
	
	m->vertexCount++;
	
	return i;
	
}

triangle3us im6fusRemoveTriangle(imesh6fus *mesh, int i){
	
	int c = mesh->faceCount;
	assert(i<c);
	
	triangle3us T = mesh->faces[i];
	
	int last = c-1;
	
	mesh->faces[i]	= mesh->faces[last];
	mesh->faceCount	= last;
	
	return T;
	
}

#pragma mark getting information ---------------------

triangle6f im6fusGetTriangle6f(const imesh6fus* mesh, int i){

	unsigned short* index = mesh->faces[i].data;
	
	v6f A = mesh->vertices[index[0]];
	v6f B = mesh->vertices[index[1]];
	v6f C = mesh->vertices[index[2]];
	
	v3fAssert(&A.coord);
	v3fAssert(&B.coord);
	v3fAssert(&C.coord);
	
	triangle6f T = {A,B,C};
	
	return T;
	
}

triangle3us* im6fusCopyAndMarkUsed(const imesh6fus* src,
								   int index,imesh6fus* dst,
								   bool* used){

	triangle3us* t=im6fusAddTriangle3us(dst,
										&src->faces[index]);
	
	used[index] = true;
	
	return t;
	
}

imesh6fus* im6fusParts2(const imesh6fus* M,
					   int* numberOfParts){
	
	*numberOfParts = 0;
	imesh6fus* parts = malloc(sizeof(imesh6fus)*MAX_PARTS);
	
	int			V		= M->vertexCount;
	int			F		= M->faceCount;
	bool*		used	= malloc( sizeof(bool) * F );
	memset(used, 0, sizeof(bool)*F );
	
	faceList*	fpv		= im6fusFacesPerVertex(M);
	int numberAdded = 0;
	
	for( int i=0; i<F; i++ ){
		
		if(used[i])continue;
		
		imesh6fus* part = &parts[*numberOfParts];
		*part = im6fusWithCapacity(V,F);
		*numberOfParts=(*numberOfParts)+1;
		part->vertexCount = V;
		memcpy(part->vertices, M->vertices, sizeof(v6f)*V );
		
		im6fusCopyAndMarkUsed(M, i, part, used);
		
		ushort* indices = (ushort*)part->faces;
		
		for(int j=0;j<part->faceCount*3;j++){
			
			ushort k = indices[j];
			
			faceList* list = &fpv[k];
			for( int n = 0; n<list->count; n++ ){
				
				int cIndex = list->faces[n];
				if(used[cIndex])continue;
				im6fusCopyAndMarkUsed(M, cIndex, part, used);
				
			}
			
		}
		numberAdded+=part->faceCount;
		
		//rintf("added to part:%i\n",part->faceCount);
		
	} //rintf("number of parts:%i\n",*numberOfParts);
	
	for(int i=0;i<M->faceCount;i++)assert(used[i]);
	
	assert(numberAdded==F);
	
	return parts;
	
}

imesh6fus* im6fusParts(const imesh6fus* mesh0,
						int* numberOfParts){
	
	imesh6fus mesh = im6fusDuplicate(mesh0);
	
	*numberOfParts = 0;
	
	imesh6fus* parts = malloc(sizeof(imesh6fus)*MAX_PARTS);
	
	while(mesh.faceCount>0){
		
		// init a new mesh in parts array
		
		imesh6fus* part = &parts[*numberOfParts];
		
		*part = im6fusWithCapacity(mesh.vertexCount,
								   mesh.faceCount);
		
		*numberOfParts=(*numberOfParts)+1;
		
		// init part with first available triangle
		
		triangle3us T = im6fusRemoveTriangle(&mesh, 0);
		
		im6fusAddTriangle3us(part,&T);
		
		for(int next=0; next < part->faceCount; next++ ){
			
			triangle3us* T = &part->faces[next];
			
			for( int i=mesh.faceCount-1 ; i>=0 ;i--){
				
				triangle3us* C = &mesh.faces[i];
				
				if(t3usIsContiguous(T, C)){
					
					im6fusAddTriangle3us(part,C);
					im6fusRemoveTriangle(&mesh,i);
					
				}
				
			} //m6fAssert(*part);
			
		}
		
		printf("added to part:%i\n",part->faceCount);
		
	}
	
	printf("number of parts:%i\n",*numberOfParts);
	
	return parts;
	
}

float im6fusArea(const imesh6fus* mesh){
	
	float area=0.0f;
	
	for(int i=0;i<mesh->faceCount;i++){
	
		triangle6f t = im6fusGetTriangle6f(mesh, i);
		area+=t6fArea(&t);
		
		assert(!isinf(area));
		assert(!isnan(area));
		
	} return area;
	
}

faceList* im6fusFacesPerVertex(const imesh6fus* m){
	
	faceList* fpv = malloc( sizeof(faceList) * m->vertexCount );
	
	for(int i=0; i<m->vertexCount; i++){
		fpv[i] = faceListWithCapacity(4);
	}
	
	faceIndex i=0;
	int reallocations = 0;
	for_each_triangle(t,m){
		for(int j=0;j<3;j++){
			
			faceList* list = fpv + t->data[j];
			reallocations+=faceListAddFace(list, i);
			
		} i++;
	}
	
	printf("reallocation ratio %.1f\n",(reallocations*1.0)/m->vertexCount);
	
	return fpv;
	
}

void im6fuAssert(const imesh6fus* m){

	int V = m->vertexCount;
	int F = m->faceCount;
	
	for(int i=0;i<V;i++){
	
		v3fAssert(&m->vertices[i].coord);
		v3fAssert(&m->vertices[i].normal);
		
	}
	
	for(int i=0;i<F;i++){
	
		for(int j=0;j<3;j++){
		
			assert(m->faces[i].data[j]<V);
			
		}
		
	}
	
}
