


#include "vec.h"
#include "triangle.h"
#include "faceList.h"
#include "util.h"

#pragma mark structure -------------------------------

typedef struct{
	
	triangle3us*	faces;
	int				faceCount;
	v6f*			vertices;
	int vertexCount;
	
}imesh6fus;

typedef struct{

	triangle3us*	faces;
	int				faceCount;
	v8f*			vertices;
	int vertexCount;
	
}imesh8fus;

#pragma mark constructor  ----------------------------

imesh6fus im6fusWithCapacity(int maxVertexCount,
							 int maxTriangleCount );

imesh6fus im6fusWith(v6f* vertices,int vCount,
					 triangle3us* faces,int fCount );

imesh6fus im6fusDuplicate( const imesh6fus* m );

#pragma mark operations ------------------------------

vertexIndex im6fusAddVertex(imesh6fus* m,
							 const v6f* v,
							 float th);

vertexIndex im6fusAddVertex2(imesh6fus* m,
							  const v6f* v,
							  x100* map,
							  float th);

vertexIndex im6fusAddVertexFast(imesh6fus* m,
							 const v6f* v,
							 float th);

triangle3us* im6fusAddIndexedTriangle(imesh6fus* m,
							  unsigned short A,
							  unsigned short B,
							  unsigned short C);

triangle3us* im6fusAddTriangle3us(imesh6fus* m,
						  const triangle3us* t);

triangle3us* im6fusAddTriangle6f(imesh6fus* m,
						 const triangle6f* t,
						 float th);

triangle3us* im6fusAddTriangle6f_2(imesh6fus* m,
								 const triangle6f* t,
								 x100* map,
								 float th);

triangle3us im6fusRemoveTriangle(imesh6fus* m,
								 int index);

#pragma mark getting information ---------------------

triangle6f im6fusGetTriangle6f(const imesh6fus* mesh, int i);

imesh6fus* im6fusParts(const imesh6fus* mesh,
					   int* count);

float im6fusArea(const imesh6fus* mesh);

imesh6fus* im6fusParts2(const imesh6fus* mesh0,
						int* numberOfParts);

faceList* im6fusFacesPerVertex(const imesh6fus* mesh);

void im6fuAssert(const imesh6fus* m);