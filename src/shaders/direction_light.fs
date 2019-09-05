#version 330 core

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
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
    vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;
    
    vec3 norm = normalize(vec3(normal * vec4(Normal, 1.0)));
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * light.diffuse * texture(material.diffuse, TexCoords).rgb;

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reverseDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(reverseDir, viewDir), 0.0), material.shininess);
    vec3 specular = spec * light.specular * texture(material.specular, TexCoords).rgb;

    vec3 result = specular + diffuse + ambient;
    FragColor = vec4(result, 1.0);
}
