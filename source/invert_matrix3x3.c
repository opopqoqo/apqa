

#import "invert_matrix3x3.h"
#import <stdio.h>

#define MATRIX_SIZE 3
#define MATRIX_ELEMENT_COUNT 9

/*****************************************************
 *
 * 3x3 matrix inversion is derived from:
 * http://stackoverflow.com/questions/983999/simple-3x3-matrix-inverse-code-c
 *
 ****************************************************/

float inv3x3(int i,int j,const float* m){
	
	int o = i-j;
	
	i += MATRIX_SIZE+1-o;
	j += MATRIX_SIZE+1+o;
	
	#define e(a,b) m[ ((i+a)%MATRIX_SIZE)*MATRIX_SIZE + ((j+b)%MATRIX_SIZE) ]
	
	float inv =
	+ e(0, 0)*e(1, 1)
	- e(0, 1)*e(1, 0);
	
	return inv;
	
	#undef e
	
}

bool inverseMatrix3x3(const float *m,float* out){
	
	float inv[9];
	
	for(int i=0;i<MATRIX_SIZE;i++)
		for(int j=0;j<MATRIX_SIZE;j++)
			inv[i*MATRIX_SIZE+j] = inv3x3(i,j,m);
	
	double D = 0;
	
	for(int k=0;k<MATRIX_SIZE;k++)
		D += m[k] * inv[k*MATRIX_SIZE];
	
    if (D == 0) return false;
	
    D = 1.0 / D;
	
    for (int i = 0; i < MATRIX_ELEMENT_COUNT; i++)
        out[i] = inv[i] * D;
	
    return true;
	
}

// ___________________________________________________

void inverseTransposeMatrix3x3(const float *m,float* out){
	
	#define e(x,y) m[(y%3)*3+(x%3)]
	
	double D=0; for(int i=0;i<3;i++){
		
		D += e(0,i) *
		(  e(1,i+1)*e(2,i+2)
		 - e(1,i+2)*e(2,i+1) );
		
	}
	
	double I = 1/D;
	
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			
			out[j*3+i] =
			(  e(j+1,i+1)*e(j+2,i+2)
			 - e(j+1,i+2)*e(j+2,i+1) ) * I;
			
		}
	}
	
	#undef e
	
}

// ___________________________________________________

#define A00 m[0]
#define A01 m[1]
#define A02 m[2]
#define A10 m[3]
#define A11 m[4]
#define A12 m[5]
#define A20 m[6]
#define A21 m[7]
#define A22 m[8]

void inverseMatrix3x3_cornstalks(const float *m,float* out){

	// computes the inverse of a matrix m
	double D =
	  A00 * (A11*A22 - A21*A12)
	+ A01 * (A12*A20 - A10*A22)
	+ A02 * (A10*A21 - A11*A20);

	double I = 1 / D;

	out[0] = (A11*A22 - A21*A12) * I;
	out[1] = (A02*A21 - A01*A22) * I;
	out[2] = (A01*A12 - A02*A11) * I;
	out[3] = (A12*A20 - A10*A22) * I;
	out[4] = (A00*A22 - A02*A20) * I;
	out[5] = (A10*A02 - A00*A12) * I;
	out[6] = (A10*A21 - A20*A11) * I;
	out[7] = (A20*A01 - A00*A21) * I;
	out[8] = (A00*A11 - A10*A01) * I;
	
}

void inverseTransposeMatrix3x3_batty(const float *m,float* out){

	double D =
	  A00*( A11*A22 - A21*A12 )
	+ A01*( A12*A20 - A10*A22 )
	+ A02*( A10*A21 - A11*A20 );
	
	double I = 1.0/D;
	
	out[0] =  (A11*A22 - A21*A12) * I;
	out[3] = -(A01*A22 - A02*A21) * I;
	out[6] =  (A01*A12 - A02*A11) * I;
	out[1] = -(A10*A22 - A12*A20) * I;
	out[4] =  (A00*A22 - A02*A20) * I;
	out[7] = -(A00*A12 - A10*A02) * I;
	out[2] =  (A10*A21 - A20*A11) * I;
	out[5] = -(A00*A21 - A20*A01) * I;
	out[8] =  (A00*A11 - A10*A01) * I;
	
}

