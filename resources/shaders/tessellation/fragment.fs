#version 420 core

out vec4 FragColor;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;

in VS_OUT {
    vec2 texCoord;
} fs_in;

void main()
{
   if(gl_FragCoord.x < 400)
   //if(gl_FrontFacing)
       FragColor = texture(texture_diffuse1, fs_in.texCoord);
   else
       FragColor = texture(texture_diffuse2, fs_in.texCoord);
}