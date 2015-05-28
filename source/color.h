// Copyright T.E.A de Souza 2012-2015 - MIT LICENSE

#import <OpenGLES/ES1/gl.h>

typedef struct{
	
	GLfloat red,green,blue,alpha;
	
}c4f;

typedef struct{
	
	GLfloat red,green,blue,alpha;
	
}c3f;

c4f c4fMake(float r,float g,float b,float a);
c3f c3fMake(float r,float g,float b);

c4f c4fRandom();
c3f c3fRandom();

// ---------------------------------------------------

#define c4f_black	c4fMake(0, 0, 0, 1)
#define c4f_white	c4fMake(1, 1, 1, 1)
#define c4f_clear	c4fMake(0, 0, 0, 0)

#define c4f_red		c4fMake(1, 0, 0, 1)
#define c4f_green	c4fMake(0, 1, 0, 1)
#define c4f_blue	c4fMake(0, 0, 1, 1)

#define c4f_cyan	c4fMake(0, 1, 1, 1)
#define c4f_magenta	c4fMake(1, 0, 1, 1)
#define c4f_yellow	c4fMake(1, 1, 0, 1)

#define c4f_gray		c4fMake(0.50, 0.50, 0.50, 1)
#define c4f_lightgray	c4fMake(0.75, 0.75, 0.75, 1)
#define c4f_darkgray	c4fMake(0.25, 0.25, 0.25, 1)