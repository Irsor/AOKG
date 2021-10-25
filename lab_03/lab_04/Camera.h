#pragma once

#include <Windows.h>
#include <stdio.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL/freeglut.h"


#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Camera
{
public:
	Camera(GLfloat radius, GLfloat pitch, GLfloat yaw);
	void apply();
	void updateCoords();
	void leftRight(GLfloat speed, bool direction);
	void zoomInOut(GLfloat speed, bool direction);
	void upDown(GLfloat speed, bool rotation);

private:
	GLfloat pitch;
	GLfloat yaw;
	GLfloat roll;

	GLfloat radius;

	glm::vec3 xyz;
	glm::mat3 coords;

	GLfloat rotateSpeed;
	GLfloat zoomSpeed;
};