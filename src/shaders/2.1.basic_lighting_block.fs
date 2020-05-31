#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture1;


struct Plan
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
uniform Plan block;
uniform Luz light;


void main()
{
    // ambient Plan
    vec3 ambientPlan = light.ambient * block.ambient;
    
    // diffuse Plan
    vec3 normPlan = normalize(Normal);
    vec3 lightDirPlan = normalize(light.pos - FragPos);
    float diffPlan = max(dot(normPlan, lightDirPlan), 0.0);
    vec3 diffusePlan = light.diffuse * (diffPlan * block.diffuse);

    // specular Plan
    vec3 viewDirPlan = normalize(viewPos - FragPos);
    vec3 reflectDirPlan = reflect(-lightDirPlan, normPlan);
    float specPlan = pow(max(dot(viewDirPlan, reflectDirPlan), 0.0), block.shine);
    vec3 specularPlan = light.specular * (specPlan * block.specular);
         

    vec4 tex = texture(texture1,TexCoords);
    vec4 result = vec4(ambientPlan + diffusePlan + specularPlan,1.0);

    FragColor =  mix(tex, result, 0.65);
}   



