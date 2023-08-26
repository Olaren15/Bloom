#version 460 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 inTextureUVs;

out vec2 textureUVs;

layout(location = 0) uniform mat4 model;
layout(location = 1) uniform mat4 view;
layout(location = 2) uniform mat4 projection;
layout(location = 3) uniform mat4 combinedProjectionView;

void main()
{
    gl_Position = combinedProjectionView * model * vec4(inPosition, 1.0f);
    textureUVs = inTextureUVs;
}