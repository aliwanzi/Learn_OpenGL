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

uniform bool reverse_normals;

void main()
{
	vec4 viewPos = matView * matModel * vec4(aPos,1.0);
	vs_out.FragPos = viewPos.xyz;
	vs_out.TexCoords = aTexCoord;

	if(reverse_normals)
		vs_out.Normal = mat3(transpose(inverse(matView * matModel)))* (-aNormal);
	else
		vs_out.Normal = mat3(transpose(inverse(matView * matModel)))* (aNormal);

	gl_Position = matProjection * viewPos;
	
}