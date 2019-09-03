#version 330 core

in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

uniform vec3 viewPos;
uniform vec3 lightPos;
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform mat4 normal;

void main()
{
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
       
    vec3 norm = normalize(vec3(normal * vec4(Normal, 1.0)));
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reverseDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(reverseDir, viewDir), 0.0), 32);
    vec3 specular = spec * specularStrength * lightColor;

    vec3 result = (specular + diffuse + ambient) * objectColor;
    FragColor = vec4(result, 1.0);
}
