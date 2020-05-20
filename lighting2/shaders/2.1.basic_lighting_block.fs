#version 330 core
out vec4 FragColor;

struct Block
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
uniform Block block;
uniform Luz light;

void main()
{
    // ambient Block
    vec3 ambientBlock = light.ambient * block.ambient;
    
    // diffuse Block
    vec3 normBlock = normalize(Normal);
    vec3 lightDirBlock = normalize(light.pos - FragPos);
    float diffBlock = max(dot(normBlock, lightDirBlock), 0.0);
    vec3 diffuseBlock = light.diffuse * (diffBlock * block.diffuse);

    // specular Block
    vec3 viewDirBlock = normalize(viewPos - FragPos);
    vec3 reflectDirBlock = reflect(-lightDirBlock, normBlock);
    float specBlock = pow(max(dot(viewDirBlock, reflectDirBlock), 0.0), block.shine);
    vec3 specularBlock = light.specular * (specBlock * block.specular);
            
    vec3 resultBlock = ambientBlock + diffuseBlock + specularBlock;
    FragColor = vec4(resultBlock, 1.0);

}   
