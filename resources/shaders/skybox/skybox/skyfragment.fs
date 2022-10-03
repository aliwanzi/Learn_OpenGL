#version 420 core
out vec4 FragColor;

in VS_OUT {
    vec3 texCoord;
} fs_in;

uniform samplerCube texture_cube_map1;

void main()
{
    //FragColor = vec4(1.0,0.0,0.0,0.0);
    FragColor = texture(texture_cube_map1, fs_in.texCoord);
}