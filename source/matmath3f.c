
#import "matmath3f.h"
#import "invert_matrix3x3.h"
#import "memory.h"
#import "vecmath3f.h"
#import <math.h>
#import "xmath.h"

#define MATRIX_SIZE 3
#define MATRIX_ELEMENT_COUNT 9

#pragma mark factory ---------------------------------

m3f m3fDuplicate(const m3f* m){

	m3f copy = *m;
	return copy;
	
}

m3f m3fMakeIdentity(){
	
	float out[] ={
		1,0,0,
		0,1,0,
		0,0,1
	};
	
	m3f m;
	
	memcpy(&m, out, sizeof(m3f));
	
	return m;
	
}

m3f m3fMakeInverse(const m3f* m){
	
	m3f M = m3fDuplicate(m);
	m3fInvert(&M);
	return M;
	
}

m3f m3fMakeProduct(const m3f* a,const m3f* b){
	
	float* A = (float*)a;
	float* B = (float*)b;
	
	m3f m;
	float* M = (float*)&m;
	
	M[0] = A[0]*B[0] + A[3]*B[1] + A[6]*B[2];
    M[3] = A[0]*B[3] + A[3]*B[4] + A[6]*B[5];
    M[6] = A[0]*B[6] + A[3]*B[7] + A[6]*B[8];
    
    M[1] = A[1]*B[0] + A[4]*B[1] + A[7]*B[2];
    M[4] = A[1]*B[3] + A[4]*B[4] + A[7]*B[5];
    M[7] = A[1]*B[6] + A[4]*B[7] + A[7]*B[8];
    
    M[2] = A[2]*B[0] + A[5]*B[1] + A[8]*B[2];
    M[5] = A[2]*B[3] + A[5]*B[4] + A[8]*B[5];
    M[8] = A[2]*B[6] + A[5]*B[7] + A[8]*B[8];

	return m;
	
}

m3f m3fMakeProduct_2(const m3f* a,const m3f* b){
	
	float* A = (float*)a;
	float* B = (float*)b;
	
	m3f m;
	float* M = (float*)&m;
	
	M[0] = A[0]*B[0] + A[3]*B[1] + A[6]*B[2];
    M[1] = A[1]*B[0] + A[4]*B[1] + A[7]*B[2];
    M[2] = A[2]*B[0] + A[5]*B[1] + A[8]*B[2];
    M[3] = A[0]*B[3] + A[3]*B[4] + A[6]*B[5];
    M[4] = A[1]*B[3] + A[4]*B[4] + A[7]*B[5];
    M[5] = A[2]*B[3] + A[5]*B[4] + A[8]*B[5];
    M[6] = A[0]*B[6] + A[3]*B[7] + A[6]*B[8];
    M[7] = A[1]*B[6] + A[4]*B[7] + A[7]*B[8];
    M[8] = A[2]*B[6] + A[5]*B[7] + A[8]*B[8];
	
	return m;
	
}

m3f m3fMakeRotationDeg(float a, float x, float y, float z){

	float rads = degreesToRadians(a);
	return m3fMakeRotationRad(rads,x,y,z);
	
}

m3f m3fMakeRotationRad(float a, float x, float y, float z){

    v3f v = {x,y,z};
	v3fNormalize(&v);
    float cos = cosf(a);
    float cosp = 1.0f - cos;
    float sin = sinf(a);
    
    float m[] = {
		
		cos + cosp * v.x * v.x,
		cosp * v.x * v.y + v.z * sin,
		cosp * v.x * v.z - v.y * sin,
		
		cosp * v.x * v.y - v.z * sin,
		cos + cosp * v.y * v.y,
		cosp * v.y * v.z + v.x * sin,
		
		cosp * v.x * v.z + v.y * sin,
		cosp * v.y * v.z - v.x * sin,
		cos + cosp * v.z * v.z
	};
	
    return m3fMakeMatrixFromArray(m);
	
}

m3f makeTranspose(const m3f* m){

	m3f M = m3fDuplicate(m);
	m3fTranspose(&M);
	return M;
	
}

m3f m3fMakeMatrixFromArray(const float* m){

	m3f M;
	memcpy(&M, m, sizeof(m3f));
	
	return M;
	
}

#pragma mark operations ------------------------------

void m3fInvert(m3f *m){

	float out[MATRIX_ELEMENT_COUNT];
	
	//inverseMatrix3x3_cornstalks((float*)m,out);
	inverseMatrix3x3((float*)m,out);
	
	memcpy(m, out, sizeof(m3f));
	
}

void m3fInvertAndTranspose(m3f* m){
	
	float out[MATRIX_ELEMENT_COUNT];
	
	inverseTransposeMatrix3x3_batty((float*)m,out);
	
	memcpy(m, out, sizeof(m3f));

}

void m3fScale(m3f* m,float x,float y,float z){

	float s[] = {x,y,z};
	float* M = (float*)m;
	
	for (int i=0;i<3;i++){
		for(int j=0;j<MATRIX_SIZE;j++){
			M[i*MATRIX_SIZE+j] *= s[i];
		}
	}

}

void m3fTranspose(m3f* m){

	float* M = (float*)m;
	
	for(int i=0;i<MATRIX_SIZE;i++){
		for(int j=0;j<i;j++){
			char a = i*MATRIX_SIZE+j;
			char b = j*MATRIX_SIZE+i;
			float x = M[a];
			M[a] = M[b];
			M[b] = x;
		}
	}
	
}

#pragma mark getting information ---------------------

bool m3fIsEqual(const m3f* a,const m3f* b){
	
	float* Ma = (float*)a;
	float* Mb = (float*)b;
	
	for(int i=0;i<MATRIX_ELEMENT_COUNT;i++){
		
		if(Ma[i]!=Mb[i])return false;
		
	}
	return true;
	
}

bool m3fIsEqualWithTolerance(const m3f* a,const m3f* b,float t){
	
	float* Ma = (float*)a;
	float* Mb = (float*)b;
	
	for(int i=0;i<MATRIX_ELEMENT_COUNT;i++){
		
		float d = fabs(Mb[i]-Ma[i]);
		if(d>t)return false;
		
	}
	return true;
	
}

bool m3fIsIdentity(const m3f* m){
	
	m3f k = m3fMakeIdentity();
	return m3fIsEqual(m, &k);
	
}

bool m3fIsIdentityWithTolerance(const m3f* m,float t){
	
	m3f k = m3fMakeIdentity();
	return m3fIsEqualWithTolerance(m, &k,t);
	
}
