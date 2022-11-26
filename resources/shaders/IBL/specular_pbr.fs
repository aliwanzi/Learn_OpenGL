#version 420 core

out vec4 FragColor;

in VS_OUT {
	vec3 FragPos;
} fs_in;

uniform samplerCube texture_cube_map1;
uniform float roughness;
const float PI = 3.14159265359;

struct PointLight
{
    vec3 position;

    vec3 diffuse;
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
    float a2 = a*a;

    float NdotH = max(dot(N,H),0.0);
    float denom = NdotH * NdotH * (a2-1.0) + 1.0;
    denom = PI * denom * denom;

    return a2/denom;
}

float RadicalInverse_VdC(uint bits) 
{
     bits = (bits << 16u) | (bits >> 16u);
     bits = ((bits & 0x55555555u) << 1u) | ((bits & 0xAAAAAAAAu) >> 1u);
     bits = ((bits & 0x33333333u) << 2u) | ((bits & 0xCCCCCCCCu) >> 2u);
     bits = ((bits & 0x0F0F0F0Fu) << 4u) | ((bits & 0xF0F0F0F0u) >> 4u);
     bits = ((bits & 0x00FF00FFu) << 8u) | ((bits & 0xFF00FF00u) >> 8u);
     return float(bits) * 2.3283064365386963e-10; // / 0x100000000
}

vec2 Hammersley(uint i, uint N)
{
    return vec2(float(i)/float(N),RadicalInverse_VdC(i));
}

vec3 ImportanceSamleGGX(vec2 Xi,vec3 N,float roughness)
{
    float a = roughness * roughness;
    float phi = 2.0 * PI * Xi.x;
    float cosTheta = sqrt((1.0 - Xi.y)/(1.0+(a*a - 1.0) * xi.y));
    float sinTheta = sqrt(1.0 - cosTheta * cosTheta);

    vec3 H;
    H.x = cos(phi) * sinTheta;
    H.y = sin(phi) * sinTheta;
    H.z = cosTheta;

    vec3 up = abs(N.z)<0.999?vec3(0.0,0.0,1.0):vec3(1.0,0.0,0.0);
    vec3 tangent = normalize( cross(up,N));
    vec3 bitangent = cross(N,tangent);
    vec3 sampleVec = H.x * tangent + H.y * bitangent + H.z * N;
    return normalize(sampleVec);
}

void main()
{
    vec3 N = normalize(fs_in.FragPos);
    vec3 V = N;

    const uint SAMPLE_COUNT = 1024u;
    vec3 prefilteredColor = vec3(0.0);
    float totalWeight = 0.0;

    for(uint i = 0u; i < SAMPLE_COUTN ; ++i)
    {
        vec2 Xi = Hammersley(i,SAMPLE_COUTN);
        vec3 H = ImportanceSamleGGX(Xi,N,roughness);
        vec3 L = normalize(2.0 * dot(V,H) * H - V);

        float NdotL = max(dot(N,L),0.0);
        if(NdotL > 0.0)
        {
            prefilteredColor += texture(environmentMap, L).rgb * NdotL;
            totalWeight      += NdotL;
        }
    }
    prefilteredColor = prefilteredColor/totalWeight;
    FragColor = vec4(prefilteredColor,1.0);
}