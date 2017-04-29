#version 330

in vec3 VertexPosition;
in vec2 VertexTexCoord; //diferente para cada vertices

out vec2 InterpolatedTexCoord;

uniform mat4 mvpMatrix;

void main()
{
	InterpolatedTexCoord = VertexTexCoord;
	gl_Position = mvpMatrix * vec4(VertexPosition, 1.0f); //COORDENADAS HOMOGENEAS. 1.0 es para multi de traslacion, coordenadas homogeneas 1- posicines. permite multiplicar por matriz (lo hace multiplicacion)

	//dar posicion final al vertice
}