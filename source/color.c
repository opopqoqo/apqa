
#import "color.h"
#import "xmath.h"

c4f c4fMake(float r,float g,float b,float a){

	c4f c = {r,g,b,a};
	return c;
	
}

c3f c3fMake(float r,float g,float b){
	
	c3f c = {r,g,b};
	return c;
	
}

c3f c3fRandom(){
	
	c3f c = {
		randomFloat(),
		randomFloat(),
		randomFloat()};
	
	return c;
	
}

c4f c4fRandom(){
	
	c4f c = {
		randomFloat(),
		randomFloat(),
		randomFloat(),
		randomFloat()};

	return c;
	
}