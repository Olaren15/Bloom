#version 460 core

out vec4 fragColor;

in vec2 textureUVs;

layout(location = 0) uniform mat4 model;
layout(location = 1) uniform mat4 view;
layout(location = 2) uniform mat4 projection;
layout(location = 3) uniform mat4 combinedProjectionView;

layout(location = 4) uniform sampler2D baseColor;

void main()
{
    fragColor = texture(baseColor, textureUVs);
}