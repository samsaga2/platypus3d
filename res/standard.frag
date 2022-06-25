#version 330 core

in vec2 TexCoord;
in vec3 VertColor;
in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

uniform Material material;

layout(std140) uniform Matrices {
    vec3 view_pos;   // 0
    mat4 projection; // 16
    mat4 view;       // 80
                     // 144
};

struct Light {
    vec3 pos;        // 0
    vec3 ambient;    // 16
    vec3 diffuse;    // 32
    vec3 specular;   // 48
    float constant;  // 60
    float linear;    // 64
    float quadratic; // 68
                     // 72
};

layout(std140) uniform Lights {
    int num_point_lights; // 0
    Light lights[4];      // 16
};

vec3 calc_point_light(int i, vec3 norm, vec3 view_dir) {
    // ambient
    vec3 ambient = lights[i].ambient * texture(material.diffuse, TexCoord).rgb;

    // diffuse
    vec3 light_dir = normalize(lights[i].pos - FragPos);
    float diff = max(dot(norm, light_dir), 0.0);
    vec3 diffuse =
        lights[i].diffuse * diff * texture(material.diffuse, TexCoord).rgb;

    // specular
    vec3 reflect_dir = reflect(-light_dir, norm);
    float spec = pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess);
    vec3 specular =
        lights[i].specular * spec * texture(material.specular, TexCoord).rgb;

    // attenuation
    float distance = length(lights[i].pos - FragPos);
    float attenuation =
        1.0 / (lights[i].constant + lights[i].linear * distance +
               lights[i].quadratic * (distance * distance));
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    // final
    return ambient + diffuse + specular;
}

void main() {
    vec3 norm = normalize(Normal);
    vec3 view_dir = normalize(view_pos - FragPos);

    vec3 result = vec3(0, 0, 0);
    for (int i = 0; i < num_point_lights; i++)
        result += calc_point_light(0, norm, view_dir);
    FragColor = vec4(result * VertColor, 1.0);
}
