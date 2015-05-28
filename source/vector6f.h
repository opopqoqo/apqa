// Copyright T.E.A de Souza 2012-2015 - MIT LICENSE

#ifndef math_vector6f_h
#define math_vector6f_h

// ___________________________________________________

#include "vec.h"
#include "matrix.h"

#pragma mark structure -------------------------------

#pragma mark constructors ----------------------------

#pragma mark operations ------------------------------

void v6fRoundCoord(v6f* u,float threshold);
void v6fTransform(v6f* v, const m4f* matrix);

#pragma mark debug -----------------------------------

void v6fAssert(const v6f* u);

#endif
