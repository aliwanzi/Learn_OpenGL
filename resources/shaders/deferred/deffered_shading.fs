#version 420 core

out vec4 FragColor;

in VS_OUT {
    vec2 TexCoords;
} fs_in;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_diffuse3;

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

    float radius;
};

const int NR_LIGHTS=32;
uniform PointLight pointLights[NR_LIGHTS];
uniform vec3 viewPos;

void main()
{
      vec3 FragPos = texture(texture_diffuse1, fs_in.TexCoords).rgb;
      vec3 Normal = texture(texture_diffuse2, fs_in.TexCoords).rgb;
      vec3 Diffuse = texture(texture_diffuse3, fs_in.TexCoords).rgb;
      float Specular = texture(texture_diffuse3, fs_in.TexCoords).a;
      
      vec3 lighting = Diffuse * 0.5;
      vec3 viewDir = normalize(viewPos - FragPos);
      for (int i = 0; i < NR_LIGHTS; ++i)
      {
          float distance = length(pointLights[i].position - FragPos);
          if(distance < pointLights[i].radius)
          {
              vec3 lightDir = normalize(pointLights[i].position - FragPos);
              vec3 diffuse = max(dot(Normal, lightDir), 0.0) * Diffuse * pointLights[i].diffuse;
      
              vec3 halfwayDir = normalize(lightDir + viewDir);
              float spec = pow(max(dot(Normal, halfwayDir), 0.0), pointLights[i].shininess);
              vec3 specular = pointLights[i].specular * spec * Specular;
      
              float attenuation = 1.0 / (pointLights[i].constant + pointLights[i].linear * distance + pointLights[i].quadratic * distance * distance);
          
              diffuse *= attenuation;
              specular *= attenuation;
              lighting += diffuse + specular;
           }
      }
      FragColor = vec4(lighting, 1.0);
}