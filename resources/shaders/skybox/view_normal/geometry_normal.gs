#version 420 core
layout (triangles) in;
layout (line_strip, max_vertices = 6) out;

in VS_OUT {
    vec3 Normal;
} gs_in[];

const float MAGNITUDE = 0.2;

uniform mat4 matProjection;

void GenerateLine(int index)
{
    gl_Position = matProjection * gl_in[index].gl_Position;
    EmitVertex();
    gl_Position = matProjection * (gl_in[index].gl_Position + vec4(gs_in[index].Normal, 0.0) * MAGNITUDE);
    EmitVertex();
    EndPrimitive();
}

void main()
{
    GenerateLine(0); // first vertex normal
    GenerateLine(1); // second vertex normal
    GenerateLine(2); // third vertex normal
}