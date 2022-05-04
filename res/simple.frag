#version 330 core

in vec2 TexCoord;
in vec3 Color;

out vec4 FragColor;

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
    vec4 tex_color = mix(texture(texture0, TexCoord),
                    texture(texture1, TexCoord),
                    0.1);
    vec3 color = Color * objectColor * lightColor;
    FragColor = tex_color * vec4(color, 0);
}
