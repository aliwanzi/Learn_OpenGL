#version 420 core

//out float FragColor;
out vec4 FragColor;

in VS_OUT {
    vec2 TexCoords;
} fs_in;

uniform sampler2D texture_diffuse1;

void main()
{
	vec2 texelSize = 1.0 / vec2(textureSize(texture_diffuse1,0));
	float result  = 0.0;
	for(int x = -2; x<2 ; x++)
	{
		for(int y = -2; y<2 ; y++)
		{
			vec2 offset = vec2(float(x),float(y)) * texelSize;
			result += texture(texture_diffuse1,fs_in.TexCoords + offset).r;
		}
	}
	FragColor = vec4(vec3(result/16),1.0);
}