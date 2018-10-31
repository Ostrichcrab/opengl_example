/* Interactive Figure Program from Chapter 5 using cylinders (quadrics) */
/* Style similar to robot program but here we must traverse tree to display */
/* Cylinders are displayed as filled and light/material properties */
/* are set as in sphere approximation program */
#include "pch.h"
#include <stdlib.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define TORSO_HEIGHT 5.0        //身体高度
#define UPPER_ARM_HEIGHT 3.0	//上臂高度
#define LOWER_ARM_HEIGHT 2.0	//下臂高度
#define UPPER_LEG_RADIUS  0.5	//小腿半径
#define LOWER_LEG_RADIUS  0.5	//大腿半径
#define LOWER_LEG_HEIGHT 2.0	//小腿高度
#define UPPER_LEG_HEIGHT 3.0	//大腿高度
#define UPPER_LEG_RADIUS  0.5	//上臂半径
#define TORSO_RADIUS 1.0		//身体半径
#define UPPER_ARM_RADIUS  0.5	//上臂半径
#define LOWER_ARM_RADIUS  0.5	//下臂半径
#define HEAD_HEIGHT 1.5			//头部高度
#define HEAD_RADIUS 1.0			//头部半径

typedef float point[3];

static GLfloat theta[11] = { 0.0,0.0,0.0,//旋转矩阵
							// 身体， 头x， 头y
							0.0,0.0,0.0,
	//lua,lla,rua
	0.0,180.0,0.0,
	//rla,rul,lll
	180.0,0.0 }; /* initial joint angles */
	//rul,rll
static GLint angle = 2;

GLUquadricObj *t, *h, *lua, *lla, *rua, *rla, *lll, *rll, *rul, *lul;//二次方程指针，用来生成物体

double size = 1.0;

void torso()//在世界坐标中心画身体
{
	glPushMatrix();
	glRotatef(-90.0, 1.0, 0.0, 0.0);//绕世界坐标x轴逆时针旋转90度
	gluCylinder(t, TORSO_RADIUS, TORSO_RADIUS, TORSO_HEIGHT, 10, 10);//画一个圆柱体，上面的旋转作用在其上
	glPopMatrix();
}

void head()//在世界坐标中心画头
{
	glPushMatrix();
	glTranslatef(0.0, 0.5*HEAD_HEIGHT, 0.0);//移动到半个头高，方便之后往身体上移动
	glScalef(HEAD_RADIUS, HEAD_HEIGHT, HEAD_RADIUS);//拉伸，y轴倍数更大
	gluSphere(h, 1.0, 10, 10);
	glPopMatrix();
}

void left_upper_arm()
{
	glPushMatrix();
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	gluCylinder(lua, UPPER_ARM_RADIUS, UPPER_ARM_RADIUS, UPPER_ARM_HEIGHT, 10, 10);
	glPopMatrix();
}

void left_lower_arm()
{
	glPushMatrix();
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	gluCylinder(lla, LOWER_ARM_RADIUS, LOWER_ARM_RADIUS, LOWER_ARM_HEIGHT, 10, 10);
	glPopMatrix();
}

void right_upper_arm()
{
	glPushMatrix();
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	gluCylinder(rua, UPPER_ARM_RADIUS, UPPER_ARM_RADIUS, UPPER_ARM_HEIGHT, 10, 10);
	glPopMatrix();
}

void right_lower_arm()
{
	glPushMatrix();
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	gluCylinder(rla, LOWER_ARM_RADIUS, LOWER_ARM_RADIUS, LOWER_ARM_HEIGHT, 10, 10);
	glPopMatrix();
}

void left_upper_leg()
{
	glPushMatrix();
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	gluCylinder(lul, UPPER_LEG_RADIUS, UPPER_LEG_RADIUS, UPPER_LEG_HEIGHT, 10, 10);
	glPopMatrix();
}

void left_lower_leg()
{
	glPushMatrix();
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	gluCylinder(lll, LOWER_LEG_RADIUS, LOWER_LEG_RADIUS, LOWER_LEG_HEIGHT, 10, 10);
	glPopMatrix();
}

void right_upper_leg()
{
	glPushMatrix();
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	gluCylinder(rul, UPPER_LEG_RADIUS, UPPER_LEG_RADIUS, UPPER_LEG_HEIGHT, 10, 10);
	glPopMatrix();
}

void right_lower_leg()
{
	glPushMatrix();
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	gluCylinder(rll, LOWER_LEG_RADIUS, LOWER_LEG_RADIUS, LOWER_LEG_HEIGHT, 10, 10);
	glPopMatrix();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glColor3f(1.0, 0.0, 1.0);//洋红

	glRotatef(theta[0], 0.0, 1.0, 0.0);//使身体可以旋转的函数
	torso();
	glPushMatrix();

	glTranslatef(0.0, TORSO_HEIGHT + 0.5*HEAD_HEIGHT, 0.0);//4 把头移动到身体上
	glRotatef(theta[1], 1.0, 0.0, 0.0);//3 绕x轴旋转的函数
	glRotatef(theta[2], 0.0, 1.0, 0.0);//2 绕y轴旋转的函数
	glTranslatef(0.0, -0.5*HEAD_HEIGHT, 0.0);//1 把头移动到坐标原点
	head();

	glPopMatrix();
	glPushMatrix();
	glTranslatef(-(TORSO_RADIUS + UPPER_ARM_RADIUS), 0.9*TORSO_HEIGHT, 0.0);//移动到身体左侧，0.9个身体处
	glRotatef(theta[3], 1.0, 0.0, 0.0);
	left_upper_arm();//左上臂

	glTranslatef(0.0, UPPER_ARM_HEIGHT, 0.0);//移到上臂上面
	glRotatef(theta[4], 1.0, 0.0, 0.0);
	left_lower_arm();//左小臂

	glPopMatrix();
	glPushMatrix();
	glTranslatef(TORSO_RADIUS + UPPER_ARM_RADIUS, 0.9*TORSO_HEIGHT, 0.0);
	glRotatef(theta[5], 1.0, 0.0, 0.0);
	right_upper_arm();//移动右上臂

	glTranslatef(0.0, UPPER_ARM_HEIGHT, 0.0);
	glRotatef(theta[6], 1.0, 0.0, 0.0);
	right_lower_arm();//移动右小臂

	glPopMatrix();
	glPushMatrix();
	glTranslatef(-(TORSO_RADIUS + UPPER_LEG_RADIUS), 0.1*UPPER_LEG_HEIGHT, 0.0);
	glRotatef(theta[7], 1.0, 0.0, 0.0);
	left_upper_leg();//左大腿

	glTranslatef(0.0, UPPER_LEG_HEIGHT, 0.0);
	glRotatef(theta[8], 1.0, 0.0, 0.0);
	left_lower_leg();//左小腿

	glPopMatrix();
	glPushMatrix();
	glTranslatef(TORSO_RADIUS + UPPER_LEG_RADIUS, 0.1*UPPER_LEG_HEIGHT, 0.0);
	glRotatef(theta[9], 1.0, 0.0, 0.0);
	right_upper_leg();//右大腿

	glTranslatef(0.0, UPPER_LEG_HEIGHT, 0.0);
	glRotatef(theta[10], 1.0, 0.0, 0.0);
	right_lower_leg();//右小腿

	glPopMatrix();
	glFlush();
	glutSwapBuffers();
}



void mouse(int btn, int state, int x, int y)
{//鼠标响应函数
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		theta[angle] += 5.0;//如果按下左键，相应的数值变大5度，相当于顺时针旋转5度
		if (theta[angle] > 360.0) theta[angle] -= 360.0;
	}
	if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) //按下右键，逆时针旋转5度
	{
		theta[angle] -= 5.0;
		if (theta[angle] < 360.0) theta[angle] += 360.0;
	}
	display();
}

void menu(int id)
{//菜单按钮
	if (id < 11) angle = id;//如果选择的是非第11个选项，设置旋转矩阵相应的下标
	if (id == 11) exit(0);//退出
}

void myReshape(int w, int h)
{
	glViewport(0, 0, w, h);//设置视口变换 标准设备坐标系->窗口坐标系

	glMatrixMode(GL_PROJECTION);//设置投影变换 视点坐标系->裁剪坐标系
	glLoadIdentity();
	if (w <= h)//如果宽小于高
		glOrtho(-10.0, 10.0, -10.0 * (GLfloat)h / (GLfloat)w,//设置视域体的left right bottom top near far
			10.0 * (GLfloat)h / (GLfloat)w, -10.0, 10.0);
	else
		glOrtho(-10.0 * (GLfloat)w / (GLfloat)h,
			10.0 * (GLfloat)w / (GLfloat)h, 0.0, 10.0, -10.0, 10.0);

	glMatrixMode(GL_MODELVIEW);//设置模型矩阵变换 确定几何对象在世界坐标系中的位置和方向 对象坐标系->世界坐标系
	glLoadIdentity();
}

void myinit()
{
	glEnable(GL_DEPTH_TEST); //开启深度缓存

	glClearColor(1.0, 1.0, 1.0, 1.0);//清除颜色
	glColor3f(1.0, 0.0, 0.0);

	/* allocate quadrics with filled drawing style */

	h = gluNewQuadric();//创建二次方程状态对象
	gluQuadricDrawStyle(h, GLU_LINE);//以二次方程状态作参数，传到绘制二次方程的函数
	t = gluNewQuadric();
	gluQuadricDrawStyle(t, GLU_LINE);//绘制成线框
	lua = gluNewQuadric();
	gluQuadricDrawStyle(lua, GLU_LINE);
	//gluQuadricDrawStyle(lua, GLU_POINT);//点集合
	//gluQuadricDrawStyle(lua, GLU_FILL);//实体集合
	//gluQuadricDrawStyle(lua, GLU_SILHOUETTE);//线模式
	lla = gluNewQuadric();
	gluQuadricDrawStyle(lla, GLU_LINE);
	rua = gluNewQuadric();
	gluQuadricDrawStyle(rua, GLU_LINE);
	rla = gluNewQuadric();
	gluQuadricDrawStyle(rla, GLU_LINE);
	lul = gluNewQuadric();
	gluQuadricDrawStyle(lul, GLU_LINE);
	lll = gluNewQuadric();
	gluQuadricDrawStyle(lll, GLU_LINE);
	rul = gluNewQuadric();
	gluQuadricDrawStyle(rul, GLU_LINE);
	rll = gluNewQuadric();
	gluQuadricDrawStyle(rll, GLU_LINE);
}

void main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("robot");
	myinit();//初始化，创建机器人各个部分
	glutReshapeFunc(myReshape);//注册重绘函数
	glutDisplayFunc(display);//注册显示函数
	glutMouseFunc(mouse);//注册鼠标响应事件

	glutCreateMenu(menu);//注册菜单
	glutAddMenuEntry("torso", 0);
	glutAddMenuEntry("head1", 1);
	glutAddMenuEntry("head2", 2);
	glutAddMenuEntry("right_upper_arm", 3);
	glutAddMenuEntry("right_lower_arm", 4);
	glutAddMenuEntry("left_upper_arm", 5);
	glutAddMenuEntry("left_lower_arm", 6);
	glutAddMenuEntry("right_upper_leg", 7);
	glutAddMenuEntry("right_lower_leg", 8);
	glutAddMenuEntry("left_upper_leg", 9);
	glutAddMenuEntry("left_lower_leg", 10);
	glutAddMenuEntry("quit", 11);
	glutAttachMenu(GLUT_MIDDLE_BUTTON);//菜单挂在中键上

	glutMainLoop();//进入事件循环
}
