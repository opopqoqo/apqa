// Copyright T.E.A de Souza 2012-2015 - MIT LICENSE

#import "colmath4f.h"

void c4fBrighten(c4f* col,float amount){

	col->red+=amount;
	col->green+=amount;
	col->blue+=amount;
	
}

void c4fDarken(c4f* col,float amount){

	col->red-=amount;
	col->green-=amount;
	col->blue-=amount;
	
}