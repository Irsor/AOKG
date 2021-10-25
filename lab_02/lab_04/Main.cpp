#pragma once 

#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <GL/freeglut.h>
#include "GraphicObject.h"
#include <string>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

// Функция обработки нажатия клавиш
void KeyboardFunc(unsigned char key, int x, int y)
{
	printf("Key code is %i\n", (unsigned int)key);
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

// функция вызывается при перерисовке окна
// в том числе и принудительно, по командам glutPostRedisplay
void Display(void)
{
	QueryPerformanceCounter(&newTick);
	// устанавливаем камеру 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(15, 15, 7.5, 0, 0, 0, 0, 1, 0);

	

	// отчищаем буфер цвета 
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// включаем тест глубины  	
	glEnable(GL_DEPTH_TEST);

	// выводим объекты 
	for (int i = 0; i < 4; i++)
	{
		gr_[i].draw();
	}

	// смена переднего и заднего буферов 
	glutSwapBuffers();
	outputFramesPerSecond();

	fpsCount++;
};

// функция, вызываемая при изменении размеров окна
void Reshape(int w, int h)
{
	// установить новую область просмотра, равную всей области окна
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	// установить матрицу проекции с правильным аспектом
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(25.0, (float)w / h, 0.2, 70.0);
};

// функция вызывается каждые 20 мс
void Simulation()
{
	double deltaTime = getSimulationTime();

	glutPostRedisplay();
};

int main(int argc, char** argv)
{
	gr_[0] = gr1;
	gr_[1] = gr2;
	gr_[2] = gr3;
	gr_[3] = gr4;
	// Инициализация библиотеки GLUT
	glutInit(&argc, argv);
	QueryPerformanceFrequency(&freq);
	// создание окна:
   // 1. устанавливаем верхний левый угол окна
	glutInitWindowPosition(200, 200);
	// 2. устанавливаем размер окна
	glutInitWindowSize(600, 600);
	// 3. создаем окно
	glutCreateWindow("LR-1");
	glColor3f(1.0, 0.0, 0.0);

	// устанавливаем функцию, которая будет вызываться для перерисовки окна
	glutDisplayFunc(Display);
	// устанавливаем функцию, которая будет вызываться при изменении размеров окнаn
	glutReshapeFunc(Reshape);
	// устанавливаем функцию которая будет вызвана через 20 мс
	// устанавливаем функцию, которая будет вызываться при нажатии на клавишу
	glutKeyboardFunc(KeyboardFunc);
	// основной цикл обработки сообощений ОС
	glutIdleFunc(Simulation);

	QueryPerformanceCounter(&newTick);
	QueryPerformanceFrequency(&freq);
	newSimTick = newTick;
	glutMainLoop();
}