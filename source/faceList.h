
#ifndef math_face_list_h
#define math_face_list_h

#include <stdbool.h>

typedef unsigned int faceIndex;

typedef struct{
	
	unsigned int* faces;
	int count;
	int capacity;
	
}faceList;

#pragma mark constructors ----------------------------

faceList faceListWithCapacity(int c);

#pragma mark operations ------------------------------

bool faceListAddFace(faceList*f, int index);

#endif