// Copyright T.E.A de Souza 2012-2015 - MIT LICENSE

#import <stdbool.h>

bool inverseMatrix3x3(const float *m,float* out);

void inverseMatrix3x3_cornstalks(
							   const float *m,
							   float* out);

void inverseTransposeMatrix3x3_batty(
									 const float *m,
									 float* out);

void inverseTransposeMatrix3x3(
							   const float *m,
							   float* out);