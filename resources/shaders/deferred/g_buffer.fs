#version 420 core

out vec4 FragColor;

layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec4 gAlbedoSpec;


in VS_OUT {
    vec3 FragPos;
    vec2 TexCoords;
	vec3 Normal;
} fs_in;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;

void main()
{
   gPosition = fs_in.FragPos;
   gNormal = normalize(fs_in.Normal);
   gAlbedoSpec.rgb = texture(texture_diffuse1,fs_in.TexCoords).rgb;
   gAlbedoSpec.a = texture(texture_specular1,fs_in.TexCoords).r;
   //FragColor = texture(texture_diffuse1, fs_in.TexCoords);
}