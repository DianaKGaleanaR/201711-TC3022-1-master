#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <math.h>
#include <string>
#include <sstream>
#include <iostream>

#include "Texture2D.h"

class Display {
public:
	Display();
	void Init();

	std::vector<glm::vec3> GetPositions();
	std::vector<glm::vec2> GetTexCoords();
	std::vector<unsigned int> GetIndices();

private:
	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> texCoords;
	std::vector<unsigned int> indices;

	int vertexCount;
	Texture2D _texture;
};