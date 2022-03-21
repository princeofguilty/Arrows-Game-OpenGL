//Jeff Chastine
#include <Windows.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>

using namespace std;

void OnDisplay();
void SetTransformations();

GLfloat fXPos = 0, fYPos = 0, fRot = 0;

void OnKeyPress(unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);
	switch (key)
	{
	case 'a':// a key
	case 'A':
		fXPos -= 0.5;
		break;
	case 'd':// d key
	case 'D':
		fXPos += 0.5;
		break;
	case 'w':// w key
	case 'W':
		fYPos += 0.5;
		break;
	case 's':// s key
	case 'S':
		fYPos -= 0.5;
		break;
	case 'e':
	case 'E':
		fRot += 0.1;
		break;
	case 'q':
	case 'Q':
		fRot -= 0.1;
		break;
	};
}
/**
Handles the special key press. This event is whenever
a special key is being pressed. */
void OnSpecialKeyPress(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:// Left function key
		fXPos -= 0.5;
		break;
	case GLUT_KEY_RIGHT:// Right function key
		fXPos += 0.5;
		break;
	case GLUT_KEY_UP:// Up function key
		fYPos += 0.5;
		break;
	case GLUT_KEY_DOWN:// Down function key
		fYPos -= 0.5;
		break;
	};
}


void InitGraphics(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	//Create an 800x600 window with its top-left corner at pixel (100, 100)
	glutInitWindowPosition(100, 100); //pass (-1, -1) for Window-Manager defaults
	glutInitWindowSize(800, 600);
	glutCreateWindow("OpenGL Lab");
	//OnDisplay will handle the paint event
	glutDisplayFunc(OnDisplay);
	// here is the setting of the idle function
	glutIdleFunc(OnDisplay);
	// here is the setting of the key function
	glutKeyboardFunc(OnKeyPress);
	glutSpecialFunc(OnSpecialKeyPress);
	SetTransformations();
	glutMainLoop();
}
/**
Sets the logical coordinate system we will use to specify
our drawings.
*/
void SetTransformations()
{
	//set up the logical coordinate system of the window: [-100, 100] x[-100, 100]
		glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60,
		(double)800 / 600,
		0.01,
		400);
	glEnable(GL_DEPTH_TEST);
	// set the camera here

}
/**
Handles the paint event. This event is triggered whenever
our displayed graphics are lost or out-of-date.
ALL rendering code should be written here.
*/

void DrawSquare()
{
	glBegin(GL_QUADS);
	glVertex2f(-.5f, -.5f);
	glVertex2f(.5f, -.5f);
	glVertex2f(.5f, .5f);
	glVertex2f(-.5f, .5f);
	glEnd();
}

void DrawCube()
{
	//+z square
	glPushMatrix();
	{
		glColor3f(1, 0, 0);
		glTranslatef(0, 0, .5f);
		DrawSquare();
	}
	glPopMatrix();
	//-z square
	glPushMatrix();
	{
		glColor3f(0, 1, 0);
		glTranslatef(0, 0, -.5f);
		DrawSquare();
	}
	glPopMatrix();
	//+x square
	glPushMatrix();
	{
		glColor3f(1, .5f, 0);
		glTranslatef(.5f, 0, 0);
		glRotatef(90, 0, 1, 0);
		DrawSquare();
	}
	glPopMatrix();
	//-x square
	glPushMatrix();
	{
		glColor3f(0, 1, .5f);
		glTranslatef(-.5f, 0, 0);
		glRotatef(90, 0, 1, 0);
		DrawSquare();
	}
	glPopMatrix();
	//+y square
	glPushMatrix();
	{
		glColor3f(.5f, 0, 1);
		glTranslatef(0, .5f, 0);
		glRotatef(90, 1, 0, 0);
		DrawSquare();
	}
	glPopMatrix();
	//-y square
	glPushMatrix();
	{
		glColor3f(1, 0, .5f);
		glTranslatef(0, -.5f, 0);
		glRotatef(90, 1, 0, 0);
		DrawSquare();
	}
	glPopMatrix();
}
void OnDisplay() 
{

	//set the background color to white
	glClearColor(0, 0, 0, 1);
	//fill the whole color buffer with the clear color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	{
		glScalef(7, 7, 7);
	// Inside OnPaint
	glRotatef(fRot, fXPos, fYPos, 0);
	DrawCube();
	//glutWireTeapot(2);//size = 2
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
		//cam pos
		0, 0, 40,
		//looking at
		0, 0, 0,
		//up dir
		0, 1, 0);

	glPopMatrix();
	glutSwapBuffers();
}

int main(int argc, char* argv[]) {
	InitGraphics(argc, argv);
	return 0;
}