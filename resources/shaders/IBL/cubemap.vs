#version 420 core

layout (location = 0) in vec3 aPos;

out VS_OUT {
	vec3 FragPos;
} vs_out;

uniform mat4 matView;
uniform mat4 matProjection;

void main()
{
	vs_out.FragPos = aPos;
	gl_Position =  matProjection * matView * vec4(aPos, 1.0);
}