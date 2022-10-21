#version 420 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;

out VS_OUT {
	vec3 FragPos;
    vec2 TexCoords;
	vec3 Normal;
} vs_out;

uniform mat4 matModel;
uniform mat4 matView;
uniform mat4 matProjection;

void main()
{
	vec4 worldPos = matModel * vec4(aPos,1.0);
	vs_out.FragPos = worldPos.xyz;
	vs_out.TexCoords = aTexCoord;

	mat3 normalMatrix = transpose(inverse(mat3(matModel)));
	vs_out.Normal=normalMatrix*aNormal;

	gl_Position = matProjection * matView * worldPos;
	
}