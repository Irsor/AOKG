#include "Mesh.h"

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

	if (fin.is_open())
	{
		std::string str;
		std::cout << std::endl << "Файл " + filename + " успешно открыт!" << std::endl << std::endl;
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

				glm::mat3 matrix;

				//std::cout << "f " << atoi(helper[0].c_str()) << " " << atoi(helper[1].c_str()) << " " << atoi(helper[2].c_str());

				matrix[0][0] = GLfloat(atoi(helper[0].c_str()));
				matrix[0][1] = GLfloat(atoi(helper[1].c_str()));
				matrix[0][2] = GLfloat(atoi(helper[2].c_str()));

				helper[0] = "";
				helper[1] = "";
				helper[2] = "";

				j = 0;

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

				//std::cout << " " << atoi(helper[0].c_str()) << " " << atoi(helper[1].c_str()) << " " << atoi(helper[2].c_str());

				matrix[1][0] = GLfloat(atoi(helper[0].c_str()));
				matrix[1][1] = GLfloat(atoi(helper[1].c_str()));
				matrix[1][2] = GLfloat(atoi(helper[2].c_str()));

				helper[0] = "";
				helper[1] = "";
				helper[2] = "";

				j = 0;

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

				//std::cout << " " << atoi(helper[0].c_str()) << " " << atoi(helper[1].c_str()) << " " << atoi(helper[2].c_str()) << std::endl;

				matrix[2][0] = GLfloat(atoi(helper[0].c_str()));
				matrix[2][1] = GLfloat(atoi(helper[1].c_str()));
				matrix[2][2] = GLfloat(atoi(helper[2].c_str()));

				fPoints.push_back(matrix);
			}
		}

		for (int i = 0; i < fPoints.size(); i++)
		{
			Vertex vertex;
			glm::mat3 matrix = fPoints[i];

			vertex.coord[0] = v[matrix[0][0] - 1].x;
			vertex.coord[1] = v[matrix[0][0] - 1].y;
			vertex.coord[2] = v[matrix[0][0] - 1].z;

			vertex.texturCoord[0] = t[matrix[0][1] - 1].x;
			vertex.texturCoord[1] = t[matrix[0][1] - 1].y;
			vertex.texturCoord[2] = t[matrix[0][1] - 1].z;

			vertex.normal[0] = n[matrix[0][2] - 1].x;
			vertex.normal[1] = n[matrix[0][2] - 1].y;
			vertex.normal[2] = n[matrix[0][2] - 1].z;

			this->vertices.push_back(vertex);

			vertex.coord[0] = v[matrix[1][0] - 1].x;
			vertex.coord[1] = v[matrix[1][0] - 1].y;
			vertex.coord[2] = v[matrix[1][0] - 1].z;

			vertex.texturCoord[0] = t[matrix[1][1] - 1].x;
			vertex.texturCoord[1] = t[matrix[1][1] - 1].y;
			vertex.texturCoord[2] = t[matrix[1][1] - 1].z;

			vertex.normal[0] = n[matrix[1][2] - 1].x;
			vertex.normal[1] = n[matrix[1][2] - 1].y;
			vertex.normal[2] = n[matrix[1][2] - 1].z;

			this->vertices.push_back(vertex);

			vertex.coord[0] = v[matrix[2][0] - 1].x;
			vertex.coord[1] = v[matrix[2][0] - 1].y;
			vertex.coord[2] = v[matrix[2][0] - 1].z;

			vertex.texturCoord[0] = t[matrix[2][1] - 1].x;
			vertex.texturCoord[1] = t[matrix[2][1] - 1].y;
			vertex.texturCoord[2] = t[matrix[2][1] - 1].z;

			vertex.normal[0] = n[matrix[2][2] - 1].x;
			vertex.normal[1] = n[matrix[2][2] - 1].y;
			vertex.normal[2] = n[matrix[2][2] - 1].z;

			this->vertices.push_back(vertex);
		}

		fin.close();

		std::cout <<std::endl << "Файл " + filename + " успешно закрыт!" << std::endl;
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

	glDrawArrays(GL_TRIANGLES, 0, vertices.size());

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}

Vertex::Vertex() {};