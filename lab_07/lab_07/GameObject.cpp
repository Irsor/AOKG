#include "GameObject.h"

GameObject::GameObject() {};

void GameObject::setGraphicObject(const GraphicObject& graphicObject)
{
	this->graphicObject = graphicObject;
	this->state = MoveDirection::STOP;
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

void GameObject::simulate(float sec)
{
	if (this->state == MoveDirection::LEFT)
	{
		if (this->progress < 1.0f)
		{
			this->progress += sec * this->speed;
			this->graphicObject.setPosition(this->getPositon().x - 10 - this->progress, 0, this->getPositon().y - 10);
			// std::cout << this->progress << std::endl;
		}
		if (this->progress >= 1.0f)
		{
			this->state = MoveDirection::STOP;
			this->setPosition(this->getPositon().x - 1, this->getPositon().y);
			this->progress = 0.0f;
		}
	}
	if (this->state == MoveDirection::RIGHT)
	{
		if (this->progress < 1.0f)
		{
			this->progress += sec * this->speed;
			this->graphicObject.setPosition(this->getPositon().x - 10 + this->progress, 0, this->getPositon().y - 10);
			// std::cout << this->progress << std::endl;
		}
		if (this->progress >= 1.0f)
		{
			this->state = MoveDirection::STOP;
			this->setPosition(this->getPositon().x + 1, this->getPositon().y);
			this->progress = 0.0f;
		}
	}
	if (this->state == MoveDirection::UP)
	{
		if (this->progress < 1.0f)
		{
			this->progress += sec * this->speed;
			this->graphicObject.setPosition(this->getPositon().x - 10, 0, this->getPositon().y - 10 - this->progress);
			// std::cout << this->progress << std::endl;
		}
		if (this->progress >= 1.0f)
		{
			this->state = MoveDirection::STOP;
			this->setPosition(this->getPositon().x, this->getPositon().y - 1);
			this->progress = 0.0f;
		}
	}
	if (this->state == MoveDirection::DOWN)
	{
		if (this->progress < 1.0f)
		{
			this->progress += sec * this->speed;
			this->graphicObject.setPosition(this->getPositon().x - 10, 0, this->getPositon().y - 10 + this->progress);
			// std::cout << this->progress << std::endl;
		}
		if (this->progress >= 1.0f)
		{
			this->state = MoveDirection::STOP;
			this->setPosition(this->getPositon().x, this->getPositon().y + 1);
			this->progress = 0.0f;
		}
	}
}

bool GameObject::isMoving()
{
	if (this->state == MoveDirection::STOP)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void GameObject::move(MoveDirection direction, float speed)
{
	this->speed = speed;
	switch (direction)
	{
	case MoveDirection::LEFT:
		this->state = MoveDirection::LEFT;
		break;
	case MoveDirection::RIGHT:
		this->state = MoveDirection::RIGHT;
		break;
	case MoveDirection::UP:
		this->state = MoveDirection::UP;
		break;
	case MoveDirection::DOWN:
		this->state = MoveDirection::DOWN;
		break;
	}
}