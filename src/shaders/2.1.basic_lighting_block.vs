#version 330 core
layout (location = 6) in vec3 aPos;
layout (location = 7) in vec3 aNormal;
layout (location = 10) in vec2 aTexCoords;



out vec2 TexCoords;

out vec3 FragPos;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{

	TexCoords = aTexCoords;
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;  
    
    gl_Position = projection * view * vec4(FragPos, 1.0);
}
