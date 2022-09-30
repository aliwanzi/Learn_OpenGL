#version 420 core
out vec4 FragColor;

in VS_OUT {
    vec2 texCoord;
} fs_in;

uniform sampler2D texture_diffuse1;
float near = 0.1;
float far = 100;
float LinearizeDepth(float depth)
{
    float zndc = depth * 2.0 -1.0;
    return (2.0 * near * far) / (far + near - zndc * (far-near));
}

void main()
{
    FragColor = texture(texture_diffuse1, fs_in.texCoord);
    //FragColor = vec4(vec3(LinearizeDepth(gl_FragCoord.z)/far), 1.0);
}