#version 420 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out VS_OUT {
    vec2 texCoord;
} vs_out;

uniform mat4 matModel;
uniform mat4 matView;
uniform mat4 matProjection;

void main()
{
	vs_out.texCoord = aTexCoord;
	gl_Position = matProjection * matView * matModel * vec4(aPos, 1.0);
	gl_PointSize = gl_Position.z + 5.0;    
}