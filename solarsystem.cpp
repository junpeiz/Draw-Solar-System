#define FREEGLUT_STATIC
#include <GL\freeglut.h>
#include <cstdlib>
#include <cmath>
#include <cstdio>
#include <iostream>

const double Pi = 3.14159;
const int n = 1000;
static int rotate_1 = 0, rotate_2 = 0, rotate_3 = 0, rotate_4 = 0, self_rotate = 0;

void init(void);
void Draw_solar_system(void);
void Draw_circuit(double R);
void Draw_vertical_circuit(double R);
void reshape(int w, int h);

void main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(50, 100);
	glutCreateWindow("A program to draw the solar system");

	init();
	glutDisplayFunc(Draw_solar_system);
	glutReshapeFunc(reshape);
	glutMainLoop();
}

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);  //开启深度测试（但注意要每次调用函数的时候清空深度缓存）
	glDepthFunc(GL_LESS);
}

void Draw_solar_system(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);  //清空深度缓存
	glColor3f(1, 0, 0);

	Draw_circuit(2.0);
	Draw_circuit(3.5);
	Draw_vertical_circuit(3.0);
	  
	glPushMatrix();           //push the matrix into stack
	glutSolidSphere(1, 20, 16);   //draw the sun

	glPushMatrix();
	glRotatef((GLfloat)(rotate_1 / 100.0), 0, 1, 0);  //行星1公转 
	glTranslatef(2, 0, 0); //将场景中的物体沿x轴正方向移动2个单位长（公转轨道半径）
	glRotatef((GLfloat)(self_rotate / 100.0), 0, 1, 0);  //行星自转
	glColor3f(0, 0.2, 0.6);
	glutSolidSphere(0.5, 20, 8);   //draw the planet

	glRotatef((GLfloat)(rotate_4 / 100.0), 0, 1, -1);   //卫星绕着行星1公转，而且轨道平面倾斜
	Draw_circuit(0.9);          //这里画的这个圆也会通过投影矩阵变换到当前坐标系下
								//也就是会自动成为绕着行星1的圆形
	glTranslatef(0.9, 0, 0);         //卫星公转半径
	glRotatef((GLfloat)(self_rotate / 100.0), 0, 1, 0);
	glColor3f(0.6, 0.2, 0);
	glutSolidSphere(0.15, 20, 8);
	glPopMatrix();   //如果这里没有经历过之前的Push和这句pop的话
					 //就会成为行星2绕着行星1转
	glPushMatrix();
	glRotatef((GLfloat)(rotate_2 / 100.0), 0, 1, 0);  //行星2绕太阳公转
	glTranslatef(3.5, 0, 0);     //行星2的公转半径
	glRotatef((GLfloat)(self_rotate / 100.0), 0, 1, 0);
	glColor3f(0, 1, 0);
	glutSolidSphere(0.5, 20, 8);

	glRotatef((GLfloat)(rotate_4 / 100.0), 0, 1, 1);   //卫星绕着行星2公转，而且轨道平面倾斜
	Draw_circuit(1.1);
	glTranslatef(1.1, 0, 0);         //卫星公转半径
	glRotatef((GLfloat)(self_rotate / 100.0), 0, 1, 0);
	glColor3f(0.6, 0.2, 0);
	glutSolidSphere(0.2, 20, 8);
	glPopMatrix();

	glPushMatrix();    //glpush和glpop的作用相当于把他们之间的这段东西限制在里面
	glRotatef((GLfloat)(rotate_3 / 100.0), 0, 0, 1);   //行星3绕太阳公转，且轨道竖直
	glTranslatef(3, 0, 0);
	glRotatef((GLfloat)(self_rotate / 100.0), 0, 1, 0);
	glColor3f(0.5, 0.5, 0.2);
	glutSolidSphere(0.4, 20, 8);
	glPopMatrix();

	glPopMatrix(); //pop the matrix
	glutSwapBuffers();
	glFlush();   

	rotate_1 = (rotate_1 + 5) % 36000;
	rotate_2 = (rotate_2 + 4) % 36000;
	rotate_3 = (rotate_3 + 3) % 36000;
	rotate_4 = (rotate_4 + 3) % 36000;
	self_rotate = (self_rotate + 3) % 36000;

	glutPostRedisplay();  //如果没有这句，要鼠标点一下才会动一下
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);   //设置机口
	glMatrixMode(GL_PROJECTION);  //指定哪一个矩阵是当前矩阵
	glLoadIdentity();
	gluPerspective(60, (GLfloat)w / (GLfloat)h, 1.0, 20);   //创建透视投影矩阵(fovy,aspect,zNear,zFar);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 5, 5, 0, 0, 0, 0, 1, 0);
}

void Draw_circuit(double R)
{
	int i;
	glBegin(GL_LINE_LOOP);
	for (i = 0; i < n; ++i)
		glVertex3f(R * cos(2 * Pi / n * i), 0, R * sin(2 * Pi / n * i));
	glEnd();
}

void Draw_vertical_circuit(double R)
{
	int i;
	glBegin(GL_LINE_LOOP);
	for (i = 0; i < n; ++i)
		glVertex3f(R * cos(2 * Pi / n * i), R * sin(2 * Pi / n * i), 0);
	glEnd();
}