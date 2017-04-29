#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <math.h>
#include <string>
#include <sstream>
#include <iostream>

#include "Texture2D.h"

class Terrain {
public:
	Terrain();
	void Init(std::string path);

	std::vector<glm::vec3> GetPositions();
	std::vector<glm::vec3> GetColors();
	std::vector<glm::vec2> GetTexCoords();
	std::vector<unsigned int> GetIndices();

	int GetDepth();
	int GetWidth();

private:
	int hmDepth;
	int hmWidth;
	int size;

	std::vector<glm::vec3> positions;
	std::vector<glm::vec3> colors;
	std::vector<glm::vec2> texCoords;
	std::vector<unsigned int> indices;

	int vertexCount;
	Texture2D _texture;
};
