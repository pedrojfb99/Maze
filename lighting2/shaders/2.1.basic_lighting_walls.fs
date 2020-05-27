#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture1;


struct ExtWall
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
uniform ExtWall extWall;
uniform Luz light;


void main()
{
    // ambient ExtWall
    vec3 ambientExtWall = light.ambient * extWall.ambient;
    
    // diffuse ExtWall
    vec3 normExtWall = normalize(Normal);
    vec3 lightDirExtWall = normalize(light.pos - FragPos);
    float diffExtWall = max(dot(normExtWall, lightDirExtWall), 0.0);
    vec3 diffuseExtWall = light.diffuse * (diffExtWall * extWall.diffuse);

    // specular ExtWall
    vec3 viewDirExtWall = normalize(viewPos - FragPos);
    vec3 reflectDirExtWall = reflect(-lightDirExtWall, normExtWall);
    float specExtWall = pow(max(dot(viewDirExtWall, reflectDirExtWall), 0.0), extWall.shine);
    vec3 specularExtWall = light.specular * (specExtWall * extWall.specular);
         

    vec4 tex = texture(texture1,TexCoords);
    vec4 result = vec4(ambientExtWall + diffuseExtWall + specularExtWall,1.0);

    FragColor =  mix(tex, result, 0);
}   



