// Copyright T.E.A de Souza 2012-2015 - MIT LICENSE

#import <XCTest/XCTest.h>
#import "triangle3f.h"

@interface triangle3fTest : XCTestCase

@end

@implementation triangle3fTest

- (void)test_t3fNormal
{
	
	v3f A = { 0,0,0 };
	v3f B = { 1,0,0 };
	v3f C = { 0,1,0 };
	
	triangle3f t = t3fWithPoints(&A, &B, &C);
	
	v3f N=t3fNormal(&t);
	
	NSLog(@"%.3f %.3f %.3f ",N.x,N.y,N.z);
	
	XCTAssert(N.x==0.0, @"normal should point up");
	XCTAssert(N.y==0.0, @"normal should point up");
	XCTAssert(N.z==1.0, @"normal should point up");
	
}

@end
