#version 330 core

out vec4 FragColor;

in vec3 texCoord;

uniform samplerCube skybox;

void main()
{    
    FragColor = vec4(200, 50, 200, 1.0); 
    FragColor = texture(skybox, texCoord);
}
