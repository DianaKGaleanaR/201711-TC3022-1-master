#version 330

in vec2 InterpolatedTexCoord;
in vec3 InterpolatedVertexPosition;

out vec4 FragColor;

uniform sampler2D DiffuseTexture;
uniform sampler2D HeightMap;

void main()
{
	float colorModification;
	float height= texture2D(HeightMap, InterpolatedTexCoord).r;
	if (height<=1.0f && height>0.9f)
	{
		colorModification= 0.2f;
	}
	FragColor = texture2D(DiffuseTexture, InterpolatedTexCoord)-colorModification;
}