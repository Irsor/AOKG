#pragma once

#include <Windows.h>
#include <stdio.h>

#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL/freeglut.h"

#include "GLM/glm.hpp"

#include "GraphicObject.h"

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

private:
	// логические координаты
	glm::vec2 position;
	// графический объект
	GraphicObject graphicObject;
	Mesh mesh;
};