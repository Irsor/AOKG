#include "GameObject.h"

GameObject::GameObject() {};

void GameObject::setGraphicObject(const GraphicObject& graphicObject)
{
	this->graphicObject = graphicObject;
}

void GameObject::setPosition(int x, int y)
{
	this->position = glm::vec2(x, y);
}

glm::vec2 GameObject::getPositon()
{
	return this->position;
}

void GameObject::draw(void)
{
	graphicObject.draw();
}
