#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <math.h>
#include <string>
#include <sstream>
#include <iostream>

#include "Texture2D.h"

class Bee {
public:
	Bee();
	void CreateBee();

	std::vector<glm::vec3> GetPositions();
	std::vector<glm::vec2> GetTexCoords();
	std::vector<glm::vec3> GetColors();
	std::vector<glm::vec3> GetNormals();
	std::vector<unsigned int> GetIndices();

private: 
	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> texCoords;
	std::vector<glm::vec3> colors;
	std::vector<glm::vec3> normals;
	std::vector<unsigned int> indices;
	Texture2D _textureBody;
	Texture2D _texture;
};