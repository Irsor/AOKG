#include "GameObjectFactory.h"

bool GameObjectFactory::init(std::string filename)
{
	setlocale(LC_ALL, "russian");

	std::vector <std::string> firstLevel { "LightObject", "HeavyObject", "BorderObject", "Player", "Bomb", "Monster" };
	std::vector <std::string> secondLevel { "mesh", "material" };
	std::vector <std::string> thirdLevel { "diffuse", "ambient", "specular", "emission", "shininess" };

	std::ifstream fin;
	fin.open(filename);

	if (!fin.is_open())
	{
		std::cout << "Не удается найти файл " << filename << std::endl;
		return false;
	}

	// std::cout << "Парсим файл " << filename << ":" << std::endl;
	
	std::string jsonString;
	getline(fin, jsonString, static_cast<char>(0));
	fin.close();

	// std::cout << jsonString << std::endl;

	rapidjson::Document document;
	document.Parse(jsonString.c_str());

	if (document.GetParseError() != 0)
	{
		std::cout << "Неверный формат файла" << std::endl;
		return false;
	}

	std::vector <Mesh> mesh(3);
	
	mesh[0].load(document["LightObject"]["mesh"].GetString());
	mesh[1].load(document["BorderObject"]["mesh"].GetString());
	mesh[2].load(document["Player"]["mesh"].GetString());

	std::vector <PhongMaterial> material(6);

	for (int i = 0; i < material.size(); i++)
	{
		glm::vec4 vec_1;
		glm::vec4 vec_2;
		glm::vec4 vec_3;
		glm::vec4 vec_4;
		GLfloat shininess;

		for (int j = 0; j < 4; j++)
		{
			vec_1[j] = document[firstLevel[i].c_str()][secondLevel[1].c_str()][thirdLevel[0].c_str()][j].GetDouble();
		}

		for (int j = 0; j < 4; j++)
		{
			vec_2[j] = document[firstLevel[i].c_str()][secondLevel[1].c_str()][thirdLevel[1].c_str()][j].GetDouble();
		}
		
		for (int j = 0; j < 4; j++)
		{
			vec_3[j] = document[firstLevel[i].c_str()][secondLevel[1].c_str()][thirdLevel[2].c_str()][j].GetDouble();
		}
	
		for (int j = 0; j < 4; j++)
		{
			vec_4[j] = document[firstLevel[i].c_str()][secondLevel[1].c_str()][thirdLevel[3].c_str()][j].GetDouble();
		}

		shininess = document[firstLevel[i].c_str()][secondLevel[1].c_str()][thirdLevel[4].c_str()].GetDouble();

		material[i].setDiffuse(vec_1);
		material[i].setAmbient(vec_2);
		material[i].setSpecular(vec_3);
		material[i].setEmission(vec_4);
		material[i].setShininess(shininess);
	}

	this->meshes.push_back(std::make_shared<Mesh>(mesh[0]));
	this->meshes.push_back(std::make_shared<Mesh>(mesh[1]));
	this->meshes.push_back(std::make_shared<Mesh>(mesh[2]));

	this->materials.push_back(std::make_shared<PhongMaterial>(material[0]));
	this->materials.push_back(std::make_shared<PhongMaterial>(material[1]));
	this->materials.push_back(std::make_shared<PhongMaterial>(material[2]));
	this->materials.push_back(std::make_shared<PhongMaterial>(material[3]));
	this->materials.push_back(std::make_shared<PhongMaterial>(material[4]));
	this->materials.push_back(std::make_shared<PhongMaterial>(material[5]));
}

std::shared_ptr<GameObject> GameObjectFactory::create(GameObjectType type, int x, int y)
{
	GraphicObject* gr = new GraphicObject;
		
	switch (type)
	{
	case GameObjectType::LIGHT_OBJECT:
		gr->setMaterial(this->materials[0]);
		gr->setMesh(this->meshes[0]);
		break;
	case GameObjectType::HEAVY_OBJECT:
		gr->setMaterial(this->materials[1]);
		gr->setMesh(this->meshes[0]);
		break;
	case GameObjectType::BORDER_OBJECT:
		gr->setMaterial(this->materials[2]);
		gr->setMesh(this->meshes[1]);
		break;
	case GameObjectType::PLAYER:
		gr->setMaterial(this->materials[3]);
		gr->setMesh(this->meshes[2]);
		break;
	case GameObjectType::BOMB:
		gr->setMaterial(this->materials[4]);
		gr->setMesh(this->meshes[2]);
		break;
	case GameObjectType::MONSTER:
		gr->setMaterial(this->materials[5]);
		gr->setMesh(this->meshes[2]);
		break;
	default:
		break;
	}

	gr->setPosition(x, 0, y);
	// std::cout << x << "   " << y << std::endl;
 	GameObject* gm = new GameObject;
	gm->setGraphicObject(*gr);

	return std::shared_ptr<GameObject>(gm);
}
