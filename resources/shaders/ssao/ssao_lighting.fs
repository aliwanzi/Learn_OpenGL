#version 420 core

out vec4 FragColor;

in VS_OUT {
    vec2 TexCoords;
} fs_in;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_diffuse3;
uniform sampler2D texture_diffuse4;

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

const int NR_LIGHTS=1;
uniform PointLight pointLights[NR_LIGHTS];

uniform mat4 matView;

uniform bool bSSAO;

void main()
{
      vec3 FragPos = texture(texture_diffuse1, fs_in.TexCoords).rgb;
      vec3 Normal = texture(texture_diffuse2, fs_in.TexCoords).rgb;
      vec3 Diffuse = texture(texture_diffuse3, fs_in.TexCoords).rgb;

      vec3 ambient=vec3(0.0);
      if(bSSAO)
      {
        float AmbientOcclusion = texture(texture_diffuse4, fs_in.TexCoords).r;
        
        ambient = pointLights[0].ambient * Diffuse * AmbientOcclusion;
      }
      else
      {
         ambient = pointLights[0].ambient * Diffuse;
      }


      vec3 viewDir = normalize( - FragPos);
      vec3 lightPosition = mat3(matView) * pointLights[0].position;

      vec3 lightDir = normalize(lightPosition - FragPos);
      vec3 diffuse = max(dot(Normal, lightDir), 0.0) * Diffuse * pointLights[0].diffuse;
      
      vec3 halfwayDir = normalize(lightDir + viewDir);
      float spec = pow(max(dot(Normal, halfwayDir), 0.0), pointLights[0].shininess);
      vec3 specular = pointLights[0].specular * spec;
      
      float distance = length(pointLights[0].position - FragPos);
      float attenuation = 1.0 / (pointLights[0].constant + pointLights[0].linear * distance + pointLights[0].quadratic * distance * distance);
          
      diffuse *= attenuation;
      specular *= attenuation;
      vec3 lighting = ambient + diffuse + specular;

      FragColor = vec4(lighting, 1.0);
}