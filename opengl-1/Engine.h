//#pragma once

//#include "Engine.h"

#ifndef Engine_h
#define Engine_h


class arrowCircle {
public:
	arrowCircle();
	float posx, radius, posy, speed;
	int angle;
	void go(float main_circle_radius, int c_angle);
	void draw(int c_angle);
	bool Launch, DONE;
};

#endif // !Engine_h