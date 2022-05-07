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

struct PointLight {
    vec3 position;

    // colors
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    // attenuation
    float constant;
    float linear;
    float quadratic;
};

#define NUM_LIGHTS 4

uniform vec3 viewPos;
uniform Material material;
uniform PointLight point_lights[NUM_LIGHTS];
uniform int num_point_lights;

vec3 calc_point_light(PointLight light, vec3 norm, vec3 view_dir) {
    // ambient
    vec3 ambient = light.ambient * texture(material.diffuse, TexCoord).rgb;

    // diffuse
    vec3 light_dir = normalize(light.position - FragPos);
    float diff = max(dot(norm, light_dir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoord).rgb;

    // specular
    vec3 reflect_dir = reflect(-light_dir, norm);  
    float spec = pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * texture(material.specular, TexCoord).rgb;

    // attenuation
    float distance = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance +
                               light.quadratic * (distance * distance));
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
        
    // final
    return ambient + diffuse + specular;
}

void main() {
    vec3 norm = normalize(Normal);
    vec3 view_dir = normalize(viewPos - FragPos);

    vec3 result = vec3(0,0,0);
    for(int i = 0; i < num_point_lights; i++)
        result += calc_point_light(point_lights[i], norm, view_dir);
    FragColor = vec4(result * VertColor, 1.0);
}
