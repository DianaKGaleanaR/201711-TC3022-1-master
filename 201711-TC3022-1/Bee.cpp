#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <IL/il.h>
#include <iostream>
#include <vector>
#include "Bee.h"

Bee::Bee(){
	positions;
	texCoords;
	indices;
	colors;
}

void Bee::CreateBee() {
	positions;
	texCoords;
	indices;
	colors;
	// Cara trasera
	positions.push_back(glm::vec3(-1.0f, -1.0f, -1.0));
	positions.push_back(glm::vec3(1.0f, -1.0f, -1.0f));
	positions.push_back(glm::vec3(1.0f, 1.0f, -1.0f));
	positions.push_back(glm::vec3(-1.0f, 1.0f, -1.0f));
	// Cara derecha
	positions.push_back(glm::vec3(1.0f, -1.0f, -1.0f));
	positions.push_back(glm::vec3(1.0f, -1.0f, 1.0f));
	positions.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
	positions.push_back(glm::vec3(1.0f, 1.0f, -1.0f));
	// Cara frontal
	positions.push_back(glm::vec3(1.0f, -1.0f, 1.0f));
	positions.push_back(glm::vec3(-1.0f, -1.0f, 1.0f));
	positions.push_back(glm::vec3(-1.0f, 1.0f, 1.0f));
	positions.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
	// Cara izquierda
	positions.push_back(glm::vec3(-1.0f, -1.0f, 1.0f));
	positions.push_back(glm::vec3(-1.0f, -1.0f, -1.0f));
	positions.push_back(glm::vec3(-1.0f, 1.0f, -1.0f));
	positions.push_back(glm::vec3(-1.0f, 1.0f, 1.0f));
	// Cara arriba
	positions.push_back(glm::vec3(-1.0f, 1.0f, -1.0f));
	positions.push_back(glm::vec3(1.0f, 1.0f, -1.0f));
	positions.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
	positions.push_back(glm::vec3(-1.0f, 1.0f, 1.0f));
	// Cara abajo
	positions.push_back(glm::vec3(-1.0f, -1.0f, 1.0f));
	positions.push_back(glm::vec3(1.0f, -1.0f, 1.0f));
	positions.push_back(glm::vec3(1.0f, -1.0f, -1.0f));
	positions.push_back(glm::vec3(-1.0f, -1.0f, -1.0f));

	texCoords.push_back(glm::vec2(1.0f, 0.0f));
	texCoords.push_back(glm::vec2(1.0f, 1.0f));
	texCoords.push_back(glm::vec2(0.0f, 1.0f));
	texCoords.push_back(glm::vec2(0.0f, 0.0f));

	texCoords.push_back(glm::vec2(1.0f, 0.0f));
	texCoords.push_back(glm::vec2(1.0f, 1.0f));
	texCoords.push_back(glm::vec2(0.0f, 1.0f));
	texCoords.push_back(glm::vec2(0.0f, 0.0f));

	texCoords.push_back(glm::vec2(1.0f, 0.0f));
	texCoords.push_back(glm::vec2(1.0f, 1.0f));
	texCoords.push_back(glm::vec2(0.0f, 1.0f));
	texCoords.push_back(glm::vec2(0.0f, 0.0f));

	texCoords.push_back(glm::vec2(1.0f, 0.0f));
	texCoords.push_back(glm::vec2(1.0f, 1.0f));
	texCoords.push_back(glm::vec2(0.0f, 1.0f));
	texCoords.push_back(glm::vec2(0.0f, 0.0f));

	texCoords.push_back(glm::vec2(1.0f, 0.0f));
	texCoords.push_back(glm::vec2(1.0f, 1.0f));
	texCoords.push_back(glm::vec2(0.0f, 1.0f));
	texCoords.push_back(glm::vec2(0.0f, 0.0f));

	texCoords.push_back(glm::vec2(1.0f, 0.0f));
	texCoords.push_back(glm::vec2(1.0f, 1.0f));
	texCoords.push_back(glm::vec2(0.0f, 1.0f));
	texCoords.push_back(glm::vec2(0.0f, 0.0f));

	// Cara trasera
	colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	// Cara derecha
	colors.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	colors.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	colors.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	colors.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	// Cara frontal
	colors.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	colors.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	colors.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	colors.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	// Cara izquierda
	colors.push_back(glm::vec3(1.0f, 0.0f, 1.0f));
	colors.push_back(glm::vec3(1.0f, 0.0f, 1.0f));
	colors.push_back(glm::vec3(1.0f, 0.0f, 1.0f));
	colors.push_back(glm::vec3(1.0f, 0.0f, 1.0f));
	// Cara arriba
	colors.push_back(glm::vec3(0.0f, 1.0f, 1.0f));
	colors.push_back(glm::vec3(0.0f, 1.0f, 1.0f));
	colors.push_back(glm::vec3(0.0f, 1.0f, 1.0f));
	colors.push_back(glm::vec3(0.0f, 1.0f, 1.0f));
	// Cara abajo
	colors.push_back(glm::vec3(0.3f, 0.5f, 0.7f));
	colors.push_back(glm::vec3(0.3f, 0.5f, 0.7f));
	colors.push_back(glm::vec3(0.3f, 0.5f, 0.7f));
	colors.push_back(glm::vec3(0.3f, 0.5f, 0.7f));

	// Cara trasera
	normals.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
	normals.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
	normals.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
	normals.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
	// Cara derecha
	normals.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	normals.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	normals.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	normals.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	// Cara frontal
	normals.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	normals.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	normals.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	normals.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	// Cara izquierda
	normals.push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
	normals.push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
	normals.push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
	normals.push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
	// Cara arriba
	normals.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	normals.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	normals.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	normals.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	// Cara abajo
	normals.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
	normals.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
	normals.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
	normals.push_back(glm::vec3(0.0f, -1.0f, 0.0f));

	//std::vector<unsigned int> indices{ 0, 1, 2, 0, 2, 3, 4, 5, 6, 4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14, 12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22, 20, 22, 23 };
	std::vector<unsigned int> indicesDef{ 0, 1, 2, 0, 2, 3, 4, 5, 6, 4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14, 12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22, 20, 22, 23 };
	indices = indicesDef;
}

std::vector<glm::vec3> Bee::GetPositions()
{
	return positions;
}

std::vector<glm::vec2> Bee::GetTexCoords()
{
	return texCoords;
}

std::vector<glm::vec3> Bee::GetColors()
{
	return colors;
}

std::vector<glm::vec3> Bee::GetNormals()
{
	return normals;
}

std::vector<unsigned int> Bee::GetIndices()
{
	return indices;
}