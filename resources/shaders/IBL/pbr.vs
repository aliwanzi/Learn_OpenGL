#version 420 core

//out float FragColor;

out vec4 FragColor;

in VS_OUT {
    vec2 TexCoords;
} fs_in;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_diffuse3;

int kernelSize = 64;
float radius = 0.5;
float bias = 0.025;

const vec2 noiseScale = vec2(800.0/4.0,600.0/4.0);

uniform mat4 matProjection;
uniform vec3 samples[64];

void main()
{
      vec3 fragPos = texture(texture_diffuse1, fs_in.TexCoords).rgb;
      vec3 normal =  normalize(texture(texture_diffuse2, fs_in.TexCoords).rgb);
      vec3 noise = normalize(texture(texture_diffuse3, fs_in.TexCoords * noiseScale).rgb);

      vec3 tangent = normalize(noise - normal * dot(noise , normal));
      vec3 bitangent = cross(normal , tangent);
      mat3 TBN = mat3(tangent,bitangent,normal);

      float occlusion = 0.0;
      for(int i = 0; i< kernelSize ; ++i)
      {
         vec3 samplePos = TBN * samples[i];
         samplePos = fragPos + samplePos * radius ;

         vec4 offset = vec4(samplePos,1.0);
         offset = matProjection * offset;
         offset.xyz /= offset.w;
         offset.xyz = offset.xyz * 0.5 + 0.5;

         float sampleDepth = texture(texture_diffuse1, offset.xy).z;

         float rangeCheck = smoothstep(0.0,1.0,radius /abs(fragPos.z - sampleDepth));
         occlusion += (sampleDepth >= samplePos.z + bias ? 1.0:0.0)*rangeCheck;
      }
      occlusion = 1.0 - (occlusion/kernelSize);

      FragColor = vec4(vec3(occlusion),1.0);
}