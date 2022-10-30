#version 420 core
out vec4 FragColor;

in VS_OUT {
	vec3 FragPos;
    vec2 TexCoords;
	vec3 Normal;
	vec4 FragPosLightSpace;
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

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;

uniform float near_plane;
uniform float far_plane;
uniform bool bShadow;

float LinearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0;
    return (2.0 * near_plane * far_plane)/(far_plane + near_plane - z * (far_plane - near_plane));
}

float ShadowCalculation(vec4 fragPosLightSpace)
{
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    projCoords = projCoords * 0.5 + 0.5;
    if(projCoords.z > 1.0)
        return 0.f;
    float closestDepth = texture(texture_diffuse1,projCoords.xy).r;
    float currentDepth = projCoords.z;

    vec3 normal = normalize(fs_in.Normal);
    vec3 lightDir = normalize( pointLights[0].position - fs_in.FragPos);
    float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);

    float shadow = 0.0;
    vec2 texelSize = 1.0/(textureSize(texture_diffuse1,0));
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(texture_diffuse1, projCoords.xy + vec2(x, y) * texelSize).r; 
            //shadow += currentDepth - bias > pcfDepth  ? 1.0 : 0.0;
            shadow += currentDepth > pcfDepth  ? 1.0 : 0.0;  
        }    
    }
    shadow /= 9.0;
    return shadow;
}

void main()
{
    vec3 color = texture(texture_diffuse2,fs_in.TexCoords).rgb;
    vec3 normal = normalize(fs_in.Normal);

    vec3 ambient = pointLights[0].ambient;

    vec3 lightDir = normalize(pointLights[0].position - fs_in.FragPos);
    float diff = max(dot(lightDir,normal),0.0);
    vec3 diffuse = diff * pointLights[0].diffuse;

    vec3 viewDir = normalize(viewPos - fs_in.FragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal,halfwayDir),0.0),pointLights[0].shininess);
    vec3 specular = spec * pointLights[0].specular;

    float shadow = bShadow ? ShadowCalculation(fs_in.FragPosLightSpace) : 0.0;
    vec3 lighting = (ambient +(1.0-shadow)*(diffuse + specular))*color;

    FragColor = vec4(lighting,1.0);
}