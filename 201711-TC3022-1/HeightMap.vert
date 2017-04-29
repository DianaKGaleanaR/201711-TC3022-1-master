#version 330

in vec3 VertexPosition;
in vec2 VertexTexCoords;

out vec2 InterpolatedTexCoord;
out vec3 InterpolatedVertexPosition;

uniform mat4 mvpMatrix;
uniform sampler2D HeightMap;

void main()
{
	InterpolatedTexCoord = VertexTexCoords;
	InterpolatedVertexPosition= VertexPosition;

	//float displacement = texture2D(HeightMap, InterpolatedTexCoord).r*5.0f;
	float displacement = texture2D(HeightMap, InterpolatedTexCoord).r*3.0f;
	
	gl_Position = mvpMatrix * vec4(VertexPosition.x, VertexPosition.y + displacement, VertexPosition.z, 1.0f);
}