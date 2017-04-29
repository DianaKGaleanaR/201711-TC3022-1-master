#include <stdio.h>
#include "Display.h"
#include "Texture2D.h"

Display::Display() {
	positions;
	texCoords;
	indices;

	_texture;
}

void Display::Init() {
	positions;
	texCoords;
	indices;

	positions.push_back(glm::vec3(-1.0f, -1.0f, -1.0));
	positions.push_back(glm::vec3(1.0f, -1.0f, -1.0f));
	positions.push_back(glm::vec3(1.0f, 1.0f, -1.0f));
	positions.push_back(glm::vec3(-1.0f, 1.0f, -1.0f));

	texCoords.push_back(glm::vec2(1.0f, 0.0f));
	texCoords.push_back(glm::vec2(1.0f, 1.0f));
	texCoords.push_back(glm::vec2(0.0f, 1.0f));
	texCoords.push_back(glm::vec2(0.0f, 0.0f));

	std::vector<unsigned int> indicesDef{0,1,2,0,2,3}; 

	indices = indicesDef;
}

std::vector<glm::vec3> Display::GetPositions()
{
	return positions;
}

std::vector<glm::vec2> Display::GetTexCoords()
{
	return texCoords;
}

std::vector<unsigned int> Display::GetIndices()
{
	return indices;
}