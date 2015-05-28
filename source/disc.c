
#import "disc.h"
#import "vecmath2f.h"

bool disc_isPointInside(const disc* bounds,
						const v2f* point){

	float d = v2fDistance(point, &bounds->location);
	
	return d < bounds->radius;
	
}