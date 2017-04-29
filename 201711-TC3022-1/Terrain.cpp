#include <stdio.h>
#include "Terrain.h"
#include "Texture2D.h"

Terrain::Terrain() {
	positions;
	texCoords;
	indices;

	_texture;
}

void Terrain::Init(std::string path) {
	_texture;
	positions;
	texCoords;
	
	_texture.LoadTexture(path);

	hmWidth = _texture.GetWidth();
	hmDepth = _texture.GetDepth();
	size = hmWidth*hmDepth;

	//POS Y TEXCOORDS
	for (int i = 0; i < hmWidth; i++)
	{
		for (int j = 0; j < hmDepth; j++)
		{
			positions.push_back(glm::vec3(i, 0.0f, j));
			//texCoords.push_back(glm::vec2((float)i / (float)(hmWidth - 1), (float)j / (float)(hmDepth - 1)));
			//texCoords.push_back(glm::vec2(i, j));
			texCoords.push_back(glm::vec2((float)i / (float)(hmWidth - 1), (float)j / (float)(hmDepth - 1)));
		}
	}
	//INDICES
	indices;
	for (int i = 0; i<hmWidth - 1; i++)//evita hacer el triangulo del mas arriba, se detiene uno antes 
	{
		for (int j = 0; j<hmDepth - 1; j++)
		{
			int current = i*hmWidth + j;
			//primer triangulo
			indices.push_back(current);
			indices.push_back(current + hmDepth);
			indices.push_back(current + hmDepth + 1);

			//segundo
			indices.push_back(current);
			indices.push_back(current + hmDepth + 1);
			indices.push_back(current + 1);
		}
	}
}

std::vector<glm::vec3> Terrain::GetPositions()
{
	return positions;
}

std::vector<glm::vec3> Terrain::GetColors()
{
	return colors;
}

std::vector<glm::vec2> Terrain::GetTexCoords()
{
	return texCoords;
}

std::vector<unsigned int> Terrain::GetIndices()
{
	return indices;
}

int Terrain::GetDepth()
{
	return hmDepth;
}

int Terrain::GetWidth()
{
	return hmWidth;
}