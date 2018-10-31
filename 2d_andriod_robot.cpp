#include "pch.h"
#include <gl/glut.h>
#include <math.h>

int i;
const GLfloat PI = 3.1415926536f;
const int n = 1000;
const GLfloat eyeR = 0.025f; //radius of eye
const GLfloat faceR = 0.3f; //radius of face
const GLfloat bodyR = 0.05f; //radius of the corner of body
const GLfloat limbR = 0.06f; //radius of limb in both ends

void drawLimb(void) {
	//draw a half circle at one end
	glBegin(GL_POLYGON);
	for (i = 0; i < n; i++) {
		glVertex2f(limbR * cos(2 * PI / n * i), limbR * sin(2 * PI / n * i));
	}
	glEnd();

	//draw a rectangle
	glTranslatef(-0.06f, 0.0f, 0.0f);
	glRectf(0.0f, 0.0f, 0.12f, -0.3f);
	glEnd();

	//draw a half circle at the other end
	glTranslatef(0.06f, -0.3f, 0.0f);
	glBegin(GL_POLYGON);
	for (i = 0; i < n; i++) {
		glVertex2f(limbR * cos(2 * PI / n * i), limbR * sin(2 * PI / n * i));
	}
	glEnd();
	glFlush();
}

void drawHands(void)
{
	glLoadIdentity();
	glTranslatef(-0.38f, 0.2f, 0.0f);
	drawLimb();

	glLoadIdentity();
	glTranslatef(0.38f, 0.2f, 0.0f);
	drawLimb();
}

void drawBody(void)
{
	glLoadIdentity();

	//draw a rectangle first
	glTranslatef(-0.3f, 0.25f, 0.0f);
	glRectf(0.0f, 0.0f, 0.6f, -0.45f);
	glEnd();

	//draw a half circle at the left bottom
	glTranslatef(0.05f, -0.45f, 0.0f);
	glBegin(GL_POLYGON);
	for (i = 0; i < n; i++) {
		if (sin(2 * PI / n * i) < 0) {
			glVertex2f(bodyR * cos(2 * PI / n * i), bodyR * sin(2 * PI / n * i));
		}
	}
	glEnd();

	//draw a half circle at the right bottom
	glTranslatef(0.5f, 0.0f, 0.0f);
	glBegin(GL_POLYGON);
	for (i = 0; i < n; i++) {
		if (sin(2 * PI / n * i) < 0) {
			glVertex2f(bodyR * cos(2 * PI / n * i), bodyR * sin(2 * PI / n * i));
		}
	}
	glEnd();

	//draw the bottom rectangle
	glRectf(0.0f, 0.0f, -0.5f, -0.05f);
	glEnd();

	glFlush();
}


void drawLegs(void)
{
	glLoadIdentity();
	glTranslatef(-0.11f, -0.08f, 0.0f);
	drawLimb();

	glLoadIdentity();
	glTranslatef(0.11f, -0.08f, 0.0f);
	drawLimb();

}

void drawLine(void) {
	glLineWidth(5.0f);

	glBegin(GL_LINES);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(0.0f, 0.15f);
	glEnd();

	glFlush();
}

void drawEye(void) {
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_POLYGON);
	for (i = 0; i < n; i++) {
		glVertex2f(eyeR * cos(2 * PI / n * i), eyeR * sin(2 * PI / n * i));
	}
	glEnd();
	glColor3ub(164, 202, 57);

	glFlush();
}

void drawFaceShape(void) {
	glBegin(GL_POLYGON);

	for (i = 0; i < n; i++) {
		if (sin(2 * PI / n * i) >= 0) {
			glVertex2f(faceR * cos(2 * PI / n * i), faceR * sin(2 * PI / n * i));
		}
	}
	glEnd();
	glFlush();
}

void drawFace(void)
{
	glLoadIdentity();
	glTranslatef(0.0f, 0.27f, 0.0f);
	drawFaceShape();//draw the overall shape of face

	//draw left eye
	glLoadIdentity();
	glTranslatef(-0.13f, 0.42f, 0.0f);
	drawEye();

	//draw right eye
	glLoadIdentity();
	glTranslatef(0.13f, 0.42f, 0.0f);
	drawEye();

	//draw left line
	glLoadIdentity();
	glTranslatef(-0.13f, 0.5f, 0.0f);
	glRotated(30.0f, 0.0f, 0.0f, 1.0f);
	drawLine();

	//draw right line
	glLoadIdentity();
	glTranslatef(0.13f, 0.5f, 0.0f);
	glRotated(-30.0f, 0.0f, 0.0f, 1.0f);
	drawLine();


}

void drawRobot(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);//set background color to white
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();
	glColor3ub(164, 202, 57);//color of robot

	drawFace();
	drawBody();
	drawHands();
	drawLegs();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);
	glutCreateWindow("Android Robot");
	glutDisplayFunc(drawRobot);
	glutMainLoop();

	return 0;
}
