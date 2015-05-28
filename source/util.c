
#include "util.h"
#include <math.h>
#include <memory.h>
#include <stdlib.h>
#include <assert.h>
#include "vec.h"

vertexList* x100MapSlot(const v6f* v,x100* map){
	
	float k = 100*(v->coord.x-map->min) / map->range;
	int n=trunc(k);
	
	assert(n>=0);
	assert(n<=100);
	
	if(n==100)n=99;
	
	return &map->slot[n];
	
}

x100_dual x100MapDualSlot(const v6f* v,x100* map){
	
	x100_dual slots;
	slots.A = NULL;
	slots.B = NULL;
	
	float k = 100*(v->coord.x-map->min) / map->range;
	int n=trunc(k);
	
	assert(n>=0);
	assert(n<=100);
	
	if(n==100){
		slots.A = &map->slot[99];
		return slots;
	}
	
	slots.A = &map->slot[n==100?99:n];
	
	float d0 = k-n;
	float d1 = n+1-k;

	
	if(d0<map->threshold){
		
		int m = n-1;
		if(m<0)return slots;
		
		slots.B=&map->slot[m];
		
	}else if(d1<map->threshold){
		
		int m = n+1;
		if(m>=100)return slots;
		
		slots.B=&map->slot[m];
		
	}
	
	return slots;
	
}

bool vertexListAdd(vertexIndex index,vertexList* list){
	
	assert(list);
	
	bool reallocated = false;
	
	int c=list->capacity;
	
	if(list->count==c){
		
		int d = c*2;
		size_t bytes = sizeof(v6f)*d;
		list->vertices = realloc(list->vertices, bytes);
		list->capacity = d;
		reallocated = true;
		
	}
	
	list->vertices[list->count++]=index;
	
	return reallocated;
	
}

x100 x100WithRange(float min,float max,float threshold){
	
	x100 map;
	map.min = min;
	map.max = max;
	map.range = max-min;
	map.threshold = threshold/map.range;
	
	for(int i=0;i<100;i++){
		
		map.slot[i] = vertexListWithCapacity(1);
		
	}return map;
	
}

vertexList vertexListWithCapacity(int c){
	
	vertexList list;
	list.count=0;
	list.capacity=c;
	
	list.vertices = malloc(sizeof(vertexIndex)*c);
	
	return list;
	
}
