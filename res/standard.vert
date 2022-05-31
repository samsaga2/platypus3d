#version 330 core

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec2 inTexCoord;
layout (location = 2) in vec3 inVertColor;
layout (location = 3) in vec3 inVertNormal;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoord;
out vec3 VertColor;

uniform mat4 model;

layout (std140) uniform Matrices {
    mat4 projection;
    mat4 view;
};

void main()
{
    // for light
    FragPos = vec3(model * vec4(inPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * inVertNormal;

    // for color
    TexCoord = inTexCoord;
    VertColor = inVertColor;
    gl_Position = projection * view * vec4(FragPos, 1.0);
}
