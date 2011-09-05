/*   ppmRead.h
	 Read PPM images into memory for use by OpenGL
	 M. Wainer, 1999
*/
#ifndef ppmOpenGL_H
#define ppmOpenGL_H
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <GL/glut.h>

/* ------------------------ prototypes  ---------------------- */
void skipComment(FILE *fin);
GLubyte *readPPM(FILE *fin, GLsizei *wid, GLsizei *ht);

#endif
