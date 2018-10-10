#include"pch.h"
#include <GL/glut.h>
#include <math.h>
//As less code as possible.
#include<stdlib.h>
#include<iostream>
using namespace std;
void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
}
char ch; double x1=-0.5, x2=0.5, yy1=-0.5, y2=0.5;
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glRectf(x1, yy1, x2, y2);
	glFlush();

}

void mykeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'W':
	case 'w': yy1 += 0.1; y2 += 0.1;
		break;
	case 'S':
	case 's': yy1 -= 0.1; y2 -= 0.1;
		break;
	case 'a':
	case 'A': x1 -= 0.1; x2 -= 0.1;
		break;
	case 'D':
	case 'd': x1 += 0.1; x2 += 0.1; 
		break;
	}
	glutPostRedisplay();
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
	glutKeyboardFunc(mykeyboard);
	glutMainLoop();
	return 0;
}
