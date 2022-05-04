#version 330 core

in vec2 TexCoord;
in vec3 Color;

out vec4 FragColor;

uniform sampler2D texture0;
uniform sampler2D texture1;

void main()
{
   FragColor = mix(texture(texture0, TexCoord),
                   texture(texture1, TexCoord),
                   0.1) * vec4(Color, 0);
}
