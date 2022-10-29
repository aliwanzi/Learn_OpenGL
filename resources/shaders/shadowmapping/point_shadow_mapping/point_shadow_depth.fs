#version 420 core

in GS_OUT {
	vec4 FragPos;
} fs_in;

uniform vec3 lightPos;
uniform float far_plane;

out vec4 FragColor;

void main()
{
    float lightDistance = (length(fs_in.FragPos.xyz))/25.0f;

    gl_FragDepth = lightDistance;
    FragColor = vec4(vec3(lightDistance),1.0);
}