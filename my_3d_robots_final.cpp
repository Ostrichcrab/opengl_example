#include"pch.h"
#include <GL/glut.h>   
#include <stdio.h>    
#include <string.h>    
#include <stdlib.h>   
#include <math.h> 

static int shoulder1 = 0;
static int shoulder2 = 0;
static int hand = 0;
static int turn1 = 0;
static int tag = 0;
double xxx = 0.0;
int flag = 0;
static int turn = 0;//转弯
static float forward = 0;//前进
static float elbow = 0, z = 0;
int w;
int h;
int font = (int)GLUT_BITMAP_8_BY_13;
char s[30];
int frame, timeOwn, timebase = 0;


static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;
//是否停止转动
bool IsStop = false;
//光照  使用光源
GLfloat lightPos[] = { 1.0f, 0.0f, -1.0f, 0.0f };
GLfloat specular[] = { 1.0f, 1.0f, 1.0f, -1.0f };//反射光
GLfloat specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };//a
GLfloat ambientLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };//环绕光
GLfloat spotDir[] = { 0.0f, 0.0f, -1.0f };
GLboolean bEdgeFlag = TRUE;



void setOrthographicProjection();
void Draw();
//设置背景
void SetupRC(void)
{
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, ambientLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);


	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 30.0f);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 20.0f);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);


	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
	glMateriali(GL_FRONT, GL_SHININESS, 8);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}
#define MAX_COORD    2


void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glShadeModel(GL_SMOOTH);
	if (IsStop == false)
	{
		turn = (turn - 5) % 360;
		if (forward < 2)
		{
			turn1 = turn;
			forward = forward - 0.04*sin((GLfloat)turn1 / 360 * 3.14 * 2);
			z = z - 0.05*cos((GLfloat)turn1 / 360 * 3.14 * 2);

			if (tag == 0) {
				shoulder1 = (shoulder1 + 3);
				shoulder2 = (shoulder2 - 3);
				if (shoulder1 >= 0) { elbow = elbow - 1.2; }
				else { elbow = elbow + 1.2; }
			}
			else
			{
				shoulder1 = (shoulder1 - 3);
				shoulder2 = (shoulder2 + 3);
				if (shoulder1 >= 0) { elbow = elbow + 1.25; }
				else { elbow = elbow - 1.2; }
			}
			if (shoulder1 > 30) {
				tag = 1;
			}
			if (shoulder1 < -30) {
				tag = 0;
			}
		}
		else
		{
			turn1 = turn;
			forward = forward + 0.04*sin((GLfloat)turn1 / 360 * 3.14 * 2);
			z = z + 0.05*cos((GLfloat)turn1 / 360 * 3.14 * 2);
			if (tag == 0) {
				shoulder1 = (shoulder1 - 3);
				shoulder2 = (shoulder2 + 3);
			}
			else
			{
				shoulder1 = (shoulder1 + 3);
				shoulder2 = (shoulder2 - 3);
			}
			if (shoulder1 > 30)
			{
				tag = 0;
			}
			if (shoulder1 < -30)
			{
				tag = 1;
			}
		}
	}

	glBegin(GL_QUADS);
	glColor3ub(0, 32, 0);
	glVertex3f(8.0f, -3.0f, -12.0f);
	glVertex3f(-8.0f, -3.0f, -12.0f);
	glColor3ub(0, 255, 0);
	glVertex3f(-8.0f, -3.0f, 4.0f);
	glVertex3f(8.0f, -3.0f, 4.0f);
	glEnd();
	//机器人运动
	glPushMatrix();
	glTranslatef(forward, 0.0 , z); //前进  
	glRotatef((GLfloat)turn, 0.0, 1.0, 0.0);
	//Something();



	glTranslatef(0.375, 0.0+xxx , 0.0);//提起右大腿
	glRotatef((GLfloat)shoulder2, 1.0, 0.0, 0.0);


	glPushMatrix();
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDir);
	//画一个光源
	glColor3ub(255, 0, 0);
	glColor3ub(0, 0, 255);
	glTranslatef(lightPos[0], lightPos[1], lightPos[2]);


	//glutWireCone(0.3f, 0.3f, 10, 10);
	glPushAttrib(GL_LIGHTING_BIT);
	glDisable(GL_LIGHTING);
	glColor3ub(255, 255, 0);
	glColor3ub(0, 0, 255);
	//glutWireSphere(0.1f, 10.0f, 10);
	glPopAttrib();
	glPopMatrix();


	glTranslatef(0.0, -0.5, 0.0);
	glColor3f(0.8, 1.0, 0.2);
	glColor3ub(0, 0, 255);
	glPushMatrix();
	glScalef(0.5, 1.0, 0.5);
	glutWireCube(1.0);
	glPopMatrix();

	glTranslatef(0.0, -0.5, 0.0);//提起右小腿   
	glRotatef((GLfloat)elbow, 1.0, 0.0, 0.0);
	glTranslatef(0.0, -1.0 , 0.0);

	glColor3f(0.5, 0.1, 0.8);
	glColor3ub(0, 0, 255);
	glPushMatrix();
	glScalef(0.5, 2.0, 0.5);
	glutWireCube(1.0);
	glPopMatrix();

	glTranslatef(0.0, -1.0 , -0.1);//右脚   
	glColor3f(0.5, 0.2, 1.0);
	glColor3ub(0, 0, 255);
	glPushMatrix();
	glScalef(0.5, 0.1, 0.7);
	glutWireCube(1.0);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(forward, 0.0 , z);
	glRotatef((GLfloat)turn, 0.0, 1.0, 0.0);

	glTranslatef(-0.375, 0.0+xxx , 0.0);//左大腿   
	glRotatef((GLfloat)shoulder1, 1.0, 0.0, 0.0);
	glTranslatef(0.0, -0.5 , 0.0);

	glColor3f(0.8, 1.0, 0.2);
	glColor3ub(0, 0, 255);
	glPushMatrix();
	glScalef(0.5, 1.0, 0.5);
	glutWireCube(1.0);
	glPopMatrix();


	glTranslatef(0.0, -0.5 , 0.0);//左小腿   
	glRotatef((GLfloat)elbow, 1.0, 0.0, 0.0);
	glTranslatef(0.0, -1.0 , 0.0);

	glColor3f(0.5, 0.1, 0.8);
	glColor3ub(0, 0, 255);
	glPushMatrix();
	glScalef(0.5, 2.0, 0.5);//缩放四方体
	glutWireCube(1.0);//画四方体  
	glPopMatrix();


	glTranslatef(0.0, -1.0 , -0.1);//左脚   
	glColor3f(0.5, 0.2, 1.0);
	glColor3ub(0, 0, 255);
	glPushMatrix();
	glScalef(0.5, 0.1, 0.7);
	glutWireCube(1.0);
	glPopMatrix();

	glPopMatrix();

	glPushMatrix();
	glTranslatef(forward, 0.0 , z);
	glRotatef((GLfloat)turn, 0.0, 1.0, 0.0);

	glTranslatef(0.0, 1.0+xxx , 0.0);//躯干   
	
	glColor3f(0.5, 0.5, 1.0);
	glColor3ub(0, 0, 255);
	glPushMatrix();
	glScalef(1.4, 2.0, 0.5);
	glutWireCube(1.0);
	glPopMatrix();

	glTranslatef(0.0, 1.25 , 0.0);//头    
	glColor3f(1.0, 0.3, 0.2); 
	glColor3ub(0, 0, 255);
	glPushMatrix();
	glScalef(0.5, 0.5, 0.5);
	glutWireCube(1.0);
	glPopMatrix();

	///////////////////////////帽子



	glRotatef((GLfloat)90, 1.0, 0.0, 0.0);

	glTranslatef(0.0, 0.0 , -0.50);

	glColor3f(0.5, 0.5, 1.0);
	glColor3ub(0, 0, 255);
	glPushMatrix();
	glScalef(1.4, 1.0, 0.1);
	glutWireSphere(1.0, 5, 5);
	glPopMatrix();

	///////////////////////////





	///////////////////////////披风



	glRotatef((GLfloat)60, 1.0, 0.0, 0.0);

	glTranslatef(0.0, 3.0, 0.0);

	glColor3f(0.5, 0.5, 1.0);
	glColor3ub(0, 0, 255);
	glPushMatrix();
	glScalef(1.4, 4.0, 0.1);
	glutWireCube(1);
	glPopMatrix();

	///////////////////////////



	glPopMatrix();

	glPushMatrix();
	glTranslatef(forward, 0.0 , z);
	glRotatef((GLfloat)turn, 0.0, 1.0, 0.0);


	glTranslatef(0.85, 1.25+xxx , 0.0);//右臂   
	glRotatef((GLfloat)shoulder1, 1.0, 0.0, 0.0);
	glTranslatef(0.0, -0.5, 0.0);

	glColor3f(1.0, 0.0, 1.0);
	glColor3ub(0, 0, 255);
	glPushMatrix();
	glScalef(0.3, 2.3, 0.4);
	glutWireCube(1.0);
	glPopMatrix();
	//////////////////剑身
	glTranslatef(0.5, -1.75, 0.0);
	glRotatef((GLfloat)30.0, 1.0, 1.0, 1.0);
	glPushMatrix();
	glScalef(0.3, 2.9, 0.1);
	glutWireCube(1.0);
	glPopMatrix();
	//////////////////
	//////////////////剑把
	glTranslatef(0.0, 0.75, 0.0);
	glRotatef((GLfloat)10.0, 1.0, 1.0, 1.0);
	glPushMatrix();
	glScalef(0.93, 0.2, 0.1);
	glutWireCube(1.0);
	glPopMatrix();
	//////////////////
	////////////////// 剑尖尖
	glTranslatef(-0.20, -2.20 , 0.2);
	glRotatef((GLfloat)90, 1.0, 0.0, 0.0);
	glPushMatrix();
	glScalef(-0.56, 0.0, 0.5);
	glutWireCone(0.30f, 1.1f, 2, 2);
	glPopMatrix();
	//////////////////
	glPopMatrix();
	glPushMatrix();
	glTranslatef(forward, 0.0, z);
	glRotatef((GLfloat)turn, 0.0, 1.0, 0.0);

	glTranslatef(-0.85, 1.25+xxx, 0.0);//左臂   
	glRotatef((GLfloat)shoulder2, 1.0, 0.0, 0.0);
	glTranslatef(0.0, -0.5, 0.0);

	glColor3f(1.0, 0.0, 1.0);
	glColor3ub(0, 0, 255);
	glPushMatrix();
	glScalef(0.3, 2.3, 0.4);
	glutWireCube(1.0);
	glPopMatrix();


	glPopMatrix();


	glutSwapBuffers();
}

void reshape(int w1, int h1)
{
	w = w1;
	h = h1;
	glViewport(0, 0, (GLsizei)w1, (GLsizei)h1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0, (GLfloat)w1 / (GLfloat)h1, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0 , -8.0);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'w': //向后走 
		turn1 = turn;
		forward = forward - 0.04*sin((GLfloat)turn1 / 360 * 3.14 * 2);
		z = z - 0.05*cos((GLfloat)turn1 / 360 * 3.14 * 2);

		if (tag == 0) {
			shoulder1 = (shoulder1 + 3);
			shoulder2 = (shoulder2 - 3);
			if (shoulder1 >= 0) { elbow = elbow - 1.2; }
			else { elbow = elbow + 1.2; }
		}
		else
		{
			shoulder1 = (shoulder1 - 3);
			shoulder2 = (shoulder2 + 3);
			if (shoulder1 >= 0) { elbow = elbow + 1.25; }
			else { elbow = elbow - 1.2; }
		}
		if (shoulder1 > 30) {
			tag = 1;
		}
		if (shoulder1 < -30) {
			tag = 0;
		}
		IsStop = true;
		glutPostRedisplay();
		break;
	case 's': //向前走 
		turn1 = turn;
		forward = forward + 0.04*sin((GLfloat)turn1 / 360 * 3.14 * 2);
		z = z + 0.05*cos((GLfloat)turn1 / 360 * 3.14 * 2);
		if (tag == 0) {
			shoulder1 = (shoulder1 - 3);
			shoulder2 = (shoulder2 + 3);
		}
		else
		{
			shoulder1 = (shoulder1 + 3);
			shoulder2 = (shoulder2 - 3);
		}
		if (shoulder1 > 30) {
			tag = 0;
		}
		if (shoulder1 < -30) {
			tag = 1;
		}
		IsStop = true;
		glutPostRedisplay();
		break;
	case 'd'://右转
		turn = (turn - 5) % 360;
		glutPostRedisplay();
		IsStop = true;
		break;
	case 'a'://左转
		turn = (turn + 5) % 360;
		glutPostRedisplay();
		IsStop = true;
		break;
	case 'l':
		shoulder1 = (shoulder1 + 2) % 360;
		//shoulder2 = (shoulder2 - 4) % 360;
		glutPostRedisplay();
		IsStop = true;
		break;
	case 'L':
		shoulder1 = (shoulder1 - 5) % 360;
		//shoulder2 = (shoulder2 + 10) % 360;
		glutPostRedisplay();
		IsStop = true;
		break;
	case 'P':
		IsStop = false;
		break;
	case 'p':
		IsStop = false;
		break;
	case '1':
		exit(0);
		break;
	case 'J':
	case 'j': 
		
		if (flag == 0) xxx += 0.5, shoulder1 += 34;
		if (xxx >= 2.0) flag = 1;
		if (flag == 1) xxx -= 0.5, shoulder1 -= 34;
		if (xxx <= 0.0) flag = 0;
		glutPostRedisplay();
		break;
	default:
		break;
	}
}
//设置视觉角度  
void setOrthographicProjection()
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);
	glScalef(1, -1, 1);
	glTranslatef(0, -h, 0);
	glMatrixMode(GL_MODELVIEW);
}
void resetPerspectiveProjection()
{
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}
//光源的坐标变化
void SpecialKeys(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)
		xRot -= 5.0f;
	if (key == GLUT_KEY_DOWN)
		xRot += 5.0f;
	if (key == GLUT_KEY_LEFT)
		yRot -= 5.0f;
	if (key == GLUT_KEY_RIGHT)
		yRot += 5.0f;
	if (key > 356.0f)
		xRot = 0.0f;
	if (key < -1.0f)
		xRot = 355.0f;
	if (key > 356.0f)
		yRot = 0.0f;
	if (key < -1.0f)
		yRot = 355.0f;
	glutPostRedisplay();
}
//鼠标事件
void Mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)//鼠标按下
	{
		if (x < 0)
		{
			//向左旋转
			yRot -= 5.0f;
		}
		else if (x >= 0)
		{
			//向右旋转
			yRot += 5.0f;
		}
		else if (y >= 0)
		{
			//向上旋转
			xRot -= 5.0f;
		}
		else if (y < 0)
		{
			//向下旋转
			xRot += 5.0f;
		}
		if (xRot > 356.0f)
			xRot = 0.0f;
		if (xRot < -1.0f)
			xRot = 355.0f;
		if (yRot > 356.0f)
			yRot = 0.0f;
		if (yRot < -1.0f)
			yRot = 355.0f;
		glutPostRedisplay();
	}
}
//时间函数,定时刷新
void TimerFunction(int value)
{
	display();
	glutPostRedisplay();
	glutTimerFunc(33, TimerFunction, 1);
}

void Draw() {
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, 0.0f);
	for (int z = 0; z < 20; z++) {
		float zStart = 100.0f - z * 10.0f;
		for (int x = 0; x < 20; x++) {
			float xStart = x * 10.0f - 100.0f;
			if ((z % 2) ^ (x % 2)) {
				glColor4ub(41, 41, 41, 255);
			}
			else {
				glColor4ub(200, 200, 200, 255);
			}
			glVertex3f(xStart, -1.0f, zStart);
			glVertex3f(xStart + 10.0f, -1.0f, zStart);
			glVertex3f(xStart + 10.0f, -1.0f, zStart - 10.0f);
			glVertex3f(xStart, -1.0f, zStart - 10.0f);
		}
	}
	glEnd();
}

//主函数
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("一蓑烟雨任平生");
	SetupRC();
	glutDisplayFunc(display);

	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(SpecialKeys);
	glutMouseFunc(Mouse);
	//glutTimerFunc(33, TimerFunction, 1);
	//glutIdleFunc(display); 

	glutMainLoop();
	return 0;
}
