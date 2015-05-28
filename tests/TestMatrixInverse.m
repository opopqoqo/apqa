
#import <SenTestingKit/SenTestingKit.h>
#import "matmath4f.h"

@interface TestMatrixInverse : SenTestCase

@end

@implementation TestMatrixInverse

- (void)setUp{ [super setUp]; }

- (void)tearDown{ [super tearDown]; }

- (void)testExample
{
	BOOL isIdentity = NO;
	STAssertTrue(isIdentity, @"should be identity");
}

@end
