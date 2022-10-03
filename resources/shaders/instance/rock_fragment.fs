#version 420 core
out vec4 FragColor;

in VS_OUT {
    vec2 texCoord;
} fs_in;

uniform sampler2D texture_diffuse1;

void main()
{
   FragColor = texture(texture_diffuse1, fs_in.texCoord);
}