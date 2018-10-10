//#include<GL\freeglut.h>
#include"pch.h"

#include <GL/glut.h>
#include <math.h>
//Five edges polygon.
//As less code as possible.

#include<stdlib.h>

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);


	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(-1.0, 0.0, 0.0);

	glColor3f(1.0, 1.0, 0.0);
	glVertex3f(0.0, 1.0, 0.0);

	glColor3f(1.0, 0.0, 1.0);
	glVertex3f(1.0, 0.0, 0.0);

	glColor3f(0.0, 1.0, 1.0);
	glVertex3f(0.5, -1.0, 0.0);

	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(-0.5, -1.0, 0.0);
	glEnd();
	glFlush();

}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(500, 300);
	glutInitWindowSize(500, 500);
	glutCreateWindow("SimplePentage");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}//#include<GL\freeglut.h>
#include"pch.h"

#include <GL/glut.h>
#include <math.h>
//Five edges polygon.
//As less code as possible.

#include<stdlib.h>

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);


	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(-1.0, 0.0, 0.0);

	glColor3f(1.0, 1.0, 0.0);
	glVertex3f(0.0, 1.0, 0.0);

	glColor3f(1.0, 0.0, 1.0);
	glVertex3f(1.0, 0.0, 0.0);

	glColor3f(0.0, 1.0, 1.0);
	glVertex3f(0.5, -1.0, 0.0);

	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(-0.5, -1.0, 0.0);
	glEnd();
	glFlush();

}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(500, 300);
	glutInitWindowSize(500, 500);
	glutCreateWindow("SimplePentage");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
