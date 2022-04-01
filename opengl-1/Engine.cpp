#include "Engine.h"
#include <Windows.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>

void DrawCircle(float cx, float cy, float r, int num_segments);

arrowCircle::arrowCircle() {
	//draw(0);
	posx = 0, radius = 0.6, posy = -19 + radius,
		speed = 0.1;
	Launch = false;
	DONE = false;
}


void arrowCircle::draw(int c_angle) {
	if(speed != -1) // freeze position
		glRotatef(-angle, 0, 0, 1);
	else
		glRotatef(-angle, 0, 0, 1);

	DrawCircle(posx, posy, radius, 50);
	// draw its arrow
	if (speed == -1) {
		glBegin(GL_LINES);
		glVertex2f(posx, posy);
		glVertex2f(0, 0);
		glEnd();
	}

	if (speed != -1) // freeze position
		glRotatef(+angle, 0, 0, 1);
}
void arrowCircle::go(float main_circle_radius, int c_angle) {
	if (posy < 0 - main_circle_radius - 5 && DONE == false) {
		posx = 0;
		if(Launch)
			posy += speed;
		angle = c_angle;
	}
	else {
		if (Launch) {
			Launch = false;
			DONE = true;
			speed = -1;
		}
		angle++;
	}
}
