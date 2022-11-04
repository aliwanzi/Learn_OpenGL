#version 420 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 18) out;

uniform mat4 matLightSpace[6];

out GS_OUT {
	vec4 FragPos;
} gs_out;

void main()
{
	for(int face = 0; face < 6; ++face)
	{
		gl_Layer = face;
		for(int i = 0; i < 3; ++i)
		{
			gs_out.FragPos = gl_in[i].gl_Position;
			gl_Position = matLightSpace[face] * gs_out.FragPos;
			EmitVertex();
		}
		EndPrimitive();
	}
}