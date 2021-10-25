#include "GraphicObject.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

GraphicObject::GraphicObject() {};


GraphicObject::GraphicObject(float x, float y, float z, float a, float r, float g, float b)
{
	setPosition(x, y, z);
	setAngle(a);
	set—olor(r, g, b);
}

void GraphicObject::setPosition(float x, float y, float z)
{
	position[0] = x;
	position[1] = y;
	position[2] = z;
}

void GraphicObject::setAngle(float a)
{
	angle = a;
}

void GraphicObject::set—olor(float r, float g, float b)
{
	color[0] = r;
	color[1] = g;
	color[2] = b;
	/*glColor3f(color[0], color[1], color[2]);*/
}

void GraphicObject::draw()
{
	glPushMatrix();
	glTranslatef(position[0], position[1], position[2]);
	glColor3f(color[0], color[1], color[2]);
	glRotatef(angle, 0.0f, 1.0f, 0.0f);
	glutWireTeapot(1.0);
	glPopMatrix();
}
