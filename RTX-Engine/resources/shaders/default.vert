#version 330 core

layout (location = 0) in vec3 position;

/*
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTex;

out vec3 color;
out vec2 texCoord;
*/

// Controls the scale of the vertices
uniform float scale;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
	gl_Position = scale * vec4(position, 1.0) * proj * view * model;
	
	// setting color and texture coordinate to be sent to fragment shader
	// color = aColor;
  // texCoord = aTex;
}