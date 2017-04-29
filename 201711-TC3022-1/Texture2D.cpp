#include "Texture2D.h"
#include <IL/il.h>

Texture2D::Texture2D()
{
	_textureId = 0; //ID
	_depth = 0;
	_width = 0;
	_imageColors;
}

Texture2D::~Texture2D()
{
	glDeleteTextures(1,&_textureId);
}

void Texture2D::Bind()
{
	glBindTexture(GL_TEXTURE_2D,_textureId);//TIPO DE TEXTURA(imagenes2d Y EL IDENTIFICADOR
}

void Texture2D::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);//TIPO DE TEXTURA(imagenes2d Y EL IDENTIFICADOR con 0 para unbind
}

void Texture2D::LoadTexture(std::string path)
{
	ILuint imageId;//identificador unde textura para devil
	ilGenImages(1, &imageId);//generar numero, de tal textura
	ilBindImage(imageId);
	ilLoadImage(path.c_str());//carga textura en version de 

	ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);//manejar RGBA y cada uno sera un unisgned byte(dato ligero y facil de render)

	glGenTextures(1, &_textureId);//numero y deonde guardar texturas
	Bind();
	//wrap, filter
	//filter
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//parametros enteros, TIPO DE TEXTURA,filtro,  minificar/aumentar textura(SON FILTROS)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//MIN
	//linear seria bilinear

	//wrap- especificar valores fuera de 0 a 1. 
	//clamp- acotar a 1
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);//s es ancho en textura
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);//t es alto en textura
	
	//mandar datos a tarjeta de video, estillo buffer data para mandar configuracion
	glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_FORMAT), ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData());
		//TIPO DE DATO, nivel de mitmaps- version reducida de texturaNINGUNA=0, internal formal como guardar datos, 2 datos(ancho, alto), sin borde, como guardar en open gl, cada uno es tipo de dato
	//cerrar
	Unbind();
	ilBindImage(0);
	ilDeleteImage(imageId);
}

void Texture2D::LoadTexture(GLint format, GLsizei width, GLsizei height, GLenum type, const void * pixels)
{
	glGenTextures(1, &_textureId);
	Bind();
	// Texture Filter
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	// Texture Wrap
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	// Cargar la información en la tarjeta de video
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, type, pixels);
	Unbind();
}

int Texture2D::GetDepth()
{
	_depth=ilGetInteger(IL_IMAGE_HEIGHT);
	return _depth;
};

int Texture2D::GetWidth()
{
	_width=ilGetInteger(IL_IMAGE_WIDTH);
	return _width;
};