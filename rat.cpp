#include <cstdlib>
#include <cmath>
#include "rat.h"
#include "glut.h"
#include "maze.h"
#include "graphics.h"



Rat::Rat() {
	mx = 0;
	my = 0;
	mdeg = 0;
	
}
void Rat::InitRat(double x, double y, double deg, Maze& maze) {
	mx = x;
	my = y;
	mdeg = deg;
	mMazePointer = maze;
}
	

void Rat::Draw()
{
	if (current_view == rat_view)
	{
		return; // drawing yourself in rat view looks bad.
	}
	glPushMatrix();
	glTranslated(mx, my, 0);
	glRotated(mdeg, 0, 0, 1);
	glScaled(.2, .2, 1.0);
	glColor3d(.75, .75, .75);
	/*DrawTriangle(.3, 0, -.3, .1, -.3, -.1);
	DrawCircle(.3, 0, .03);*/
	DrawCircle(0, 0, .5);
	DrawCircle(.6, 0, .3);
	DrawCircle(.6, .3, .2);
	DrawCircle(.6, -.3, .2);
	DrawCircle(.9, 0, .1);
	glPopMatrix();
	
}

void Rat::DrawTriangle(double x1, double y1, double x2, double y2, double x3, double y3)
{
	glBegin(GL_TRIANGLES);
	glVertex2d(x1, y1);
	glVertex2d(x2, y2);
	glVertex2d(x3, y3);
	glEnd();
}
void Rat::DrawCircle(double x, double y, double radius) {
	glBegin(GL_POLYGON);
	for (int i = 0; i < 32; i++)
	{
		double theta = (double)i / 32.0 * 2.0 * 3.1415926;
		double tempx = x + radius * cos(theta);
		double tempy = y + radius * sin(theta);
		glVertex2d(tempx, tempy);
	}
	glEnd();
}

void Rat::SpinLeft() {
	mdeg += .35;
}

void Rat::SpinRight() {
	mdeg -= .35;
}

double Rat::getDeg() {
	return mdeg;
}

double Rat::getDx() {
	double radians = mdeg * 3.14159265 / 180;
	double dx = cos(radians);
	return dx;
}

double Rat::getDy() {
	double radians = mdeg * 3.14159265 / 180;
	double dy = sin(radians);
	return dy;
}
void Rat::ScurryForward() {
	double radians = mdeg * 3.14159265 / 180;
	double dx = cos(radians);
	double dy = sin(radians);
	double speed = .001;

	if (mMazePointer.isSafe(mx + dx * speed, my + dy * speed, .5)) {

		 mx += dx * speed;
		 my += dy * speed;
	}
	if (mMazePointer.isSafe(mx, my + dy * speed, .2)) {
		my += dy * speed;
	}
	if (mMazePointer.isSafe(mx + dx * speed, my, .2)) {
		mx += dx * speed;
	}

}

double Rat::getX() {
	return mx;
}

double Rat::getY() {
	return my;
}

double Rat::getDir() {
	return mdeg;
}

void Rat::tiltUp()
{
}
