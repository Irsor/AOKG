#pragma once

#include <Windows.h>
#include <stdio.h>

#include "GameObject.h"
#include "Mesh.h"
#include "GraphicObject.h"
#include "Material.h"

#include <memory>
#include <vector>
#include <fstream>

#include "rapidjson/document.h"

#include "glew-2.2.0/include/GL/glew.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL/freeglut.h"

enum class GameObjectType
{
	LIGHT_OBJECT, // легкий игровой объект
	HEAVY_OBJECT, // тяжелый игровой объект
	BORDER_OBJECT, // граничный игровой объект
	PLAYER, // игровой объект для представления игрока
	BOMB, // игровой объект для представления бомбы
	MONSTER // игровой объект для представления монстров
};

class GameObjectFactory
{
public:
	bool init(std::string filename);
	std::shared_ptr <GameObject> create(GameObjectType type, int x, int y);
	std::shared_ptr <Monster> create(GameObjectType type, int x, int y, bool monster);

private:
	std::vector <std::shared_ptr <Mesh>> meshes;
	std::vector <std::shared_ptr <PhongMaterial>> materials;
};