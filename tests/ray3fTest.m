// Copyright T.E.A de Souza 2012-2015 - MIT LICENSE

#import <XCTest/XCTest.h>
#include "ray3f.h"

@interface ray3fTest : XCTestCase

@end

@implementation ray3fTest

/* 
 * Intersect a ray with the XY plane lying at origin
 */
-(void)testRayHasIntersectionWithXYPlane1 {
	
	ray3f ray = { {0,0,-1}, {0,0,1} };
	
	v3f o = {0,0,0};
	v3f u = {1,0,0};
	v3f v = {0,1,0};
	
	p3f plane = p3fWithOriginAndVectors(&o, &u, &v);
	
	v3f I = r3fIntersectPlane(&ray, &plane);
	
	XCTAssert(I.x == 0, "@ x: %f ",I.x);
	XCTAssert(I.y == 0, "@ x: %f ",I.y);
	XCTAssert(I.z == 0, "@ x: %f ",I.y);
	
}

/*
 * Similar to the above
 */
-(void)testRayHasIntersectionWithXYPlane2 {
	
	ray3f ray = { {0,0,5}, {0,0,-1} };
	
	v3f o = {0,0,0};
	v3f u = {1,0,0};
	v3f v = {0,1,0};
	
	p3f plane = p3fWithOriginAndVectors(&o, &u, &v);
	
	v3f I = r3fIntersectPlane(&ray, &plane);
	
	XCTAssert(I.x == 0, "@ x: %f ",I.x);
	XCTAssert(I.y == 0, "@ x: %f ",I.y);
	XCTAssert(I.z == 0, "@ x: %f ",I.y);
	
}

/*
 * Now the ray is facing backwards.
 */
-(void)testRayHasNoIntersectionWithXYPlane {
	
	ray3f ray = { {0,0,-1}, {0,0,-1} };
	
	v3f o = {0,0,0};
	v3f u = {1,0,0};
	v3f v = {0,1,0};
	
	p3f plane = p3fWithOriginAndVectors(&o, &u, &v);
	
	v3f I = r3fIntersectPlane(&ray, &plane);
	
	XCTAssert(isnan(I.x), "@ x: %f ",I.x);
	XCTAssert(isnan(I.y), "@ x: %f ",I.y);
	XCTAssert(isnan(I.z), "@ x: %f ",I.y);
	
}

@end
