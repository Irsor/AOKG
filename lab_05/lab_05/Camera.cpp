#include "Camera.h"

#include <iostream>

#include <cmath>

Camera::Camera(GLfloat radius, GLfloat pitch, GLfloat yaw)
{
	this->coords[0][0] = 0;
	this->coords[0][1] = 0;
	this->coords[0][2] = 0;
	this->coords[1][0] = 0;
	this->coords[1][1] = 0;
	this->coords[1][2] = 0;
	this->coords[2][0] = 0;
	this->coords[2][1] = 1;
	this->coords[2][2] = 0;

	this->radius = radius;

	this->yaw = yaw;
	this->pitch = pitch;
	this->roll = 0;

	this->rotateSpeed = 100000;
	this->zoomSpeed = 1000;
}

void Camera::updateCoords()
{
	// this->coords[0][0] = r * sin(theta) * cos(fi);
	this->coords[0][0] = radius * cos(glm::radians(this->pitch)) * cos(glm::radians(this->yaw));
	this->coords[0][1] = radius * sin(glm::radians(this->pitch));
	this->coords[0][2] = radius * cos(glm::radians(this->pitch)) * sin(glm::radians(this->yaw));
}

void Camera::zoomInOut(GLfloat speed, bool direction)
{
	if (direction)
	{
		if (this->radius <= 50)
		{
			radius += this->zoomSpeed * speed;
		}
	}
	else
	{
		if (this->radius >= 0.01)
		{
			radius -= this->zoomSpeed * speed;
		}
	}
}

void Camera::leftRight(GLfloat speed, bool direction)
{
	if (direction)
	{
		yaw += speed * this->rotateSpeed;
	}
	else
	{
		yaw -= speed * this->rotateSpeed;
	}
}

void Camera::upDown(GLfloat speed, bool direction)
{
	if (direction)
	{
		if (this->pitch <= 89)
		{
			pitch += speed * this->rotateSpeed;
		}
	}
	else
	{
		if (this->pitch >= -89)
		{
			pitch -= speed * this->rotateSpeed;
			// std::cout << pitch << std::endl;
		}
	}

}

void Camera::apply()
{
	gluLookAt(coords[0][0], coords[0][1], coords[0][2], coords[1][0], coords[1][1], coords[1][2], coords[2][0], coords[2][1], coords[2][2]);
}