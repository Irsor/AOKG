#include "Light.h"

Light::Light(GLfloat x, GLfloat y, GLfloat z)
{
	this->position[0] = x;
	this->position[1] = y;
	this->position[2] = z;
	this->position[3] = 0;
}

void Light::setAmbient(glm::vec4 color)
{
	this->ambient = color;
}

void Light::setDiffuse(glm::vec4 color)
{
	this->diffuse = color;
}

void Light::setSpecular(glm::vec4 color)
{
	this->specular = color;
}

void Light::apply(GLenum lightNumber)
{
	glEnable(GL_LIGHTING);
	glEnable(lightNumber);

	GLfloat position[] = { this->position[0], this->position[1], this->position[2], this->position[3] };
	GLfloat ambient[] = { this->ambient[0], this->ambient[1], this->ambient[2], this->ambient[3] };
	GLfloat diffuse[] = { this->diffuse[0], this->diffuse[1], this->diffuse[2], this->diffuse[3] };
	GLfloat specular[] = { this->specular[0], this->specular[1], this->specular[2], this->specular[3] };

	glLightfv(lightNumber, GL_POSITION, position);
	glLightfv(lightNumber, GL_AMBIENT, ambient);
	glLightfv(lightNumber, GL_DIFFUSE, diffuse);
	glLightfv(lightNumber, GL_POSITION, position);
}