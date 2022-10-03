#version 420 core
out vec4 FragColor;

in VS_OUT {
    vec2 texCoord;
} fs_in;

const float offset = 1.0/300.0;
vec2 offsets[9] = vec2[](
    vec2(-offset,  offset), // ����
    vec2( 0.0f,    offset), // ����
    vec2( offset,  offset), // ����
    vec2(-offset,  0.0f),   // ��
    vec2( 0.0f,    0.0f),   // ��
    vec2( offset,  0.0f),   // ��
    vec2(-offset, -offset), // ����
    vec2( 0.0f,   -offset), // ����
    vec2( offset, -offset)  // ����
);


uniform sampler2D texture_diffuse1;
vec4 Sharpen();
vec4 Blur();
vec4 Edge();

void main()
{
    //FragColor = texture(texture_diffuse1, fs_in.texCoord);

    //����
    //FragColor = vec4(vec3(1.0-texture(texture_diffuse1, fs_in.texCoord)),1.0);

    //�Ҷ�
    //FragColor = texture(texture_diffuse1, fs_in.texCoord);
    //float average = (FragColor.r+FragColor.g+FragColor.b)/3.0;
    //FragColor = vec4(vec3(average),1.0);

    //��
    //FragColor=Sharpen();

    //ģ��
    FragColor=Blur();

    //��Ե���
    //FragColor=Edge();
}

vec4 Sharpen()
{
    float kernel[9] = float[](
        -1, -1, -1,
        -1,  9, -1,
        -1, -1, -1
    );

    vec3 sampleTex[9];
    for(int i = 0; i < 9; i++)
    {
        sampleTex[i] = vec3(texture(texture_diffuse1, fs_in.texCoord.st + offsets[i]));
    }
    vec3 col = vec3(0.0);
    for(int i = 0; i < 9; i++)
        col += sampleTex[i] * kernel[i];

    return vec4(col,1.0);
}

vec4 Blur()
{
    float kernel[9] = float[](
        1.0 / 16, 2.0 / 16, 1.0 / 16,
        2.0 / 16, 4.0 / 16, 2.0 / 16,
        1.0 / 16, 2.0 / 16, 1.0 / 16  
    );

    vec3 sampleTex[9];
    for(int i = 0; i < 9; i++)
    {
        sampleTex[i] = vec3(texture(texture_diffuse1, fs_in.texCoord.st + offsets[i]));
    }
    vec3 col = vec3(0.0);
    for(int i = 0; i < 9; i++)
        col += sampleTex[i] * kernel[i];

    return vec4(col,1.0);
}

vec4 Edge()
{
    float kernel[9] = float[](
        1, 1, 1,
        1, -8, 1,
        1, 1, 1
    );

    vec3 sampleTex[9];
    for(int i = 0; i < 9; i++)
    {
        sampleTex[i] = vec3(texture(texture_diffuse1, fs_in.texCoord.st + offsets[i]));
    }
    vec3 col = vec3(0.0);
    for(int i = 0; i < 9; i++)
        col += sampleTex[i] * kernel[i];

    return vec4(col,1.0);
}