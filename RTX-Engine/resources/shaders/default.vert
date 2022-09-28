#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNorm;

out vec2 texCoord;
out vec3 normal;

uniform float scale;

uniform mat4 MPV;

void main()
{
	gl_Position = MPV * vec4(aPos, 1.0);
	texCoord = aTexCoord;
	normal = aNorm;
}
