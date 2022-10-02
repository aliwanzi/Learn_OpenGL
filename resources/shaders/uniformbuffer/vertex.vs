#version 420 core

layout (location = 0) in vec3 aPos;

layout(std140) uniform Matrices
{
	mat4 matView;
	mat4 matProjection;
};

uniform mat4 matModel;

void main()
{
	gl_Position = matProjection * matView * matModel * vec4(aPos, 1.0);
}