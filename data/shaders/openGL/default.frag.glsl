#version 460 core

out vec4 fragColor;

in vec2 texCoord;

layout(location = 2) uniform sampler2D texture1;
layout(location = 3) uniform sampler2D texture2;

void main()
{
    fragColor = mix(texture(texture1, texCoord), texture(texture2, texCoord), 0.8);
}