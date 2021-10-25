#pragma once

#include <Windows.h>
#include <stdio.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL/freeglut.h"

#include <iostream>
#include <string>
#include <fstream>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class PhongMaterial
{
public:
	PhongMaterial();

	void setAmbient(glm::vec4 color);
	void setDiffuse(glm::vec4 color);
	void setSpecular(glm::vec4 color);
	void setEmission(glm::vec4 color);
	void setShininess(GLfloat param);

	void load(std::string fileName);

	void apply();

private:
	glm::vec4 ambient;
	glm::vec4 diffuse;
	glm::vec4 specular;
	glm::vec4 emission;
	GLfloat shininess;
};