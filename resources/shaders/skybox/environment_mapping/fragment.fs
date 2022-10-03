#version 420 core
out vec4 FragColor;

in VS_OUT {
	vec3 FragPos;
	vec3 Normal;
    vec2 TexCoord;
} fs_in;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform samplerCube texture_cube_map1;

uniform vec3 viewPos;

void main()
{
    vec3 norm = normalize(fs_in.Normal);
    vec3 viewDir = normalize(viewPos - vec3(fs_in.FragPos));

    //∑¥…‰
    vec3 R = reflect(-viewDir,norm);

    //’€…‰
    //float ratio = 1.00 / 1.52;
    //vec3 R = refract(-viewDir, norm, ratio);

    vec3 reflection  = vec3(texture(texture_cube_map1,R));
    vec3 specular = vec3(texture(texture_specular1,fs_in.TexCoord)) * reflection ;
    

    float diff = max(normalize(dot(norm, viewDir)), 0.0f);
    vec3 diffuse = diff * vec3(texture(texture_diffuse1,fs_in.TexCoord));

    FragColor = vec4(specular + diffuse,1.0);
}