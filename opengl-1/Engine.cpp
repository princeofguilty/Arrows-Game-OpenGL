#include "Engine.h"
#include <Windows.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>

void DrawCircle(float cx, float cy, float r, int num_segments);

arrowCircle::arrowCircle() {
	draw();
	posx = 0, radius = 0.6, posy = -19 + radius,
		speed = 0.1, angle_i=0, angle_r=0;
	Launch = false;
	DONE = false;
}


void arrowCircle::draw() {
	glRotatef(-angle_i, 0, 0, 1);

	DrawCircle(posx, posy, radius, 50);
	// draw its arrow
	if (speed == -1) {
		glBegin(GL_LINES);
		glVertex2f(posx, posy);
		glVertex2f(0, 0);
		glEnd();
	}

	glRotatef(speed == -1 ? angle_r : angle_i, 0, 0, 1);
}
void arrowCircle::go(float main_circle_radius) {
	if (posy < 0 - main_circle_radius - 5 && DONE == false) {
		posx = 0;
		if(Launch)
			posy += speed;
		angle_i = ++angle_i % 360;
	}
	else {
		if (Launch) {
			Launch = false;
			DONE = true;
			speed = -1;
		}
		angle_r = ++angle_r % 360;
	}
}
