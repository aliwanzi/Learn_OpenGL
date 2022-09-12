#version 420 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in vec3 aTangent;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;
out vec3 Color;

uniform mat4 matModel;
uniform mat4 matView;
uniform mat4 matProjection;

void main()
{
	FragPos = vec3(matModel * vec4(aPos,1.0));
	Normal = mat3(transpose(inverse(matModel)))* aNormal;
	TexCoords = aTexCoord;
	Color = aTangent;

	gl_Position = matProjection * matView * vec4(FragPos, 1.0);
}