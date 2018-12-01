#ifndef _DRAW_H_
#define _DRAW_H_

#include "utils.h"

void drawText(char *, GLint, GLint);  
void drawFilledCircle(GLfloat, GLfloat, GLfloat);
void drawLine(Point, Point);
void drawPath(std::vector<int>);
void drawAll();
void drawGenerationHUD();
void drawCommandHUD();
void drawDistanceHUD();
void drawCitiesHUD();

#endif
