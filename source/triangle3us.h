// Copyright T.E.A de Souza 2012-2015 - MIT LICENSE

#ifndef math_triangle3us_h
#define math_triangle3us_h

// ___________________________________________________

#include <stdbool.h>

#pragma mark structure -------------------------------

typedef struct{
	
	unsigned short data[3];
	
}triangle3us;

#pragma mark operations ------------------------------

bool t3usIsContiguous(const triangle3us* A,
					  const triangle3us* B);

bool t3usEquals(const triangle3us* A,
				const triangle3us* B);

#endif
