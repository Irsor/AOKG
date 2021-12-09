#pragma once

#include <Windows.h>
#include <stdio.h>
#include <string>

#include <stb_image.h>

#include "glew-2.2.0/include/GL/glew.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include <GL/freeglut.h>

// ПЕРЕЧИСЛЕНИЕ ДЛЯ ОПРЕДЕЛЕНИЯ РЕЖИМА ФИЛЬТРАЦИИ
enum class TextureFilter 
{
	POINT, // ТОЧЕЧНАЯ
	BILINEAR, // БИЛИНЕЙНАЯ
	TRILINEAR, // ТРИЛИНЕЙНАЯ
	ANISOTROPIC // АНИЗТОРОПНАЯ
};


class Texture
{
public:
	// загрузка текстуры из внешнего файла
	void load(std::string filename);

	// применение текстуры (привязка к текстурному блоку и установка параметров)
	void apply(TextureFilter texFilter = TextureFilter::ANISOTROPIC);

	// отключение текстурирования для всех текстурных блоков
	static void disableAll();

private:
	// идентификатор (индекс) текстурного объекта
	GLuint texIndex;
};

