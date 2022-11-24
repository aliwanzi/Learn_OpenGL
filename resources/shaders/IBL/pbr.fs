#version 420 core

out vec4 FragColor;

in VS_OUT {
	vec3 FragPos;
    vec2 TexCoords;
	vec3 Normal;
} fs_in;

const float PI = 3.14159265359;

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

const int NR_LIGHTS=4;
uniform PointLight pointLights[NR_LIGHTS];

uniform vec3 viewPos;

uniform vec3 albedo;
uniform float metallic;
uniform float roughness;
uniform float ao;

float DistributionGGX(vec3 N,vec3 H,float roughness)
{
    float a = roughness * roughness;
    float NdotH = max(dot(N,H),0.0);
    float denom = NdotH * NdotH * (a-1.0) + 1;
    denom = PI * denom * denom;

    return a/denom;
}

float GeometrySchlickGGX(float NdotV,float k)
{
    float denom = NdotV * (1.0 - k) + k;
    return NdotV / denom;
}

float GeometrySmith(vec3 N,vec3 V,vec3 L,float k)
{
    float NdotV = max(dot(N,V),0.0);
    float NdotL = max(dot(N,L),0.0);

    float ggx1 = GeometrySchlickGGX(NdotV,k);
    float ggx2 = GeometrySchlickGGX(NdotL,k);
    return ggx1 * ggx2;
}

vec3 fresnelSchlick(vec3 H,vec3 V)
{
    float HdotV = max(dot(H,V),0.0);

    vec3 F0 = mix(vec3(0.04),albedo,metallic);

    return F0+(1.0-F0) * pow(1.0-HdotV,5.0);
}

void main()
{
    vec3 N = fs_in.Normal;
    vec3 V = normalize(viewPos - fs_in.FragPos);

    vec3 Lo = vec3(0.0);
    for(int i=0;i<4;++i)
    {
        vec3 L = normalize(pointLights[i].position - fs_in.FragPos);
        vec3 H = normalize(V + L);
        float distance = length(pointLights[i].position - fs_in.FragPos);
        float attenuation = 1.0/(distance*distance);
        vec3 radiance = pointLights[i].diffuse * attenuation;

        // Cook-Torrance BRDF
        float NDF = DistributionGGX(N, H, roughness);   
        float G   = GeometrySmith(N, V, L, roughness);      
        vec3 F    = fresnelSchlick(max(dot(H, V), 0.0), F0);

        vec3 numerator = F;
        float denominator = 4.0 * max(dot(N,V),0.0) * max(dot(N,L),0.0) + 0.0001;
        vec3 specular = numerator / denominator;

        vec3 kS = F;
        vec3 kD = vec3(1.0) - kS;

        kD *= (1.0 - metallic);

        float NdotL = max(dot(N,L),0.0);

        Lo += (kD * albedo / PI + specular) * radiance * NdotL;

    }

    vec3 ambient = albedo * ao;

    vec3 color = ambient + Lo;

    color = color /(color + vec3(1.0));

    color = pow (color ,vec3(1.0/2.0));

    FragColor = vec4(color,1.0);
}