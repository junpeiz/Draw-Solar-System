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
	glEnable(GL_DEPTH_TEST);  //������Ȳ��ԣ���ע��Ҫÿ�ε��ú�����ʱ�������Ȼ��棩
	glDepthFunc(GL_LESS);
}

void Draw_solar_system(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);  //�����Ȼ���
	glColor3f(1, 0, 0);

	Draw_circuit(2.0);
	Draw_circuit(3.5);
	Draw_vertical_circuit(3.0);
	  
	glPushMatrix();           //push the matrix into stack
	glutSolidSphere(1, 20, 16);   //draw the sun

	glPushMatrix();
	glRotatef((GLfloat)(rotate_1 / 100.0), 0, 1, 0);  //����1��ת 
	glTranslatef(2, 0, 0); //�������е�������x���������ƶ�2����λ������ת����뾶��
	glRotatef((GLfloat)(self_rotate / 100.0), 0, 1, 0);  //������ת
	glColor3f(0, 0.2, 0.6);
	glutSolidSphere(0.5, 20, 8);   //draw the planet

	glRotatef((GLfloat)(rotate_4 / 100.0), 0, 1, -1);   //������������1��ת�����ҹ��ƽ����б
	Draw_circuit(0.9);          //���ﻭ�����ԲҲ��ͨ��ͶӰ����任����ǰ����ϵ��
								//Ҳ���ǻ��Զ���Ϊ��������1��Բ��
	glTranslatef(0.9, 0, 0);         //���ǹ�ת�뾶
	glRotatef((GLfloat)(self_rotate / 100.0), 0, 1, 0);
	glColor3f(0.6, 0.2, 0);
	glutSolidSphere(0.15, 20, 8);
	glPopMatrix();   //�������û�о�����֮ǰ��Push�����pop�Ļ�
					 //�ͻ��Ϊ����2��������1ת
	glPushMatrix();
	glRotatef((GLfloat)(rotate_2 / 100.0), 0, 1, 0);  //����2��̫����ת
	glTranslatef(3.5, 0, 0);     //����2�Ĺ�ת�뾶
	glRotatef((GLfloat)(self_rotate / 100.0), 0, 1, 0);
	glColor3f(0, 1, 0);
	glutSolidSphere(0.5, 20, 8);

	glRotatef((GLfloat)(rotate_4 / 100.0), 0, 1, 1);   //������������2��ת�����ҹ��ƽ����б
	Draw_circuit(1.1);
	glTranslatef(1.1, 0, 0);         //���ǹ�ת�뾶
	glRotatef((GLfloat)(self_rotate / 100.0), 0, 1, 0);
	glColor3f(0.6, 0.2, 0);
	glutSolidSphere(0.2, 20, 8);
	glPopMatrix();

	glPushMatrix();    //glpush��glpop�������൱�ڰ�����֮�����ζ�������������
	glRotatef((GLfloat)(rotate_3 / 100.0), 0, 0, 1);   //����3��̫����ת���ҹ����ֱ
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

	glutPostRedisplay();  //���û����䣬Ҫ����һ�²Żᶯһ��
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);   //���û���
	glMatrixMode(GL_PROJECTION);  //ָ����һ�������ǵ�ǰ����
	glLoadIdentity();
	gluPerspective(60, (GLfloat)w / (GLfloat)h, 1.0, 20);   //����͸��ͶӰ����(fovy,aspect,zNear,zFar);
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