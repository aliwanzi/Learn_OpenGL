#version 420 core

layout (location = 0) in vec3 aPos;

out VS_OUT {
    vec2 texCoord;
} vs_out;

uniform mat4 matModel;
uniform mat4 matLightSpace;

void main()
{
	gl_Position = matLightSpace * matModel * vec4(aPos, 1.0);
}