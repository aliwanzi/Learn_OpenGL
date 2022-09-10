#version 420 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aColor;

out VS_OUT {
    vec3 color;
} vs_out;


void main()
{
	gl_Position =  vec4(aPos, 1.0);
	vs_out.color = aColor;
}