// Copyright T.E.A de Souza 2012-2015 - MIT LICENSE

#import "vec.h"
#import <stdbool.h>

typedef struct{

	v2f location;
	float radius;
	
}disc;

bool disc_isPointInside(const disc* bounds,
						const v2f* point);