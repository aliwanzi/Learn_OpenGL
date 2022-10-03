#version 420 core

layout (location = 0) in vec3 aPos;

out VS_OUT {
    vec3 texCoord;
} vs_out;

uniform mat4 matView;
uniform mat4 matProjection;

void main()
{
	vec4 pos = matProjection * matView  * vec4(aPos, 1.0);
	gl_Position = pos.xyww;
	vs_out.texCoord = aPos;
}