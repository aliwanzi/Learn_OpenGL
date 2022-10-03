#version 420 core

layout (location = 0) in vec3 aPos;
layout (location = 2) in vec3 aNormal;

out VS_OUT {
	vec3 Normal;
} vs_out;

uniform mat4 matModel;
uniform mat4 matView;

void main()
{
	vs_out.Normal = mat3(transpose(inverse(matView * matModel))) * aNormal;

	gl_Position = matView * matModel * vec4(aPos, 1.0);
}