#version 420 core

out vec4 FragColor;

in VS_OUT {
	vec3 FragPos;
} fs_in;

const float PI = 3.14159265359;
uniform samplerCube texture_cube_map1;

void main()
{
    vec3 N = normalize(fs_in.FragPos);

    vec3 irradiance = vec3(0.0);

    vec3 up = vec3(0.0,1.0,0.0);
    vec3 right = normalize(cross(up,N));
    up = normalize(cross(N,right));

    float sampleDelta = 0.025;
    float nrSamples = 0.0f;
    for(float phi = 0.0; phi <2.0 * PI; phi+= sampleDelta)
    {
        for(float theta = 0.0; theta < 0.5 * PI; theta += sampleDelta)
        {
            vec3 tangentSample = vec3(sin(theta)*cos(phi),sin(theta)*sin(phi),cos(theta));
            vec3 sampleVec = tangentSample.x * right + tangentSample.y * up + tangentSample.z * N;
            irradiance +=texture(texture_cube_map1,sampleVec).rgb * cos(theta) * sin(theta);
            nrSamples ++ ;
        }
    }

    irradiance = PI * irradiance * (1.0/float(nrSamples));
    FragColor = vec4(irradiance,1.0);
}