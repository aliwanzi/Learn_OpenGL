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

    vec3 diffuse;
};

const int NR_LIGHTS=4;
uniform PointLight pointLights[NR_LIGHTS];

uniform samplerCube texture_cube_map1;
uniform samplerCube texture_cube_map2;
uniform vec3 viewPos;

// material parameters
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_diffuse3;
uniform sampler2D texture_diffuse4;
uniform sampler2D texture_diffuse5;
uniform sampler2D texture_diffuse6;


vec3 GetNormal()
{
    vec3 tangentNormal = texture(texture_diffuse6,fs_in.TexCoords).xyz * 2.0 - 1.0;

    vec3 Q1 = dFdx(fs_in.FragPos);
    vec3 Q2 = dFdy(fs_in.FragPos);
    vec2 st1 = dFdx(fs_in.TexCoords);
    vec2 st2 = dFdy(fs_in.TexCoords);

    vec3 N = normalize(fs_in.Normal);
    vec3 T = normalize(Q1*st2.t - Q2*st1.t);
    vec3 B = - normalize(cross(N,T));

    mat3 TBN = mat3(T,B,N);

    return normalize(TBN*tangentNormal);
}

float DistributionGGX(vec3 N,vec3 H,float roughness)
{
    float a = roughness * roughness;
    float a2 = a*a;

    float NdotH = max(dot(N,H),0.0);
    float denom = NdotH * NdotH * (a2-1.0) + 1.0;
    denom = PI * denom * denom;

    return a2/denom;
}

float GeometrySchlickGGX(float NdotV,float roughness)
{
    float r = (roughness + 1.0);
    float k = (r*r)/8.0;

    float nom   = NdotV;
    float denom = NdotV * (1.0 - k) + k;

    return nom / denom;
}

float GeometrySmith(vec3 N,vec3 V,vec3 L,float k)
{
    float NdotV = max(dot(N,V),0.0);
    float NdotL = max(dot(N,L),0.0);

    float ggx1 = GeometrySchlickGGX(NdotV,k);
    float ggx2 = GeometrySchlickGGX(NdotL,k);
    return ggx1 * ggx2;
    
}

vec3 fresnelSchlick(vec3 H,vec3 V,vec3 F0)
{
    float HdotV = max(dot(H,V),0.0);
    return F0+(1.0-F0) * pow(clamp(1.0 - HdotV, 0.0, 1.0),5.0);
}

vec3 fresnelSchlickRoughness(vec3 H,vec3 V, vec3 F0, float roughness)
{
    float HdotV = max(dot(H,V),0.0);
    return F0 + (max(vec3(1.0 - roughness), F0) - F0) * pow(clamp(1.0 - HdotV, 0.0, 1.0), 5.0);
}   

void main()
{
    vec3 albedo = pow(texture(texture_diffuse2,fs_in.TexCoords).rgb,vec3(2.2));
    float metallic = texture(texture_diffuse3,fs_in.TexCoords).r;
    float roughness = texture(texture_diffuse4,fs_in.TexCoords).r;
    float ao = texture(texture_diffuse5,fs_in.TexCoords).r;

   vec3  F0 = mix(vec3(0.04),albedo,metallic);
    vec3 N = GetNormal();
    vec3 V = normalize(viewPos - fs_in.FragPos);
    vec3 R = reflect(-V, N); 

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
        vec3 F    = fresnelSchlick(H, V, F0);

        vec3 numerator = NDF * G * F; 
        float denominator = 4.0 * max(dot(N,V),0.0) * max(dot(N,L),0.0) + 0.0001;
        vec3 specular = numerator / denominator;

        vec3 kS = F;
        vec3 kD = vec3(1.0) - kS;

        kD *= (1.0 - metallic);

        float NdotL = max(dot(N,L),0.0);

        Lo += (kD * albedo / PI + specular) * radiance * NdotL;

    }

    vec3 kS = fresnelSchlickRoughness(N, V, F0,roughness);

    //specular
    const float MAX_REFLECTION_LOD = 4.0;
    vec3 prefilteredColor = textureLod(texture_cube_map2,R,roughness * MAX_REFLECTION_LOD).rgb;
    vec2 brdf = texture(texture_diffuse6,vec2(max(dot(N,V),0.0),roughness)).rg;
    vec3 specular = prefilteredColor *(kS*brdf.x + brdf.y);

    //ambient
    vec3 kD = vec3(1.0) - kS;
    kD *= (1.0 - metallic);

    vec3 irradiance = texture(texture_cube_map1,N).rgb;
    vec3 diffuse = irradiance * albedo;

    vec3 ambient = (kD * diffuse + specular) * ao;
    vec3 color = ambient + Lo;

    color = color/(color+vec3(1.0));

    color = pow(color,vec3(1.0/2.2));

    FragColor = vec4(Lo,1.0);
}