#include <Windows.h>
#include <stdio.h>

#include <iostream>
#include <string>
#include <fstream>
#include <memory>
#include <vector>

#include <gl/GL.h>
#include <gl/GLU.h>
#include <GL/freeglut.h>

#include "GraphicObject.h"
#include "Camera.h"

#include "Light.h"
#include "Material.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

// ������� ��������� ������� ������
void KeyboardFunc(unsigned char key, int x, int y)
{
	// printf("Key code is %i\n", (unsigned int)key);
};

GraphicObject gr1(-2.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
GraphicObject gr2(0.0f, 0.0f, 2.5f, 90, 0.0f, 1.0f, 1.0f);
GraphicObject gr3(0.0f, 0.0f, -2.5f, -90, 1.0f, 0.0f, 1.0f);
GraphicObject gr4(2.5f, 0.0f, 0.0f, 180, 1.0f, 1.0f, 0.0f);

GraphicObject gr_[4];

LARGE_INTEGER newTick;
LARGE_INTEGER oldTick;
LARGE_INTEGER freq;

LARGE_INTEGER newSimTick;
LARGE_INTEGER oldSimTick;

PhongMaterial material_1;
PhongMaterial material_2;
PhongMaterial material_3;
PhongMaterial material_4;

std::vector <std::shared_ptr<PhongMaterial>> materials(4);

Camera camera(15, 15, 7.5);
Light light(10.0f, 0.0f, 0.0f);

double getSimulationTime()
{
	oldSimTick = newSimTick;
	QueryPerformanceCounter(&newSimTick);
	return (double(newSimTick.QuadPart - oldSimTick.QuadPart)) / freq.QuadPart;
}


float fpsCount = 0;

void outputFramesPerSecond()
{
	QueryPerformanceCounter(&newTick);

	double delta = double(newTick.QuadPart - oldTick.QuadPart) / freq.QuadPart;
	std::string msg;
	if (delta >= 1.0)
	{
		msg += "FPS: ";
		msg += std::to_string((double)fpsCount / delta);
		const char* ch = msg.c_str();
		glutSetWindowTitle(ch);
		fpsCount = 0;
		oldTick = newTick;
	}

}

// ������� ���������� ��� ����������� ����
// � ��� ����� � �������������, �� �������� glutPostRedisplay
void Display(void)
{
	QueryPerformanceCounter(&newTick);
	// ������������� ������ 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// gluLookAt(15, 15, 7.5, 0, 0, 0, 0, 1, 0);

	camera.apply();
	camera.updateCoords();

	light.apply();
	
	// �������� ����� ����� 
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// �������� ���� �������  	
	glEnable(GL_DEPTH_TEST);

	for (auto& gr : gr_)
	{
		gr.draw();
	}

	// ����� ��������� � ������� ������� 
	glutSwapBuffers();
	outputFramesPerSecond();

	fpsCount++;
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
	double deltaTime = getSimulationTime();

	if (GetAsyncKeyState(VK_LEFT))
	{
		camera.leftRight(getSimulationTime(), 0);
	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		camera.leftRight(getSimulationTime(), 1);
	}
	if (GetAsyncKeyState(VK_UP))
	{
		camera.upDown(getSimulationTime(), 0);
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		camera.upDown(getSimulationTime(), 1);
	}
	if (GetAsyncKeyState(VK_ADD))
	{
		camera.zoomInOut(getSimulationTime(), 0);
	}
	if (GetAsyncKeyState(VK_SUBTRACT))
	{
		camera.zoomInOut(getSimulationTime(), 1);
	}

	glutPostRedisplay();
};

int main(int argc, char** argv)
{
	material_1.load("data/materials/material_1.txt");
	material_2.load("data/materials/material_2.txt");
	material_3.load("data/materials/material_3.txt");
	material_4.load("data/materials/material_4.txt");

	materials[0] = std::make_shared<PhongMaterial>(material_1);
	materials[3] = std::make_shared<PhongMaterial>(material_2);
	materials[1] = std::make_shared<PhongMaterial>(material_3);
	materials[2] = std::make_shared<PhongMaterial>(material_4);

	gr_[0] = gr1;
	gr_[0].setMaterial(materials[0]);
	gr_[1] = gr2;
	gr_[1].setMaterial(materials[1]);
	gr_[2] = gr3;
	gr_[2].setMaterial(materials[2]);
	gr_[3] = gr4;
	gr_[3].setMaterial(materials[3]);

	light.setAmbient(glm::vec4(0.2f, 0.2f, 0.2f, 0.0f));
	light.setDiffuse(glm::vec4(0.4f, 0.4f, 0.4f, 0.0f));
	light.setSpecular(glm::vec4(0.8f, 0.8f, 0.8f, 0.0f));

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