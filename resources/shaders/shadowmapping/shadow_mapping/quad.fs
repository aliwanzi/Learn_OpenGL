#version 420 core
out vec4 FragColor;

in VS_OUT {
    vec2 texCoord;
} fs_in;

uniform sampler2D texture_diffuse1;
uniform float near_plane;
uniform float far_plane;

float LinearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0;
    return (2.0 * near_plane * far_plane)/(far_plane + near_plane - z * (far_plane - near_plane));
}

void main()
{
    float depthValue = texture(texture_diffuse1,fs_in.texCoord).r;
    FragColor = vec4(vec3(depthValue),1.0);
}