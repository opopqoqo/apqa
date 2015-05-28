// Copyright T.E.A de Souza 2012-2015 - MIT LICENSE

#import <XCTest/XCTest.h>
#import "mesh.h"

@interface imesh6fTest : XCTestCase

@end

@implementation imesh6fTest

-(void)testMeshToIMesh1{
	
	#define n 0, 0,0,1
	
	float data[36]={
		
		1,2, n,
		3,4, n,
		5,6, n,
		
		7,8, n,
		9,10, n,
		11,12, n
		
	};

	#undef n
	
	mesh6f m = m6fWithData((triangle6f*)data,2);
	
	imesh6fus imesh = im6fWithMesh6f(&m, 1e-5);
	
	XCTAssert(imesh.faceCount==2,@"%i",imesh.faceCount);
	XCTAssert(imesh.vertexCount==6,@"%i",imesh.vertexCount);
	
}

-(void)testMeshToIMesh2{
	
	#define n 0, 0,0,1

	
	float data[36]={
		
		1,2, n,
		3,4, n,
		5,6, n,
		
		5,6, n,
		7,8, n,
		9,10, n,
		
	};
	
	#undef n
	
	
	mesh6f m = m6fWithData((triangle6f*)data,2);
	
	imesh6fus imesh = im6fWithMesh6f(&m, 1e-5);
	
	XCTAssert(imesh.faceCount==2,@"%i",imesh.faceCount);
	XCTAssert(imesh.vertexCount==5,@"%i",imesh.vertexCount);
	
}

-(void)testAddTriangle{

	#define n 0, 0,0,1
	
	triangle6f t0 = {
		1,2, n,
		3,4, n,
		5,6, n
	};
	
	triangle6f t1 = {
		7,8, n,
		9,10, n,
		11,12, n
	};
	
	#undef n
	
	imesh6fus m = im6fusWithCapacity(6, 2);
	
	im6fusAddTriangle6f(&m, &t0, 1e-5);
	im6fusAddTriangle6f(&m, &t1, 1e-5);

	XCTAssert(m.faceCount==2,@"%i",m.faceCount);
	XCTAssert(m.vertexCount==6,@"%i",m.vertexCount);

	

}

-(void)testAddVertex{

	imesh6fus m = im6fusWithCapacity(2, 0);
	
	v6f v = {0,1,2,3,4,5};
	
	int i=im6fusAddVertex(&m, &v, 1e-5);
	int j=im6fusAddVertex(&m, &v, 1e-5);
	
	XCTAssert(i==j, @"%i!=%i",i,j);
	
}

-(void)testAddVertex2{
	
	imesh6fus m = im6fusWithCapacity(2, 0);
	
	v6f v0 = {0  , 1, 2, 3, 4, 5};
	v6f v1 = {0.1, 1, 2, 3, 4, 5};
	
	int i=im6fusAddVertex(&m, &v0, 1e-5);
	int j=im6fusAddVertex(&m, &v1, 1e-5);
	
	XCTAssert(i!=j, @"%i!=%i",i,j);
	
}

-(void)testAddVertex3{
	
	imesh6fus m = im6fusWithCapacity(2, 0);
	
	v6f v0 = {0    , 1, 2, 3, 4, 5};
	v6f v1 = {1e-6 , 1, 2, 3, 4, 5};
	
	int i=im6fusAddVertex(&m, &v0, 1e-5);
	int j=im6fusAddVertex(&m, &v1, 1e-5);
	
	XCTAssert(i==j, @"%i!=%i",i,j);
	
}

- (void)testMeshParts2_1
{
	
#define n 0,0,0,1
	
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
	imesh6fus im = im6fWithMesh6f(&m, 1e-5f);
	
	int c;
	
	im6fusParts2(&im, &c);
	
	XCTAssertTrue(c==2, @"mesh parts:%i",c);
	
}

- (void)testMeshParts2_2
{
	
#define n 0,0,0,1
	
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
	imesh6fus im = im6fWithMesh6f(&m, 1e-5f);
	int c;
	
	im6fusParts2(&im, &c);
	
	XCTAssertTrue(c==1, @"mesh parts:%i",c);
	
}

- (void)testMeshParts
{
	
#define n 0,0,0,1
	
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
	imesh6fus im = im6fWithMesh6f(&m, 1e-5f);
	
	int c;
	
	im6fusParts(&im, &c);
	
	XCTAssertTrue(c==2, @"mesh parts:%i",c);
	
}

- (void)testMeshParts2
{
	
#define n 0,0,0,1
	
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
	imesh6fus im = im6fWithMesh6f(&m, 1e-5f);
	int c;
	
	im6fusParts(&im, &c);
	
	XCTAssertTrue(c==1, @"mesh parts:%i",c);
	
}

- (void)testDuplicate
{
	
#define n 0, 0,0,1
	
	triangle6f t0 = {
		1,2, n,
		3,4, n,
		5,6, n
	};
	
	triangle6f t1 = {
		7,8, n,
		9,10, n,
		11,12, n
	};
	
#undef n
	
	imesh6fus m0 = im6fusWithCapacity(6, 2);
	
	im6fusAddTriangle6f(&m0, &t0, 1e-5);
	im6fusAddTriangle6f(&m0, &t1, 1e-5);
	
	imesh6fus m1 = im6fusDuplicate(&m0);

	XCTAssertTrue( t3usEquals(&m0.faces[0], &m1.faces[0]),
				  @"faces should be equal");
	
}

@end
