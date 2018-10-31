#include "pch.h"
#define _STDCALL_SUPPORTED

#include <GL/glut.h>

static int left_shoulder = 0, left_elbow = 0;
static int right_shoulder = 0, right_elbow = 0;
static int turn = 0;//旋转

void init() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(1.0, 0.0, 0.0);
	glPushMatrix();
	glRotatef((GLfloat)turn, 0.0, 1.0, 0.0);
	//左前臂shoulder
	glTranslatef(0.5, 1.7, 0.0);
	glRotatef((GLfloat)left_shoulder, 0.0, 0.0, 1.0);
	glTranslatef(0.5, 0.0, 0.0);
	glPushMatrix();
	glScalef(1.3, 0.4, 1.0);
	glutSolidCube(0.5);
	glPopMatrix();

	//左前臂elbow
	glTranslatef(0.3, 0.0, 0.0);
	glRotatef((GLfloat)left_elbow, 0.0, 0.0, 1.0);
	glTranslatef(0.3, 0.0, 0.0);
	glPushMatrix();
	glScalef(1.0, 0.4, 1.0);
	glutSolidCube(0.5);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glRotatef((GLfloat)turn, 0.0, 1.0, 0.0);
	//右前臂shoulder
	glTranslatef(-0.5, 1.7, 0.0);
	glRotatef((GLfloat)right_shoulder, 0.0, 0.0, 1.0);
	glTranslatef(-0.5, 0.0, 0.0);
	glPushMatrix();
	glScalef(1.3, 0.4, 1.0);
	glutSolidCube(0.5);
	glPopMatrix();

	//右前臂elbow
	glTranslatef(-0.3, 0.0, 0.0);
	glRotatef((GLfloat)right_elbow, 0.0, 0.0, 1.0);
	glTranslatef(-0.3, 0.0, 0.0);
	glPushMatrix();
	glScalef(1.0, 0.4, 1.0);
	glutSolidCube(0.5);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glRotatef((GLfloat)turn, 0.0, 1.0, 0.0);
	//躯干
	glTranslatef(0.0, 1.0, 0.0);
	glColor3f(0.0, 0.5, 1.0);
	glPushMatrix();
	glScalef(1.3, 2.0, 0.5);
	glutSolidCube(1.0);
	glPopMatrix();

	//头
	glTranslatef(0.0, 1.25, 0.0);
	glColor3f(1.0, 0.6, 0.2);
	glPushMatrix();
	glScalef(0.5, 0.5, 0.5);
	glutSolidSphere(0.8, 50, 10);
	glPopMatrix();
	glPopMatrix();

	//右腿
	glPushMatrix();
	glRotatef((GLfloat)(turn + 180), 0.0, 1.0, 0.0);
	//提起右大腿
	glTranslatef(0.375, 0.0, 0.0);
	glRotatef((GLfloat)left_shoulder, 1.0, 0.0, 0.0);
	glTranslatef(0.0, -0.5, 0.0);
	glColor3f(0.8, 1.0, 0.2);
	glPushMatrix();
	glScalef(0.5, 1.0, 0.5);
	glutSolidCube(1.0);
	glPopMatrix();

	//提起右小腿
	glTranslatef(0.0, -0.5, 0.0);
	glRotatef((GLfloat)left_elbow, 1.0, 0.0, 0.0);
	glTranslatef(0.0, -0.5, 0.0);

	glColor3f(0.5, 0.1, 0.8);
	glPushMatrix();
	glScalef(0.5, 1.0, 0.5);
	glutSolidCube(1.0);
	glPopMatrix();

	//右脚
	glTranslatef(0.0, -0.5, -0.1);
	glColor3f(0.5, 0.2, 1.0);
	glPushMatrix();
	glScalef(0.5, 0.1, 0.7);
	glutSolidCube(1.0);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glRotatef((GLfloat)(turn + 180), 0.0, 1.0, 0.0);

	//左大腿
	glTranslatef(-0.375, 0.0, 0.0);
	glRotatef((GLfloat)right_shoulder, 1.0, 0.0, 0.0);
	glTranslatef(0.0, -0.5, 0.0);

	glColor3f(0.8, 1.0, 0.2);
	glPushMatrix();
	glScalef(0.5, 1.0, 0.5);
	glutSolidCube(1.0);
	glPopMatrix();

	//左小腿
	glTranslatef(0.0, -0.5, 0.0);
	glRotatef((GLfloat)right_elbow, 1.0, 0.0, 0.0);
	glTranslatef(0.0, -0.5, 0.0);
	glColor3f(0.5, 0.1, 0.8);
	glPushMatrix();
	glScalef(0.5, 1.0, 0.5);
	glutSolidCube(1.0);
	glPopMatrix();

	//左脚
	glTranslatef(0.0, -0.5, -0.1);
	glColor3f(0.5, 0.2, 1.0);
	glPushMatrix();
	glScalef(0.5, 0.1, 0.7);
	glutSolidCube(1.0);
	glPopMatrix();

	glPopMatrix();

	glutSwapBuffers();
}

void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -5.0);
}

void keyboard(unsigned char key, int x, int y) {
	/*
	//限制手脚活动空间
	if(left_shoulder>180) left_shoulder = 180;
	else if(left_shoulder<0) left_shoulder = 0;
	if(left_elbow>180) left_elbow = 180;
	else if(left_elbow<0) left_elbow = 0;
	*/
	switch (key) {
	case ';':
		left_shoulder = (left_shoulder + 5) % 360;
		glutPostRedisplay();
		break;
	case 'k':
		left_shoulder = (left_shoulder - 5) % 360;
		glutPostRedisplay();
		break;
	case 'o':
		left_elbow = (left_elbow + 5) % 360;
		glutPostRedisplay();
		break;
	case 'l':
		left_elbow = (left_elbow - 5) % 360;
		glutPostRedisplay();
		break;
	case 'a':
		right_shoulder = (right_shoulder + 5) % 360;
		glutPostRedisplay();
		break;
	case 'd':
		right_shoulder = (right_shoulder - 5) % 360;
		glutPostRedisplay();
		break;
	case 'w':
		right_elbow = (right_elbow + 5) % 360;
		glutPostRedisplay();
		break;
	case 's':
		right_elbow = (right_elbow - 5) % 360;
		glutPostRedisplay();
		break;
	case 'f':
		turn = (turn + 5) % 360;
		glutPostRedisplay();
		break;
	case 'j':
		turn = (turn - 5) % 360;
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GL_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 80);
	glutCreateWindow("robot");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}
