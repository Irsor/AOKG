#pragma once

#include <Windows.h>
#include <stdio.h>

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <cstddef>

#include "glew-2.2.0/include/GL/glew.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL/freeglut.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

struct Vertex
{
	Vertex();

	// геометрические координаты
	GLfloat coord[3];
	// вектор нормали
	GLfloat normal[3];
	// текстурные координаты нулевого текстурного блока 
	GLfloat texturCoord[3];
};

class Mesh
{
public:
	Mesh();
	void load(std::string filename);
	void draw();

private:
	/*std::vector <Vertex> vertices;
	std::vector <GLuint> indices;*/
	// количество индексов
	int indexCount;
	// индексы (идентификаторы) буферов OpenGL
	GLuint bufferIds[2];
};