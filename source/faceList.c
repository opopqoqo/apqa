
#include "faceList.h"

#include <stdlib.h>
#include <memory.h>

faceList faceListWithCapacity(int c){

	faceList list;
	list.count = 0;
	list.capacity = c;
	list.faces = malloc(sizeof(unsigned int)*c);
	
	return list;
	
}

bool faceListAddFace(faceList *list, int index){

	bool reallocated = false;
	
	int c=list->capacity;
	
	if(list->count==c){
	
		int d = c*2;
		size_t bytes = sizeof(faceIndex)*d;
		list->faces = realloc(list->faces, bytes);
		list->capacity = d;
		reallocated = true;
		
	}
	
	list->faces[list->count++]=index;
	
	return reallocated;
	
}