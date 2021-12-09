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
	glTranslatef(this->position[0], this->position[1], this->position[2]);

	if (this->material != nullptr && this->mesh != nullptr)
	{
		this->material->apply();
		this->mesh->draw();
		Texture::disableAll();
	}
	glPopMatrix();
}

void GraphicObject::setMaterial(std::shared_ptr <Material> material)
{
	this->material = material;
}

void GraphicObject::setMesh(std::shared_ptr <Mesh> mesh)
{
	this->mesh = mesh;
}