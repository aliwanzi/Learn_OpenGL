#version 420 core

layout (location = 0) in vec3 aPos;

out VS_OUT {
    vec3 WorldPos;
} vs_out;

uniform mat4 matModel;
uniform mat4 matView;
uniform mat4 matProjection;

void main()
{
	vs_out.WorldPos = aPos;

	vec4 clipPos = matProjection * mat4(mat3(matView)) * vec4(aPos, 1.0);

	gl_Position = clipPos.xyww;
}