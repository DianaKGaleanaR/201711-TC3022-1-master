#version 330 

in vec2 InterpolatedTexCoord; 
in vec3 InterpolatedColor;

out vec4 FragColor;

uniform sampler2D DisplayTexture; //textura en dos dimensiones es un tipo de dato, es reconocido como numero entero!
//
void main()
{
	FragColor= texture2D(DisplayTexture, InterpolatedTexCoord);
}