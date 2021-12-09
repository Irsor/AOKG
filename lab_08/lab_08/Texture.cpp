#include "Texture.h"

void Texture::load(std::string filename)
{
	// определяем модель памяти (параметры распаковки)
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// загружаем изображение
	int width, height, cnt;
	unsigned char* image = stbi_load("data\\textures\\plane.jpg", &width, &height, &cnt, 0);

	// генерируем текстурный объект
	glGenTextures(1, &this->texIndex);

	// делаем текстурный объект текущим
	glBindTexture(GL_TEXTURE_2D, this->texIndex);

	//// задаем параметры текстурного объекта
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// привязываем изображение к текстуре
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	// отвязывем текущую текстуру
	glBindTexture(GL_TEXTURE_2D, 0);

	// освобождаем память выделенную под изображение
	stbi_image_free(image);
}

void Texture::apply(TextureFilter texFilter)
{
	glBindTexture(GL_TEXTURE_2D, this->texIndex);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	switch (texFilter)
	{
	case TextureFilter::POINT:
		break;
	case TextureFilter::BILINEAR:
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		break;
	case TextureFilter::TRILINEAR:
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		break;
	case TextureFilter::ANISOTROPIC:
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		break;
	}
}

void Texture::disableAll()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
