#version 420 core
out vec4 FragColor;

in VS_OUT {
	vec3 FragPos;
} fs_in;

uniform sampler2D texture_diffuse1;

const vec2 invAtan = vec2(0.1591,0.3183);
vec2 World3DTo2D(vec3 pos)
{
    vec2 uv = vec2(atan(pos.z,pos.x),asin(pos.y));
    uv *= invAtan;
    uv += vec2(0.5f);
    return uv;
}

void main()
{
    vec2 uv = World3DTo2D(normalize(fs_in.FragPos));
    FragColor = texture(texture_diffuse1, uv);
}