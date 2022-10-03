#version 420 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in VS_OUT {
	vec3 Normal;
    vec2 TexCoord;
} gs_in[];

out GS_OUT {
    vec3 FragPos;
	vec3 Normal;
    vec2 TexCoord;
} gs_out;

uniform float time;
uniform mat4 matView;
uniform mat4 matProjection;

const float MAGNITUDE = 2.0;

vec4 explode(vec4 position, vec3 normal)
{
    vec3 direction = normal * ((time + 1.0) / 2.0) * MAGNITUDE; 
    return position + vec4(direction, 0.0);
}

void main() 
{    
    gs_out.FragPos = vec3(explode(gl_in[0].gl_Position, gs_in[0].Normal));
    gs_out.TexCoord = gs_in[0].TexCoord;
    gs_out.Normal = gs_in[0].Normal;
    gl_Position = matProjection * matView * vec4(gs_out.FragPos,1.0);
    EmitVertex();

    gs_out.FragPos = vec3(explode(gl_in[1].gl_Position, gs_in[1].Normal));
    gs_out.TexCoord = gs_in[1].TexCoord;
    gs_out.Normal = gs_in[1].Normal;
    gl_Position = matProjection * matView * vec4(gs_out.FragPos,1.0);
    EmitVertex();

    gs_out.FragPos = vec3(explode(gl_in[2].gl_Position, gs_in[2].Normal));
    gs_out.TexCoord = gs_in[2].TexCoord;
    gs_out.Normal = gs_in[2].Normal;
    gl_Position = matProjection * matView * vec4(gs_out.FragPos,1.0);
    EmitVertex();

    EndPrimitive();
}