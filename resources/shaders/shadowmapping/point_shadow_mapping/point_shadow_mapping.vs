#version 420 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;

out VS_OUT {
	vec3 FragPos;
    vec2 TexCoords;
	vec3 Normal;
} vs_out;

uniform bool reverse_normals;

uniform mat4 matModel;
uniform mat4 matView;
uniform mat4 matProjection;

void main()
{
	vs_out.FragPos = vec3(matModel * vec4(aPos,1.0));
	if(reverse_normals)
		vs_out.Normal = mat3(transpose(inverse(matModel)))* (-aNormal);
	else
		vs_out.Normal = mat3(transpose(inverse(matModel)))* (aNormal);

	vs_out.TexCoords = aTexCoord;
	gl_Position = matProjection * matView * vec4(vs_out.FragPos, 1.0);
}