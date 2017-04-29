#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <math.h>
#include <string>
#include <sstream>
#include <iostream>

#include "Texture2D.h"
#include "InputFile.h"
#include "ShaderProgram.h"
#include "Mesh.h"

class Texture2D
{
public:
	Texture2D();
	~Texture2D();

	void LoadTexture(std::string path);//arga texture, 
	void LoadTexture(GLint format, GLsizei width, GLsizei height, GLenum type, const void* pixels);

	void Bind();//activate
	void Unbind();//unactivate

	int GetDepth();
	int GetWidth();

private:
	GLuint _textureId;//identificador
	GLuint _depth;
	GLuint _width;

	std::vector<glm::vec3> _imageColors;

};