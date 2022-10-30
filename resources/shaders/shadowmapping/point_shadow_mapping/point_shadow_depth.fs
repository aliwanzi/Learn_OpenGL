#version 420 core

in GS_OUT {
	vec4 FragPos;
} fs_in;

struct PointLight
{
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;

    float constant;
    float linear;
    float quadratic;
};

#define NR_POINT_LIGHTS 1

uniform PointLight pointLights[NR_POINT_LIGHTS];

uniform vec3 lightPos;
uniform float far_plane;

out vec4 FragColor;

void main()
{
    float lightDistance = (length(fs_in.FragPos.xyz - pointLights[0].position))/far_plane;

    gl_FragDepth = lightDistance;
    FragColor = vec4(vec3(lightDistance),1.0);
}