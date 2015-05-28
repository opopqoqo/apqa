
#ifndef math_mesh_h
#define math_mesh_h

// ___________________________________________________

#include "mesh6f.h"
#include "mesh3f.h"
#include "imesh6f.h"

#pragma mark additional constructors -----------------

imesh6fus im6fWithMesh6f(const mesh6f* m,float th);
imesh6fus im6fWithMesh6f_2(const mesh6f* m,float th);

mesh6f m6fWithIMesh6f(const imesh6fus* m);

#endif