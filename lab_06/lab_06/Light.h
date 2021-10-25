#pragma once

#include <Windows.h>
#include <stdio.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL/freeglut.h"


#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Light
{
public:
	Light(GLfloat x, GLfloat y, GLfloat z);

	void setAmbient(glm::vec4 color);
	void setDiffuse(glm::vec4 color);
	void setSpecular(glm::vec4 color);

	void apply(GLenum ligntNumber = GL_LIGHT0);

private:
	glm::vec4 position;
	glm::vec4 ambient;
	glm::vec4 diffuse;
	glm::vec4 specular;
};