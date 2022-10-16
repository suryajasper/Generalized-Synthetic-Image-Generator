#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNorm;

out vec3 fragPos;

out mat4 projCam;

out vec2 texCoord;
out vec3 normal;

out vec3 lightPos;
out vec3 lightColor;
out float lightIntensity;

uniform float scale;
uniform mat4 MPV;
uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

uniform vec3 lightPosIn;
uniform vec3 lightColorIn;
uniform float lightIntensityIn;

void main()
{
	gl_Position = MPV * vec4(aPos, 1.0);

	fragPos = vec3(model * vec4(aPos, 1.0));

	projCam = proj;

	texCoord = aTexCoord;
	normal = aNorm;
	
	lightPos = lightPosIn;
	lightColor = lightColorIn;
	lightIntensity = lightIntensityIn;
}
