//#pragma once

//#include "Engine.h"

#ifndef Engine_h
#define Engine_h


class arrowCircle {
public:
	arrowCircle();
	float posx, radius, posy, speed;
	int angle_i, angle_r;
	void go(float main_circle_radius);
	void draw();
	bool Launch, DONE;
};

#endif // !Engine_h