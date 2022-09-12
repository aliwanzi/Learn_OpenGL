#version 420 core

out vec4 FragColor;

struct DirLight
{
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;

    vec3 color;
};

struct PointLight
{
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;

    vec3 color;

    float constant;
    float linear;
    float quadratic;
};

struct SpotLight
{
    vec3 position;
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;

    vec3 color;

    float constant;
    float linear;
    float quadratic;

    float cutOff;
    float outerCutOff;
};

#define NR_POINT_LIGHTS 4

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;
in vec3 Color;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;

uniform vec3 viewPos;
uniform DirLight dirLight;
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform SpotLight spotLight;

vec3 CalcDirLight(DirLight light,vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light,vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos,vec3 viewDir);

void main()
{
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 result = CalcDirLight(dirLight, norm, viewDir);
    for(int i = 0 ; i<NR_POINT_LIGHTS ; i++)
        result += CalcPointLight(pointLights[i], norm, FragPos,viewDir);
    result += CalcSpotLight(spotLight, norm, FragPos,viewDir);
    FragColor = vec4(result,1.0);
}

vec3 CalcDirLight(DirLight light,vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);

    float diff = max(dot(normal,lightDir),0.0);

    vec3 half = normalize(viewDir + lightDir);
    float spec = pow(max(dot(normal,half),0.0),light.shininess);

    vec3 ambient = light.ambient * light.color * Color;
    vec3 diffuse = light.diffuse * diff * light.color * Color;
    vec3 specular = light.specular *spec* light.color * Color;
    return ambient + diffuse + specular;
}

vec3 CalcPointLight(PointLight light,vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);

    float diff = max(dot(normal,lightDir),0.0);

    vec3 half = normalize(viewDir + lightDir);
    float spec = pow(max(dot(normal,half),0.0),light.shininess);

    float distance = length(light.position - fragPos);
    float attention = 1.0/(light.constant + light.linear * distance + light.quadratic *distance*distance );

    vec3 ambient = light.ambient * light.color * Color * attention ;
    vec3 diffuse = light.diffuse *  diff *light.color * Color * attention ;
    vec3 specular = light.specular * spec * light.color * Color * attention ;
    return ambient + diffuse + specular;
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos,vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);

    float diff = max(dot(normal,lightDir),0.0);

    vec3 half = normalize(viewDir+lightDir);
    float spec = pow(max(dot(normal,half),0.0),light.shininess);

    float distance = length(light.position - fragPos);
    float attention = 1.0/(light.constant + light.linear * distance + light.quadratic *distance*distance );

    float theta = dot(lightDir,normalize(-light.direction));
    float epsion = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta-light.outerCutOff)/epsion,0.0,1.0);

    vec3 ambient = light.ambient *  light.color * Color * attention * intensity;
    vec3 diffuse = light.diffuse * diff * light.color * Color *  attention * intensity;
    vec3 specular = light.specular *  spec * light.color * Color*  attention * intensity;
    return ambient + diffuse + specular;
}