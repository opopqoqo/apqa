
#import <XCTest/XCTest.h>
#import "mesh6f.h"
@interface mesh6fTest : XCTestCase

@end

@implementation mesh6fTest

- (void)setUp
{
    [super setUp];
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)testMeshParts
{
	
	#define n 0,1,1,1
	
	float data[] = {
		
		1,2,	n,
		3,4,	n,
		5,6,	n,
		
		7,8,	n,
		9,10,	n,
		11,12,	n
		
	};
	
	#undef n
	
	mesh6f m = m6fWithData((triangle6f*)&data, 2);
	
	int c;
	
	m6fParts(m, 1e-5, &c);
	 
	XCTAssertTrue(c==2, @"mesh parts:%i",c);
	
}

- (void)testMeshParts2
{
	
#define n 0,1,1,1
	
	float data[] = {
		
		1,2,	n,
		3,4,	n,
		5,6,	n,
		
		5,6,	n,
		6,7,	n,
		8,9,	n
		
	};
	
#undef n
	
	mesh6f m = m6fWithData((triangle6f*)&data, 2);
	
	int c;
	
	m6fParts(m, 1e-5, &c);
	
	XCTAssertTrue(c==1, @"mesh parts:%i",c);
	
}

@end
