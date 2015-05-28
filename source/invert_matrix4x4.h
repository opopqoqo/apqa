// Copyright T.E.A de Souza 2012-2015 - MIT LICENSE

#import <stdbool.h>

bool inverseMatrix4x4(const float *m, float *out);

bool inverseMatrix4x4_mesa(const float* m, float* outp);

double det4x4_mesa(const float* m);

double det4x4(const float* m);