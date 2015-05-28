
typedef unsigned char dimension;

#pragma mark constructors ----------------------------

void vfMake(const float* A,
			const float* B,
			float* result,
			dimension size);

float* vfNew(dimension size);

#pragma mark getting information ---------------------

float vfDistance(const float* A,
				 const float* B,
				 dimension size);

float vfDistanceSquared(const float* A,
						const float* B,
						dimension size);

float vfLengthSquared(const float* u,
					  dimension size);

float vfLength(const float* u,
			   dimension size);

#pragma mark operations ------------------------------

void vfNormalize(float* u,
				  dimension size);

void vfAdd(float* u,
		   const float* v,
		   dimension size);

void vfSub(float* u,
		   const float* v,
		   dimension size);

void vfMul(float* u,
		   const float* v,
		   dimension size);

void vfDiv(float* u,
		   const float* v,
		   dimension size);

void vfScale(float* u,
			  float factor,
			  dimension size);

void vfOffset(float* u,
			  float factor,
			  dimension size);

void vfsmoothstep(const float* e0,
				  const float* e1,
				  float x,
				  float *dst,
				  dimension size);

