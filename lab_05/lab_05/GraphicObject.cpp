#include "GraphicObject.h"

GraphicObject::GraphicObject() {};


GraphicObject::GraphicObject(float x, float y, float z, float a, float r, float g, float b)
{
	setPosition(x, y, z);
	setAngle(a);
	setÑolor(r, g, b);
	setPath(path);
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

void GraphicObject::setÑolor(float r, float g, float b)
{
	color[0] = r;
	color[1] = g;
	color[2] = b;
	/*glColor3f(color[0], color[1], color[2]);*/
}

void GraphicObject::setPath(std::string path)
{
	this->path = path;
}

void GraphicObject::draw()
{
	glPushMatrix();
	glTranslatef(position[0], position[1], position[2]);
	glColor3f(color[0], color[1], color[2]);
	glRotatef(angle, 0.0f, 1.0f, 0.0f);

	if (this->material != nullptr && this->mesh != nullptr)
	{
		this->material->apply();
		this->mesh->draw();
	}
	
	glPopMatrix();
}

void GraphicObject::setMaterial(std::shared_ptr <PhongMaterial> material)
{
	this->material = material;
}

void GraphicObject::setMesh(std::shared_ptr <Mesh> mesh)
{
	this->mesh = mesh;
}