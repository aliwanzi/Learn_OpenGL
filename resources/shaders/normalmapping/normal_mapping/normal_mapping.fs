#version 420 core
out vec4 FragColor;

in VS_OUT {
	vec3 FragPos;
    vec2 TexCoords;
    vec3 Normal;
	vec3 TangentLightPos;
	vec3 TangentViewPos;
	vec3 TangentFragPos;
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
uniform vec3 viewPos;
uniform bool bShadow;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;

void main()
{
    vec3 color = texture(texture_diffuse1,fs_in.TexCoords).rgb;
    vec3 ambient = pointLights[0].ambient;
    vec3 diffuse = vec3(0.0);
    vec3 specular = vec3(0.0);

    if(!bShadow)
    {
        vec3 normal = texture(texture_diffuse2,fs_in.TexCoords).rgb;
        normal = normalize(normal * 2.0 - 1.0);

        vec3 lightDir = normalize(fs_in.TangentLightPos - fs_in.TangentFragPos);
        float diff = max(dot(lightDir,normal),0.0);
        diffuse = diff * pointLights[0].diffuse;

        vec3 viewDir = normalize(fs_in.TangentViewPos - fs_in.TangentFragPos);
        vec3 halfwayDir = normalize(lightDir + viewDir);
        float spec = pow(max(dot(normal,halfwayDir),0.0),pointLights[0].shininess);
        specular = spec * pointLights[0].specular;

        vec3 lighting = (ambient + diffuse + specular) * color;
        FragColor = vec4(diffuse,1.0);
    }
    else
    {
        //vec3 normal = normalize(fs_in.Normal);
        vec3 normal = texture(texture_diffuse2,fs_in.TexCoords).rgb;
        normal = normalize(normal * 2.0 - 1.0);
        vec3 lightDir = normalize(pointLights[0].position - fs_in.FragPos);
        float diff = max(dot(lightDir,normal),0.0);
        vec3 diffuse = diff * pointLights[0].diffuse;

        vec3 viewDir = normalize(viewPos - fs_in.FragPos);
        vec3 halfwayDir = normalize(lightDir + viewDir);
        float spec = pow(max(dot(normal,halfwayDir),0.0),pointLights[0].shininess);
        vec3 specular = spec * pointLights[0].specular;

        vec3 lighting = (ambient + diffuse + specular) * color;
        FragColor = vec4(lighting,1.0);
    }
}