#version 420 core
out vec4 FragColor;

in VS_OUT {
    vec3 WorldPos;
} fs_in;

uniform samplerCube texture_cube_map1;

void main()
{
    //FragColor = vec4(1.0,0.0,0.0,0.0);
    vec3 envColor = texture(texture_cube_map1, fs_in.WorldPos,0.0).rgb;

    envColor = envColor / (envColor + vec3(1.0));
    envColor = pow(envColor, vec3(1.0/2.2)); 

    FragColor = vec4(envColor,1.0);

}