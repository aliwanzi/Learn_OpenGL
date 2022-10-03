#version 420 core

layout (location = 0) in vec3 aPos;
layout (location = 2) in vec3 aColor;

layout (location = 5) in vec2 offset;

out vec3 Color;

void main()
{
	vec2 pos = vec2(aPos) * (gl_InstanceID / 100.0);
	gl_Position = vec4(pos+offset,0.0,1.0);
	Color = aColor;
}