#include <Windows.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>
#include "Engine.h"

//#define DOUBLE_BUFFER
#define SINGLE_BUFFER

arrowCircle* ac = NULL;

bool* onMouse;
int angle=0;

float position = 0;

struct arrows_exist
{
	arrowCircle* arr[20];
	int counter=0;
	void add(arrowCircle* a) {
		arr[counter++] = a;
	}
	void run() {
		for (int i = 0; i < counter; i++)
		{
			arr[i]->draw();
			arr[i]->go(3);
		}
	}
	arrowCircle pop() {
		return ac[counter];
	}
}ArrowsExist;

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
	//glLoadIdentity();
	glLineWidth((GLfloat)3.0);

	glRotatef(1, 0, 0, 1);
	angle = angle % 360;
	glColor3f(0.1, 0.1, 0.1);

	glShadeModel(GL_SMOOTH);
	DrawCircle(0, 0, 3, 100);
	
	
	glColor3f(0.1, 0.1, 0.1);
	ac->draw();
	ac->go(3);
	if (ac->DONE == true) {
		ArrowsExist.add(ac);
		ac = new arrowCircle();
		ac->angle_i = ArrowsExist.pop().angle_i;
		
	}

	ArrowsExist.run();

	onMouse = &ac->Launch;

#ifdef DOUBLE_BUFFER
	glutSwapBuffers();
#else
	glFlush();
#endif



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