#version 420 core

layout (location = 0) in vec3 aPos;

uniform mat4 matModel;
uniform mat4 matLightSpace;

void main()
{
	gl_Position = matLightSpace * matModel * vec4(aPos, 1.0);
}