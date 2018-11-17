#ifndef _UI_H_
#define _UI_H_

#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glu.h>

void keyPressEvent(unsigned char, int, int);
void drawFilledCircle(GLfloat, GLfloat, GLfloat);
void drawLine(GLfloat, GLfloat, GLfloat, GLfloat);
void OnMouseClick(int, int, int, int);
void display();
void setup();

#endif
