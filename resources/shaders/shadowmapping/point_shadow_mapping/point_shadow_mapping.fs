#version 420 core
out vec4 FragColor;

in VS_OUT {
	vec3 FragPos;
    vec2 TexCoords;
	vec3 Normal;
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
uniform samplerCube texture_cube_map1;

uniform float near_plane;
uniform float far_plane;

uniform bool bShadow;

float ShadowCalculation0(vec3 fragPos)
{
    vec3 fragToLight = fragPos - pointLights[0].position;
    float closetDepth = texture(texture_cube_map1,fragToLight).r;

    closetDepth *= far_plane;
    float currentDepth = length(fragToLight);

    float bias = 0.05;
    float shadow = currentDepth-bias> closetDepth ?1.0:0.0;
    return shadow;
}

float ShadowCalculation1(vec3 fragPos)
{
    vec3 fragToLight = fragPos - pointLights[0].position;
    float currentDepth = length(fragToLight);

    float shadow = 0.0;
    float bias = 0.05;
    float samples = 4.0;
    float offset = 0.1;
    for(float x = -offset; x<offset; x += offset/(samples*0.5))
    {
        for(float y = -offset; y < offset; y += offset/(samples*0.5))
        {
            for(float z = -offset; z < offset; z += offset/(samples*0.5))
            {
                float closetDepth = texture(texture_cube_map1,fragToLight + vec3(x,y,z)).r;
                closetDepth *= far_plane;
                if(currentDepth - bias > closetDepth)
                    shadow += 1.0;
            }
        }
    }
    shadow /= (samples*samples*samples);
    return shadow;
}

float ShadowCalculation2(vec3 fragPos)
{
    vec3 fragToLight = fragPos - pointLights[0].position;
    float currentDepth = length(fragToLight);

    float shadow = 0.0;
    float bias = 0.15;
    float samples =20.0;
    float offset = 0.05;

    vec3 sampleOffsetDirections[20] = vec3[]
    (
       vec3( 1,  1,  1), vec3( 1, -1,  1), vec3(-1, -1,  1), vec3(-1,  1,  1), 
       vec3( 1,  1, -1), vec3( 1, -1, -1), vec3(-1, -1, -1), vec3(-1,  1, -1),
       vec3( 1,  1,  0), vec3( 1, -1,  0), vec3(-1, -1,  0), vec3(-1,  1,  0),
       vec3( 1,  0,  1), vec3(-1,  0,  1), vec3( 1,  0, -1), vec3(-1,  0, -1),
       vec3( 0,  1,  1), vec3( 0, -1,  1), vec3( 0, -1, -1), vec3( 0,  1, -1)
    );
    

    for(int i=0;i<samples;++i)
    {
        float closetDepth = texture(texture_cube_map1,fragToLight + sampleOffsetDirections[i] * offset).r;
        closetDepth *= far_plane;
        if(currentDepth - bias > closetDepth)
            shadow += 1.0; 
    }
    shadow /= samples;
    return shadow;
}

void main()
{
    vec3 color = texture(texture_diffuse1,fs_in.TexCoords).rgb;
    vec3 normal = normalize(fs_in.Normal);

    vec3 ambient = pointLights[0].ambient;

    vec3 lightDir = normalize(pointLights[0].position - fs_in.FragPos);
    float diff = max(dot(lightDir,normal),0.0);
    vec3 diffuse = diff * pointLights[0].diffuse;

    vec3 viewDir = normalize(viewPos - fs_in.FragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal,halfwayDir),0.0),pointLights[0].shininess);
    vec3 specular = spec * pointLights[0].specular;

    float shadow = bShadow ? ShadowCalculation2(fs_in.FragPos) : 0.0;

    vec3 lighting = (ambient +(1.0-shadow)*(diffuse + specular))*color;

    FragColor = vec4(lighting,1.0);
}