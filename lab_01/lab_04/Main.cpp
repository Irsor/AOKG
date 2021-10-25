#pragma once 

#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <GL/freeglut.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

// ������� ��������� ������� ������
void KeyboardFunc(unsigned char key, int x, int y)
{
	printf("Key code is %i\n", (unsigned int)key);
};


LARGE_INTEGER newTick;
LARGE_INTEGER oldTick;
LARGE_INTEGER freq;

LARGE_INTEGER newSimTick;
LARGE_INTEGER oldSimTick;

double getSimulationTime()
{
	oldSimTick = newSimTick;
	QueryPerformanceCounter(&newSimTick);
	return (double(newSimTick.QuadPart - oldSimTick.QuadPart)) / freq.QuadPart;
}


// ������� ���������� ��� ����������� ����
// � ��� ����� � �������������, �� �������� glutPostRedisplay
void Display(void)
{
	QueryPerformanceCounter(&newTick);
	// ������������� ������ 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(15, 15, 7.5, 0, 0, 0, 0, 1, 0);


	// �������� ����� ����� 
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// �������� ���� �������  	
	glEnable(GL_DEPTH_TEST);

	// ������� ������� 

	glutWireTeapot(1.0);
	// ����� ��������� � ������� ������� 
	glutSwapBuffers();
};

// �������, ���������� ��� ��������� �������� ����
void Reshape(int w, int h)
{
	// ���������� ����� ������� ���������, ������ ���� ������� ����
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	// ���������� ������� �������� � ���������� ��������
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(25.0, (float)w / h, 0.2, 70.0);
};

// ������� ���������� ������ 20 ��
void Simulation()
{
	
	glutPostRedisplay();
};

int main(int argc, char** argv)
{
	// ������������� ���������� GLUT
	glutInit(&argc, argv);
	QueryPerformanceFrequency(&freq);
	// �������� ����:
   // 1. ������������� ������� ����� ���� ����
	glutInitWindowPosition(200, 200);
	// 2. ������������� ������ ����
	glutInitWindowSize(600, 600);
	// 3. ������� ����
	glutCreateWindow("LR-1");
	glColor3f(1.0, 0.0, 0.0);

	// ������������� �������, ������� ����� ���������� ��� ����������� ����
	glutDisplayFunc(Display);
	// ������������� �������, ������� ����� ���������� ��� ��������� �������� ����n
	glutReshapeFunc(Reshape);
	// ������������� ������� ������� ����� ������� ����� 20 ��
	// ������������� �������, ������� ����� ���������� ��� ������� �� �������
	glutKeyboardFunc(KeyboardFunc);
	// �������� ���� ��������� ���������� ��
	glutIdleFunc(Simulation);

	QueryPerformanceCounter(&newTick);
	QueryPerformanceFrequency(&freq);
	newSimTick = newTick;
	glutMainLoop();
}