#version 420 core
layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

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

#define NR_POINT_LIGHTS 4
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform vec3 viewPos;

in VS_OUT {
    vec3 FragPos;
    vec2 TexCoords;
	vec3 Normal;
} fs_in;

uniform sampler2D texture_diffuse1;

void main()
{
    vec3 color = texture(texture_diffuse1, fs_in.TexCoords).rgb;
    vec3 normal = normalize(fs_in.Normal);

    vec3 lighting = vec3(0.0);
    vec3 viewDir = normalize(viewPos - fs_in.FragPos);
    for(int i =0;i<NR_POINT_LIGHTS;i++)
    {
        vec3 ambient = pointLights[i].ambient * color;

        vec3 lightDir = normalize(pointLights[i].position - fs_in.FragPos);
        float diff = max(dot(lightDir,normal),0.0);
        vec3 diffuse = pointLights[i].diffuse * diff * color;

        float distance = length(fs_in.FragPos-pointLights[i].position);

        ambient *= 1.0/(distance*distance);
        diffuse *= 1.0/(distance*distance);
        lighting += ambient+diffuse;
    }

   FragColor = vec4(lighting, 1.0);

    float brightness = dot(lighting,vec3(0.2126,0.7152,0.0722));
    if(brightness > 1.0)
        BrightColor = vec4(lighting,1.0);
    else
        BrightColor = vec4(0.0,0.0,0.0,1.0);

}