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
uniform float heightScale;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_diffuse3;

vec2 ParallaxMapping0(vec2 texCoords, vec3 viewDir)
{
    float height = texture(texture_diffuse3,texCoords).r;
    return texCoords - viewDir.xy * (height * heightScale);
}

vec2 ParallaxMapping1(vec2 texCoords, vec3 viewDir)
{
    const float minLayers = 8;
    const float maxLayers = 32;
    float numLayers = mix(maxLayers,minLayers,abs(dot(vec3(0.0,0.0,1.0),viewDir)));
    float layerDepth = 1.0 / numLayers;
    float currentLayerDepth = 0.0;
    vec2 P = viewDir.xy/viewDir.z * heightScale;
    vec2 deltaTexCoords = P / numLayers;

    vec2 currentTexCoords = texCoords;
    float currentDepthMapValue = texture(texture_diffuse3,currentTexCoords).r;

    while(currentLayerDepth < currentDepthMapValue)
    {
        currentTexCoords -= deltaTexCoords;
        currentDepthMapValue = texture(texture_diffuse3,currentTexCoords).r;
        currentLayerDepth += layerDepth;
    }
    return currentTexCoords;
}

vec2 ParallaxMapping2(vec2 texCoords, vec3 viewDir)
{
    const float minLayers = 8;
    const float maxLayers = 32;
    float numLayers = mix(maxLayers,minLayers,abs(dot(vec3(0.0,0.0,1.0),viewDir)));
    float layerDepth = 1.0 / numLayers;
    float currentLayerDepth = 0.0;
    vec2 P = viewDir.xy/viewDir.z * heightScale;
    vec2 deltaTexCoords = P / numLayers;

    vec2 currentTexCoords = texCoords;
    float currentDepthMapValue = texture(texture_diffuse3,currentTexCoords).r;

    while(currentLayerDepth < currentDepthMapValue)
    {
        currentTexCoords -= deltaTexCoords;
        currentDepthMapValue = texture(texture_diffuse3,currentTexCoords).r;
        currentLayerDepth += layerDepth;
    }

    vec2 prevTexCoords = currentTexCoords + deltaTexCoords;
    float beforeDepth = texture(texture_diffuse3,prevTexCoords).r - currentLayerDepth + layerDepth;

    float afterDepth = currentLayerDepth - currentDepthMapValue;
    float weight = beforeDepth / (afterDepth+beforeDepth);
    vec2 finalTexCoords = currentTexCoords * weight + prevTexCoords * (1.0 - weight);

    return finalTexCoords;
}

void main()
{
    vec3 ambient = pointLights[0].ambient;
    vec3 diffuse = vec3(0.0);
    vec3 specular = vec3(0.0);

    if(bShadow)
    {
        vec3 color = texture(texture_diffuse1,fs_in.TexCoords).rgb;

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
        FragColor = vec4(lighting,1.0);
    }
    else
    {
        vec3 viewDir = normalize(fs_in.TangentViewPos - fs_in.TangentFragPos);

        vec2 texCoords = ParallaxMapping2(fs_in.TexCoords, viewDir);
        if(texCoords.x > 1.0 || texCoords.y > 1.0 || texCoords.x < 0.0 || texCoords.y < 0.0)
            discard;

        vec3 color = texture(texture_diffuse1,texCoords).rgb;

        vec3 normal = texture(texture_diffuse2,texCoords).rgb;
        normal = normalize(normal * 2.0 - 1.0);

        vec3 lightDir = normalize(fs_in.TangentLightPos - fs_in.TangentFragPos);
        float diff = max(dot(lightDir,normal),0.0);
        diffuse = diff * pointLights[0].diffuse;

        vec3 halfwayDir = normalize(lightDir + viewDir);
        float spec = pow(max(dot(normal,halfwayDir),0.0),pointLights[0].shininess);
        specular = spec * pointLights[0].specular;

        vec3 lighting = (ambient + diffuse + specular) * color;
        FragColor = vec4(lighting,1.0);
    }
}