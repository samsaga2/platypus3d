#version 330 core

in vec2 TexCoord;
in vec3 VertColor;
in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform vec3 objectColor;

uniform Material material;
uniform vec3 viewPos;
uniform vec3 lightColor;
uniform vec3 lightPos;

void main()
{
    vec3 texColor = mix(texture(texture0, TexCoord),
                        texture(texture1, TexCoord),
                        0.1).xyz;
        
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse =  diff * material.diffuse;
    
    // specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = spec * material.specular;
        
    // final
    vec3 fragLightColor = (material.ambient + diffuse + specular) * lightColor;
    vec3 fragObjectColor = VertColor * objectColor * texColor;
    FragColor = vec4(fragLightColor * fragObjectColor, 1.0);
}
