#version 330 core

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float c0;
    float c1;
    float c2;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

out vec4 FragColor;

uniform vec3 viewPos;
uniform Light light;
uniform mat4 normal;
uniform Material material;

void main()
{
    float distance = length(FragPos - light.position);
    float attenuation = 1.0 / (light.c0 + light.c1 * distance + light.c2 * distance * distance);
    vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;
    
    vec3 norm = normalize(vec3(normal * vec4(Normal, 1.0)));
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * light.diffuse * texture(material.diffuse, TexCoords).rgb;

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reverseDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(reverseDir, viewDir), 0.0), material.shininess);
    vec3 specular = spec * light.specular * texture(material.specular, TexCoords).rgb;

    vec3 result = specular + diffuse + ambient;
    result = result * attenuation;
    FragColor = vec4(result, 1.0);
}
