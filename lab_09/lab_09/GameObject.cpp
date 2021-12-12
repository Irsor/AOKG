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

void GameObject::setExist(bool value)
{
	this->exist = value;
}

bool GameObject::getExist()
{
	return exist;
}

void GameObject::move(MoveDirection direction, float speed)
{
	this->speed = speed + 10.0f;
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

Monster::Monster() 
{
	this->setExist(true);
}

void Monster::setLastStand(int x, int y)
{
	this->lastStand.x = x;
	this->lastStand.y = y;
}

void Monster::setLastStand(glm::vec2 vector)
{
	this->lastStand.x = vector.x;
	this->lastStand.y = vector.y;
}

glm::vec2 Monster::getLastStand()
{
	return this->lastStand;
}

void Monster::monsterSimulation()
{
	srand(time(NULL));

	if (!this->isMoving())
	{
		if (passabilityMap[int(this->getPositon().x + 1)][int(this->getPositon().y)] > 0 &&
			passabilityMap[int(this->getPositon().x - 1)][int(this->getPositon().y)] > 0 &&
			passabilityMap[int(this->getPositon().x)][int(this->getPositon().y + 1)] > 0)
		{
			this->move(MoveDirection::UP, 1.0f);
			this->setLastStand(this->getPositon());
		}
		else
			if (passabilityMap[int(this->getPositon().x + 1)][int(this->getPositon().y)] > 0 &&
				passabilityMap[int(this->getPositon().x - 1)][int(this->getPositon().y)] > 0 &&
				passabilityMap[int(this->getPositon().x)][int(this->getPositon().y - 1)] > 0)
			{
				this->move(MoveDirection::DOWN, 1.0f);
				this->setLastStand(this->getPositon());
			}
			else
				if (passabilityMap[int(this->getPositon().x + 1)][int(this->getPositon().y)] > 0 &&
					passabilityMap[int(this->getPositon().x)][int(this->getPositon().y - 1)] > 0 &&
					passabilityMap[int(this->getPositon().x)][int(this->getPositon().y + 1)] > 0)
				{
					this->move(MoveDirection::LEFT, 1.0f);
					this->setLastStand(this->getPositon());
				}
				else
					if (passabilityMap[int(this->getPositon().x - 1)][int(this->getPositon().y)] > 0 &&
						passabilityMap[int(this->getPositon().x)][int(this->getPositon().y - 1)] > 0 &&
						passabilityMap[int(this->getPositon().x)][int(this->getPositon().y + 1)] > 0)
					{
						this->move(MoveDirection::RIGHT, 1.0f);
						this->setLastStand(this->getPositon());
					}
					else
					{
						if (passabilityMap[int(this->getPositon().x + 1)][int(this->getPositon().y)] > 0 &&
							passabilityMap[int(this->getPositon().x - 1)][int(this->getPositon().y)] > 0)
						{
							if (this->getLastStand().x == this->getPositon().x && this->getLastStand().y == this->getPositon().y + 1)
							{
								this->move(MoveDirection::UP, 1.0f);
								this->setLastStand(this->getPositon());
							}
							else
							{
								this->move(MoveDirection::DOWN, 1.0f);
								this->setLastStand(this->getPositon());
							}
						}
						else
							if (passabilityMap[int(this->getPositon().x)][int(this->getPositon().y + 1)] > 0 &&
								passabilityMap[int(this->getPositon().x)][int(this->getPositon().y - 1)] > 0)
							{
								if (this->getLastStand().x == this->getPositon().x + 1 && this->getLastStand().y == this->getPositon().y)
								{
									this->move(MoveDirection::LEFT, 1.0f);
									this->setLastStand(this->getPositon());
								}
								else
								{
									this->move(MoveDirection::RIGHT, 1.0f);
									this->setLastStand(this->getPositon());
								}
							}
							else
							{
								int direction = rand() % 4;

						switch (direction)
						{
						case 0:
							if (passabilityMap[int(this->getPositon().x + 1)][int(this->getPositon().y)] == 0)
							{
								if (!(this->getLastStand().x == this->getPositon().x + 1 && this->getLastStand().y == this->getPositon().y))
							{
								this->move(MoveDirection::RIGHT, 1.0f);
								this->setLastStand(this->getPositon());
							}
						}
						break;
					case 1:
						if (passabilityMap[int(this->getPositon().x)][int(this->getPositon().y) + 1] == 0)
						{
							if (!(this->getLastStand().x == this->getPositon().x && this->getLastStand().y == this->getPositon().y + 1))
								{
								this->move(MoveDirection::DOWN, 1.0f);
								this->setLastStand(this->getPositon());
							}
						}
					break;
					case 2:
						if (passabilityMap[int(this->getPositon().x - 1)][int(this->getPositon().y)] == 0)
						{
							if (!(this->getLastStand().x == this->getPositon().x - 1 && this->getLastStand().y == this->getPositon().y))
							{
								this->move(MoveDirection::LEFT, 1.0f);
								this->setLastStand(this->getPositon());
							}
						}
					break;
					case 3:
						if (passabilityMap[int(this->getPositon().x)][int(this->getPositon().y - 1)] == 0)
						{
							if (!(this->getLastStand().x == this->getPositon().x && this->getLastStand().y == this->getPositon().y - 1))
							{
								this->setLastStand(this->getPositon());
								this->move(MoveDirection::UP, 1.0f);
							}
						}
					break;
				}
			}
		}
	}
}


