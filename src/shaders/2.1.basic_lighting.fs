#version 330 core
out vec4 FragColor;

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
uniform Plan plan;
uniform Luz light;

void main()
{
    // ambient Plan
    vec3 ambientPlan = light.ambient * plan.ambient;
    
    // diffuse Plan
    vec3 normPlan = normalize(Normal);
    vec3 lightDirPlan = normalize(light.pos - FragPos);
    float diffPlan = max(dot(normPlan, lightDirPlan), 0.0);
    vec3 diffusePlan = light.diffuse * (diffPlan * plan.diffuse);

    // specular Plan
    vec3 viewDirPlan = normalize(viewPos - FragPos);
    vec3 reflectDirPlan = reflect(-lightDirPlan, normPlan);
    float specPlan = pow(max(dot(viewDirPlan, reflectDirPlan), 0.0), plan.shine);
    vec3 specularPlan = light.specular * (specPlan * plan.specular);
            
    vec3 resultPlan = ambientPlan + diffusePlan + specularPlan;
    FragColor = vec4(resultPlan, 1.0);

}   

