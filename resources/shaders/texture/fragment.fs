#version 420 core

out vec4 FragColor;

in VS_OUT {
    vec2 texCoord;
} fs_in;

uniform float mixValue;
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;

void main()
{
   FragColor = mix(texture(texture_diffuse2,fs_in.texCoord),texture(texture_diffuse1,fs_in.texCoord),mixValue);
}