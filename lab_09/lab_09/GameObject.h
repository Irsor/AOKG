#pragma once

#include <Windows.h>
#include <stdio.h>

#include "glew-2.2.0/include/GL/glew.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL/freeglut.h"

#include "GLM/glm.hpp"

#include "GraphicObject.h"

extern int passabilityMap[21][21];

// класс-перечисление дл€ указани€ направлени€ перемещени€
enum class MoveDirection { STOP, LEFT, RIGHT, UP, DOWN };

class GameObject
{
public:
	GameObject();

	// установка используемого графического объекта
	void setGraphicObject(const GraphicObject& graphicObject);

	// установка логических координат
	void setPosition(int x, int y);

	// получение текущих логических координат
	glm::vec2 getPositon();

	// вывод игрового объекта на экран
	void draw(void);

	// начать движение в выбранном направлении с указанной скоростью 
	// скорость передвижени€ определ€етс€ количеством клеток в секунду
	void move(MoveDirection direction, float speed = 3.0f);

	// симул€ци€ игрового объекта (плавное перемещение объекта)
	// метод вызываетс€ непрерывно в функции simulation
	void simulate(float sec);

	// проверка на то, что объект в насто€щий момент движетс€
	bool isMoving();

private:
	// логические координаты
	glm::vec2 position;
	// графический объект
	GraphicObject graphicObject;
	// состо€ние объекта (заданное направление перемещени€)
	MoveDirection state;
	// прогресс в перемещении (от 0.0 до 1.0)
	float progress;
	// скорость перемещени€
	float speed;
};

class Monster : public GameObject
{
public:
	Monster();

	// установить прошлые координаты
	void setLastStand(int x, int y);

	// перегрузка дл€ векторов
	void setLastStand(glm::vec2 vector);

	// получить прошлые координаты
	glm::vec2 getLastStand();

	// перемещение монстров
	void monsterSimulation();

private:
	// прошлые координаты дл€ монстра
	glm::vec2 lastStand;
};