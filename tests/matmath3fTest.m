
#import <XCTest/XCTest.h>
#import "matmath3f.h"

@interface matmath3fTest : XCTestCase

@end

@implementation matmath3fTest

- (void)testInvertMatrix3x3_1
{
	
	m3f M = m3fMakeIdentity();
	
	m3f I = m3fMakeInverse(&M);
	
	m3f P = m3fMakeProduct(&M, &I);
	
	BOOL isIdentity = m3fIsIdentity(&P);
	XCTAssertTrue(isIdentity, @"NO");
	
}

- (void)testInvertMatrix3x3_2
{
	
	//proofInv();
	
	srand(3466);
	
	for(int i=0;i<12;i++){
		
		m3f M = m3fMakeRotationDeg((rand()*1.0/RAND_MAX)*180,
								   (rand()*1.0/RAND_MAX),
								   (rand()*1.0/RAND_MAX),
								   (rand()*1.0/RAND_MAX));
		
		m3fScale(&M, 2.0, 1.3, 3.4);
		
		m3f I = m3fMakeInverse(&M);
		
		m3f P = m3fMakeProduct(&M, &I);
		
		BOOL isIdentity = m3fIsIdentityWithTolerance(&P,0.000001);
		XCTAssertTrue(isIdentity, @"NO");
	}
}

@end
