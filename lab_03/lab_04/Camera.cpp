#include "Camera.h"

#include <iostream>

#include <cmath>

Camera::Camera(GLfloat radius, GLfloat pitch, GLfloat yaw)
{
	this->coords[0][0] = 10;
	this->coords[0][1] = 10;
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

	this->rotateSpeed = 1000;
	this->zoomSpeed = 0.1;
}

void Camera::updateCoords()
{
	// this->coords[0][0] = r * sin(theta) * cos(fi);
	/*this->coords[0][0] = pitch - yaw;
	this->coords[0][1] = pitch;
	this->coords[0][2] = pitch + yaw;*/
	// this->coords[0][0] = r * sin(theta) * cos(fi);
	this->coords[0][0] = this->coords[0][0];
	this->coords[0][1] = this->coords[0][0];
	this->coords[0][2] = this->coords[0][0];
	this->coords[1][0] = this->coords[1][0];
	this->coords[1][1] = this->coords[1][1];
	this->coords[1][2] = this->coords[1][2];

}

void Camera::zoomInOut(GLfloat speed, bool direction)
{
	if (direction)
	{
		radius += this->zoomSpeed;
	}
	else
	{
		radius -= this->zoomSpeed;
	}
}

void Camera::leftRight(GLfloat speed, bool direction)
{
	if (direction)
	{
		this->coords[0][0] += speed * this->rotateSpeed;
		this->coords[1][0] += speed * this->rotateSpeed;
	}
	else
	{
		this->coords[0][0] -= speed * this->rotateSpeed;
		this->coords[1][0] -= speed * this->rotateSpeed;
	}
}

void Camera::upDown(GLfloat speed, bool direction)
{
	if (direction)
	{
		if (this->pitch <= 89)
		{
			this->coords[0][1] += speed * this->rotateSpeed;
			this->coords[1][1] += speed * this->rotateSpeed;
		}
	}
	else
	{
		if (this->pitch >= -89)
		{
			this->coords[0][1] -= speed * this->rotateSpeed;
			this->coords[1][1] -= speed * this->rotateSpeed;
		}
	}

}

void Camera::apply()
{
	gluLookAt(coords[0][0], coords[0][1], coords[0][2], coords[1][0], coords[1][1], coords[1][2], coords[2][0], coords[2][1], coords[2][2]);
}