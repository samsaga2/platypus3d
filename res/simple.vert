#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 texcoord;
layout (location = 2) in vec3 color;

out vec2 TexCoord;
out vec3 Color;

uniform mat4 transform;

void main()
{
   gl_Position = transform * vec4(pos, 1.0);
   TexCoord = texcoord;
   Color = color;
}
