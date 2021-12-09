#pragma once

#include <Windows.h>
#include <stdio.h>
#include <string>

#include <stb_image.h>

#include "glew-2.2.0/include/GL/glew.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include <GL/freeglut.h>

// ������������ ��� ����������� ������ ����������
enum class TextureFilter 
{
	POINT, // ��������
	BILINEAR, // ����������
	TRILINEAR, // �����������
	ANISOTROPIC // ������������
};


class Texture
{
public:
	// �������� �������� �� �������� �����
	void load(std::string filename);

	// ���������� �������� (�������� � ����������� ����� � ��������� ����������)
	void apply(TextureFilter texFilter = TextureFilter::ANISOTROPIC);

	// ���������� ��������������� ��� ���� ���������� ������
	static void disableAll();

private:
	// ������������� (������) ����������� �������
	GLuint texIndex;
};

