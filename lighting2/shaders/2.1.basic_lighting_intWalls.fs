#version 330 core
out vec4 FragColor;

struct IntWall
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shine;
};

struct Luz
{
    vec3 pos;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 Normal;  
in vec3 FragPos;

  
uniform vec3 viewPos;
uniform IntWall intWall;
uniform Luz light;

void main()
{
    // ambient IntWall
    vec3 ambientIntWall = light.ambient * intWall.ambient;
    
    // diffuse IntWall
    vec3 normIntWall = normalize(Normal);
    vec3 lightDirIntWall = normalize(light.pos - FragPos);
    float diffIntWall = max(dot(normIntWall, lightDirIntWall), 0.0);
    vec3 diffuseIntWall = light.diffuse * (diffIntWall * intWall.diffuse);

    // specular IntWall
    vec3 viewDirIntWall = normalize(viewPos - FragPos);
    vec3 reflectDirIntWall = reflect(-lightDirIntWall, normIntWall);
    float specIntWall = pow(max(dot(viewDirIntWall, reflectDirIntWall), 0.0), intWall.shine);
    vec3 specularIntWall = light.specular * (specIntWall * intWall.specular);
            
    vec3 resultIntWall = ambientIntWall + diffuseIntWall + specularIntWall;
    FragColor = vec4(resultIntWall, 1.0);

}   
