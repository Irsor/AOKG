#include "Mesh.h"
#include <map>

Mesh::Mesh() {};

void Mesh::load(std::string filename)
{
	setlocale(LC_ALL, "ru");

	// графичесие координаты
	std::vector <glm::vec3> v;
	// нормали
	std::vector <glm::vec3> n;
	// текстуры
	std::vector <glm::vec3> t;
	// индексы атрибутов для постройки вершин
	std::vector <glm::mat3> fPoints;

	std::ifstream fin;
	fin.open(filename);

	std::map <std::string, int> vertexToIndexTable;
	int index = 0;


	if (fin.is_open())
	{
		std::string str;
		/*std::cout << std::endl << "Файл " + filename + " успешно открыт!" << std::endl << std::endl;*/
		GLfloat numbers[3];

		while (fin >> str)
		{
			if (str == "#" || str == "g")
			{
				std::getline(fin, str);
			}
			if (str == "v")
			{
				fin >> numbers[0];
				fin >> numbers[1];
				fin >> numbers[2];

				//std::cout << "v " << numbers[0] << " " << numbers[0] << " " << numbers[0] << std::endl;

				v.push_back(glm::vec3(numbers[0], numbers[1], numbers[2]));
			}
			if (str == "vn")
			{
				fin >> numbers[0];
				fin >> numbers[1];
				fin >> numbers[2];

				//std::cout << "vn " << numbers[0] << " " << numbers[0] << " " << numbers[0] << std::endl;

				n.push_back(glm::vec3(numbers[0], numbers[1], numbers[2]));
			}
			if (str == "vt")
			{
				fin >> numbers[0];
				fin >> numbers[1];
				fin >> numbers[2];

				//std::cout << "vt " << numbers[0] << " " << numbers[0] << " " << numbers[0] << std::endl;

				t.push_back(glm::vec3(numbers[0], numbers[1], numbers[2]));
			}
			if (str == "f")
			{
				std::string str1;
				std::string str2;
				std::string str3;

				fin >> str1;
				fin >> str2;
				fin >> str3;

				auto key = vertexToIndexTable.find(str1);

				if (key == vertexToIndexTable.cend())
				{
					vertexToIndexTable.insert(std::pair<std::string, int>(str1, index));
					this->indices.push_back(index);
					index++;

					std::vector <std::string> helper(3);
					int j = 0;

					for (int i = 0; i < str1.size(); i++)
					{
						if (str1[i] == '/')
						{
							j++;
						}
						else
						{
							helper[j] += (str1[i]);
						}
					}

					glm::vec3 vec;
					vec[0] = atoi(helper[0].c_str());
					vec[1] = atoi(helper[1].c_str());
					vec[2] = atoi(helper[2].c_str());

					Vertex vertex;
					vertex.coord[0] = v[vec[0] - 1].x;
					vertex.coord[1] = v[vec[0] - 1].y;
					vertex.coord[2] = v[vec[0] - 1].z;
					vertex.texturCoord[0] = t[vec[1] - 1].x;
					vertex.texturCoord[1] = t[vec[1] - 1].y;
					vertex.texturCoord[2] = t[vec[1] - 1].z;
					vertex.normal[0] = n[vec[2] - 1].x;
					vertex.normal[1] = n[vec[2] - 1].y;
					vertex.normal[2] = n[vec[2] - 1].z;

					vertices.push_back(vertex);
				}
				else
				{
					this->indices.push_back(vertexToIndexTable[str1]);
				}

				key = vertexToIndexTable.find(str2);

				if (key == vertexToIndexTable.cend())
				{
					vertexToIndexTable.insert(std::pair<std::string, int>(str2, index));
					this->indices.push_back(index);
					index++;

					std::vector <std::string> helper(3);
					int j = 0;

					for (int i = 0; i < str2.size(); i++)
					{
						if (str2[i] == '/')
						{
							j++;
						}
						else
						{
							helper[j] += (str2[i]);
						}
					}

					glm::vec3 vec;
					vec[0] = atoi(helper[0].c_str());
					vec[1] = atoi(helper[1].c_str());
					vec[2] = atoi(helper[2].c_str());

					Vertex vertex;
					vertex.coord[0] = v[vec[0] - 1].x;
					vertex.coord[1] = v[vec[0] - 1].y;
					vertex.coord[2] = v[vec[0] - 1].z;
					vertex.normal[0] = n[vec[2] - 1].x;
					vertex.normal[1] = n[vec[2] - 1].y;
					vertex.normal[2] = n[vec[2] - 1].z;
					vertex.texturCoord[0] = t[vec[1] - 1].x;
					vertex.texturCoord[1] = t[vec[1] - 1].y;
					vertex.texturCoord[2] = t[vec[1] - 1].z;

					vertices.push_back(vertex);
				}
				else
				{
					this->indices.push_back(vertexToIndexTable[str2]);
				}

				key = vertexToIndexTable.find(str3);

				if (key == vertexToIndexTable.cend())
				{
					vertexToIndexTable.insert(std::pair<std::string, int>(str3, index));
					this->indices.push_back(index);
					index++;

					std::vector <std::string> helper(3);
					int j = 0;

					for (int i = 0; i < str3.size(); i++)
					{
						if (str3[i] == '/')
						{
							j++;
						}
						else
						{
							helper[j] += (str3[i]);
						}
					}

					glm::vec3 vec;
					vec[0] = atoi(helper[0].c_str());
					vec[1] = atoi(helper[1].c_str());
					vec[2] = atoi(helper[2].c_str());

					Vertex vertex;
					vertex.coord[0] = v[vec[0] - 1].x;
					vertex.coord[1] = v[vec[0] - 1].y;
					vertex.coord[2] = v[vec[0] - 1].z;
					vertex.normal[0] = n[vec[2] - 1].x;
					vertex.normal[1] = n[vec[2] - 1].y;
					vertex.normal[2] = n[vec[2] - 1].z;
					vertex.texturCoord[0] = t[vec[1] - 1].x;
					vertex.texturCoord[1] = t[vec[1] - 1].y;
					vertex.texturCoord[2] = t[vec[1] - 1].z;

					vertices.push_back(vertex);				
				}
				else
				{
					this->indices.push_back(vertexToIndexTable[str3]);
				}
			}
		}

		fin.close();

		/*std::cout << std::endl << "Файл " + filename + " успешно закрыт!" << std::endl;*/

		// ключаем необходимые веришинные массивы
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);

		// указываем откуда и как брать атрибуты вершин
		glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), vertices[0].texturCoord);
		glNormalPointer(GL_FLOAT, sizeof(Vertex), vertices[0].normal);
		glVertexPointer(3, GL_FLOAT, sizeof(Vertex), vertices[0].coord);

		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, indices.data());

		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	}
	else
	{
		std::cout << "Файл " + filename + " не открыт" << std::endl;
	}
}


void Mesh::draw()
{
	if (vertices.size() == 0)
	{
		return;
	}

	// ключаем необходимые веришинные массивы
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

	// указываем откуда и как брать атрибуты вершин
	glTexCoordPointer(3, GL_FLOAT, sizeof(Vertex), vertices[0].texturCoord);
	glNormalPointer(GL_FLOAT, sizeof(Vertex), vertices[0].normal);
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), vertices[0].coord);

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, indices.data());

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}

Vertex::Vertex() {};