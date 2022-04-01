#include <Windows.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>
#include "Engine.h"
#include <stdio.h>

//#define DOUBLE_BUFFER
#define SINGLE_BUFFER

arrowCircle* ac = NULL;

bool* onMouse;
int s_angle = 0;
bool EXIT = false;

float position = 0;

struct arrows_exist
{
	arrowCircle* arr[40];
	int counter = 0;
	void add(arrowCircle* a) {
		arr[counter++] = a;
	}
	void run() {
		for (int i = 0; i < counter; i++)
		{
			arr[i]->draw(s_angle);
			arr[i]->go(3, s_angle);
		}
	}
	arrowCircle pop() {
		return ac[counter];
	}

	void check() {
		for (int i = 0; i < counter; i++)
		{
			for (int j = i + 1; j < counter; j++)
			{
				if (abs(arr[i]->angle - arr[j]->angle) < 10) {
					printf("SCORE = %d\n", counter - 1);
					EXIT = true;
				}
			}
		}
	}
}ArrowsExist;

void RenderString(float x, float y, void* font, const unsigned char* str)
{
	//char* c;

	glRasterPos2f(x, y);

	glutBitmapString(font, str);
}

void DrawCircle(float cx, float cy, float r, int num_segments) {
	//GL_LINE_LOOP for unfilled circle
	//GL_TRIANGLE_FAN for filled circle
	glBegin(GL_TRIANGLE_FAN);
	for (int ii = 0; ii < num_segments; ii++) {
		float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle 
		float x = r * cosf(theta);//calculate the x component 
		float y = r * sinf(theta);//calculate the y component 
		glVertex2f(x + cx, y + cy);//output vertex 
	}
	glEnd();
}

void timer(int) {
	glutPostRedisplay();
	//if(!EXIT)
	glutTimerFunc(1000 / 60, timer, 0);
	if (position <= 18)
		position += 0.15;
	else if (position > -10)
		position -= 0.15;
	position = 0;

	glColor3f(1 - abs(position) / 14, 1 - abs(position) / 14, 1 - abs(position) / 24);
}

void init() {
	//glClearColor(0.1, 0.1, 0.1, 1); // change background color
	glClearColor(1.0, 246 / 255.0, 243 / 255.0, 0);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glLineWidth((GLfloat)3.0);


	glRotatef(s_angle++, 0, 0, 1);

	s_angle = s_angle % 360;
	glColor3f(0.1, 0.1, 0.1);

	glShadeModel(GL_SMOOTH);
	DrawCircle(0, 0, 3, 100);
	ArrowsExist.run();

	glColor3f(0., 0., 0.);
	//glRotatef(-angle, 0, 0, 1);
	if (!EXIT) {
		ac->draw(s_angle);
		ac->go(3, s_angle);
		if (ac->DONE == true) {
			ArrowsExist.add(ac);
			ac = new arrowCircle();
		}
	}
	if (!EXIT) 
		ArrowsExist.check();
	else
		ArrowsExist.counter--;

	if (EXIT && ArrowsExist.counter == 0) {
		EXIT = false;
	}

	onMouse = &ac->Launch;
	glColor3f(1, 1, 1);
	char a[10];
	sprintf(a, "%d", ArrowsExist.counter);
	RenderString(-1.0f, 0.03f, GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)a);
	glColor3f(0., 0., 0.);

#ifdef DOUBLE_BUFFER
	glutSwapBuffers();
#else
	glFlush();
#endif

	//if (EXIT)
	//	exit(0);


}

void reshape(int w, int h) {
	// set viewport && projection

	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-20, 20, -20, 20);
	glMatrixMode(GL_MODELVIEW);

}

void mouseClicks(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		*onMouse = true;
	}
}

int main(int argc, char** argv) {
	ac = new arrowCircle();
	glutInit(&argc, argv);
#ifdef DOUBLE_BUFFER
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
#else
	glutInitDisplayMode(GLUT_RGB);
#endif


	glutInitWindowPosition(200, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("hello");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	init(); // call some initial functions ex. background color

	glutTimerFunc(0, timer, 0);
	glutMouseFunc(mouseClicks);

	glutMainLoop();

	return 1;
}