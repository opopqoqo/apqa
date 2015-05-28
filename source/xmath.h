
#import <stdbool.h>

/**
 * Adjust the specified rotation towards the desired
 * rotation, given a time step and the maximum
 * rotation per milliseconds
 */
float adjustRotation(float currentRotationRads,
					 float desiredRotationRads,
					 float maxRadsPerMs,
					 int ms);

/**
 * Return the angle of the (x,y) vector relative to 
 * the x axis, in degrees.
 */
float angleDeg(float x,float y);

float fract(float x);

/**
 * Return the angle of the (x,y) vector relative to 
 * the x axis, in radians.
 */
float angleRad(float x,float y);

float angularDistance(float a,float b);

/* clamp x to [a,b] */
float clamp(float x,float a,float b);

float degreesToRadians(float angle);

/**
 * Displace x using a cosine function dependent
 * on p.
 * The displacement is in the range [-r,r]
 * and repeats with frequency f over p
 */
float displace(float x,float p,float f,float r);

int nearestPOT(float num);

float saturate(float x);

float smoothstep(float e0,float e1,float x);

float radiansToDegrees(float angle);

/**
 * returns a random in the range [0,1[,
 * with probability P that the bit is set
 */
bool randomBit(float P);

/**
 * returns a random in the range [0,1[
 */
float randomFloat();

/**
 * returns a random in the range [a,b[
 */
float randomFloatInRange(float a,float b);

/**
 * returns a random in the range [-1,1[
 */
float randomSignedFloat();

/**
 * returns a random int in the range [0,max[
 */
int randomInt(int max);

float screenRatio(float distance,
				  float radius,
				  float viewingAngle);

/* max with support for overriding NaN */
float xmax(float a,float b);

/**
 * min with support for overriding NaN
 */
float xmin(float a,float b);
