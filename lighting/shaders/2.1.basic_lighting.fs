#version 330 core

out vec4 FragColor;
out vec4 FragColor2;

in vec3 Normal;
in vec3 Normal2;

in vec3 FragPos;
in vec3 FragPos2;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 objectColor;

uniform vec3 lightColor2;
uniform vec3 objectColor2;

void main()
{
    //ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
    vec3 ambient2 = ambientStrength * lightColor2;

    //diffuse
    vec3 norm = normalize(Normal);
    vec3 norm2 = normalize(Normal2);
    vec3 lightDir = normalize(lightPos - FragPos);
    vec3 lightDir2 = normalize(lightPos - FragPos2);
    float diff = max(dot(norm,lightDir),0.0);
    float diff2 = max(dot(norm2,lightDir2),0.0);
    vec3 diffuse = diff * lightColor;
    vec3 diffuse2 = diff2 * lightColor2;

    vec3 result = (ambient + diffuse) + objectColor;
    vec3 result2 = (ambient2 + diffuse2) + objectColor2;

    FragColor = vec4(result,1.0);
    FragColor2 = vec4(result2,1.0);
} 