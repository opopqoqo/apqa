
#ifndef math_util_h
#define math_util_h

// ___________________________________________________

#include <stdbool.h>
#include "vec.h"

#pragma mark types -----------------------------------

typedef unsigned short vertexIndex;

#pragma mark structures ------------------------------

typedef struct{
	
	vertexIndex* vertices;
	int count;
	int capacity;
	
}vertexList;

typedef struct{
	
	vertexList slot[100];
	float min,max,range,threshold;
	
}x100;

typedef struct{

	vertexList* A;
	vertexList* B;
	
} x100_dual;

#pragma mark operations ------------------------------

vertexList vertexListWithCapacity(int c);
bool vertexListAdd(vertexIndex index,
				   vertexList* list);

vertexList* x100MapSlot(const v6f* v,x100* map);

x100_dual x100MapDualSlot(const v6f* v,x100* map);

x100 x100WithRange(float min,float max,float threshold);

// ___________________________________________________

#endif