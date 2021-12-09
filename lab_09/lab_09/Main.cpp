#define STB_IMAGE_IMPLEMENTATION
#include <Windows.h>
#include <stdio.h>

#include <iostream>
#include <string>
#include <fstream>
#include <memory>
#include <vector>

#include "glew-2.2.0/include/GL/glew.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include <GL/freeglut.h>

#include "GraphicObject.h"
#include "Camera.h"

#include "Light.h"
#include "Material.h"

#include "Mesh.h"
#include "GameObject.h"

#include "GameObjectFactory.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Simulation.h"

#include "rapidjson-master/include/rapidjson/rapidjson.h"

#include "Texture.h"

LARGE_INTEGER frequency;
LARGE_INTEGER newSimTick;
LARGE_INTEGER oldSimTick;

LARGE_INTEGER newTick;
LARGE_INTEGER oldTick;

Camera camera(50, 65, 90);
Light light(25.0f, 25.0f, 0.0f);
GraphicObject gr[25];

GameObjectFactory gameObjectFactory;

GameObject gm[21][21];

GameObject plane;

const GLfloat SIZE_ = 1.0f;

std::shared_ptr <GameObject> mapObjects[21][21];
std::shared_ptr <GameObject> player;
std::shared_ptr <Monster> enemy[3];
std::shared_ptr <GameObject> bomb;

extern enum class MoveDirection;

Texture planeTexture;

bool showPlayer;
bool bombExist;

int passabilityMap[21][21] = {
 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
 3,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,2,0,0,0,3,
 3,0,2,1,2,0,2,0,2,2,2,1,2,0,2,0,2,0,2,2,3,
 3,0,2,0,2,0,0,0,2,0,2,0,0,0,2,0,1,0,0,0,3,
 3,0,1,0,2,2,1,2,2,0,2,0,2,2,2,1,2,0,2,0,3,
 3,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,2,0,2,0,3,
 3,0,2,2,1,1,2,0,2,0,2,2,2,2,2,0,2,2,2,0,3,
 3,0,2,0,0,0,2,0,2,0,0,0,0,0,2,0,0,0,0,0,3,
 3,0,2,0,2,2,2,0,2,0,2,2,1,2,2,2,1,2,2,0,3,
 3,0,0,0,2,0,0,0,2,0,2,0,0,0,0,0,0,0,1,0,3,
 3,2,2,2,2,0,2,2,2,0,2,0,2,2,2,2,2,2,2,0,3,
 3,0,0,0,2,0,0,0,1,0,2,0,0,0,2,0,0,0,0,0,3,
 3,0,2,0,2,2,2,0,2,1,2,0,2,2,2,0,2,2,2,2,3,
 3,0,2,0,0,0,2,0,0,0,2,0,0,0,2,0,2,0,0,0,3,
 3,2,2,2,2,0,2,2,2,0,2,2,2,0,1,0,2,2,2,0,3,
 3,0,0,0,0,0,2,0,2,0,0,0,2,0,1,0,0,0,2,0,3,
 3,0,2,0,2,1,2,0,2,0,2,2,2,0,2,2,2,0,2,0,3,
 3,0,1,0,1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,3,
 3,0,2,1,2,0,2,2,2,2,2,0,2,0,2,0,2,2,2,2,3,
 3,0,0,0,0,0,0,0,0,0,0,0,2,0,2,0,0,0,0,0,3,
 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
};

int fpsCount = 0;

void outputFramesPerSecond()
{
	QueryPerformanceCounter(&newTick);

	double delta = double(newTick.QuadPart - oldTick.QuadPart) / frequency.QuadPart;
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

void drawPlane()
{
	// выбираем активный текстурный блок
	glActiveTexture(GL_TEXTURE0);
	// разрешаем текстурирование в выбранном текстурном блоке
	glEnable(GL_TEXTURE_2D);
	// привязываем текстуру к ранее выбранному текстурному блоку
	planeTexture.apply();
	// указываем режим наложения текстуры (GL_MODULATE)
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// выводим плоскость
	plane.draw();
	// отключаем текстурирование (чтобы все остальные объекты выводились без текстур)
	// Texture::disableAll();
}

// функция вызывается при перерисовке окна
// в том числе и принудительно, по командам glutPostRedisplay
void Display(void)
{
	QueryPerformanceCounter(&newSimTick);
	// устанавливаем камеру 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	camera.apply();
	camera.updateCoords();

	light.apply();
	
	// отчищаем буфер цвета 
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// включаем тест глубины  	
	glEnable(GL_DEPTH_TEST);

	for (int i = 0; i < 21; i++)
	{
		for (int j = 0; j < 21; j++)
		{
			if (mapObjects[i][j].get() != nullptr)
			{
				mapObjects[i][j].get()->draw();
			}
		}
	}

	if (showPlayer)
	{
		player.get()->draw();
	}
	
	enemy[0].get()->draw(); 
	enemy[1].get()->draw();
	enemy[2].get()->draw(); 

	plane.draw();

	if (bomb != nullptr)
	{
		bomb.get()->draw();
	}

	outputFramesPerSecond();
	// std::cout << mapObjects[0][0];

	// смена переднего и заднего буферов 

	fpsCount++;
	glutSwapBuffers();
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

void initData()
{
	gameObjectFactory.init("data/GameObjectsDescription.json");
	showPlayer = true;

	for (int i = 0; i < 21; i++)
	{
		for (int j = 0; j < 21; j++)
		{
			switch (passabilityMap[i][j])
			{
			case 1:
				mapObjects[i][j] = gameObjectFactory.create(GameObjectType::LIGHT_OBJECT, i, j);
				break;
			case 2:
				mapObjects[i][j] = gameObjectFactory.create(GameObjectType::HEAVY_OBJECT, i, j);
				break;
			case 3:
				mapObjects[i][j] = gameObjectFactory.create(GameObjectType::BORDER_OBJECT, i, j);
				break;
			default:
				mapObjects[i][j] = nullptr;
				break;
			}
		}
	}

	player = gameObjectFactory.create(GameObjectType::PLAYER, 19, 1);
	
	enemy[0] = gameObjectFactory.create(GameObjectType::MONSTER, 19, 19, 1);
	enemy[1] = gameObjectFactory.create(GameObjectType::MONSTER, 1, 19, 1);
	enemy[2] = gameObjectFactory.create(GameObjectType::MONSTER, 1, 1, 1); 

	enemy[0].get()->setLastStand(19, 19);
	enemy[1].get()->setLastStand(1, 19);
	enemy[2].get()->setLastStand(1, 1);

	// Инициализация плоскости
	// planeTexture.load("data\\textures\\plane.jpg");
	GraphicObject planeGraphicObject(0, -0.6, 0, 0, 0, 0, 0);

	// ИНИЦИАЛИЗАЦИЯ ПЛОСКОСТИ:
	// установка меша для плоскости
	std::shared_ptr<Mesh> planeMesh = std::make_shared<Mesh>();
	planeMesh->load("data\\meshes\\HighPolyPlane.obj");
	planeGraphicObject.setMesh(planeMesh);

	// загрузка текстуры для плоскости
	std::shared_ptr<Texture> planeTexture = std::make_shared<Texture>();
	planeTexture->load("data\\textures\\plane.jpg");

	// установка материала для плоскости
	std::shared_ptr<PhongMaterialWithTexture> planeMaterial =
		std::make_shared<PhongMaterialWithTexture>();
	planeMaterial->load("data\\materials\\PlaneMaterial.txt");
	planeMaterial->setTexture(planeTexture);
	planeGraphicObject.setMaterial(planeMaterial);
	plane.setGraphicObject(planeGraphicObject);
	Texture::disableAll();
}

int main(int argc, char** argv)
{
	light.setAmbient(glm::vec4(1.0f, 1.0f, 1.0f, 0.0f));
	light.setDiffuse(glm::vec4(1.0f, 1.0f, 1.0f, 0.0f));
	light.setSpecular(glm::vec4(1.0f, 1.0f, 1.0f, 0.0f));
	
	// Инициализация библиотеки GLUT
	glutInit(&argc, argv);
	// создание окна:
	// 1. устанавливаем верхний левый угол окна
	glutInitWindowPosition(200, 200);
	// 2. устанавливаем размер окна
	glutInitWindowSize(800, 600);
	// 3. создаем окно
	glutCreateWindow("LR-1");

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		printf("Error: %s\n", glewGetErrorString(err));
	}
	printf("Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

	// проверка поддержки расширения для работы с буфером VBO
	if (GLEW_ARB_vertex_buffer_object)
	{
		printf("VBO is supported");
	};

	initData();

	// устанавливаем функцию, которая будет вызываться для перерисовки окна
	glutDisplayFunc(Display);
	// устанавливаем функцию, которая будет вызываться при изменении размеров окнаn
	glutReshapeFunc(Reshape);
	// основной цикл обработки сообощений ОС
	glutIdleFunc(simulation);

	QueryPerformanceCounter(&newSimTick);
	QueryPerformanceFrequency(&frequency);

	glutMainLoop();
}