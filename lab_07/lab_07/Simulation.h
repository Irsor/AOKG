#pragma once

#include <Windows.h>
#include <stdio.h>

#include "glew-2.2.0/include/GL/glew.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL/freeglut.h"

#include "Camera.h"
#include "GameObject.h"

extern int passabilityMap[21][21];

extern LARGE_INTEGER newTick;
extern LARGE_INTEGER oldTick;
extern LARGE_INTEGER frequency;

extern LARGE_INTEGER newSimTick;
extern LARGE_INTEGER oldSimTick;

extern Camera camera;
extern std::shared_ptr <GameObject> player;
extern std::shared_ptr <GameObject> mapObjects[21][21];
extern enum class MoveDirection;

// получение времени симул€ции в секундах
float getSimulationTime();

// симул€ци€ камеры
void cameraSimulation(float simulationTime);

// симул€ци€ всех игровых объектов
void gameObjectsSimulation(float simulationTime);

// перемещение главного геро€ (распределение сообщений)
void movePlayer();

// функци€ симул€ции
void simulation();