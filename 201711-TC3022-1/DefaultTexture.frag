#version 330 

in vec2 InterpolatedTexCoord; 
in vec3 InterpolatedColor;

out vec4 FragColor;

uniform sampler2D BeeTexture; //textura en dos dimensiones es un tipo de dato, es reconocido como numero entero!
//
uniform sampler2D BeeBodyTexture; 

void main()
{
	FragColor= texture2D(BeeTexture, InterpolatedTexCoord);
}