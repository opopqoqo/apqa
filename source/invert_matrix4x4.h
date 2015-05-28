
#import <stdbool.h>

bool inverseMatrix4x4(const float *m, float *out);

bool inverseMatrix4x4_mesa(const float* m, float* outp);

double det4x4_mesa(const float* m);

double det4x4(const float* m);