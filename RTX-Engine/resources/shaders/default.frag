#version 330 core

out vec4 FragColor;

in vec3 fragPos;

in mat4 projCam;

in vec2 texCoord;
in vec3 normal;

in vec3 lightPos;
in vec3 lightColor;
in float lightIntensity;

uniform sampler2D tex0;

struct Light {
	float intensity;
	vec3 color;
};

struct SpotLight {
	Light super;

	vec3 position;
};

void main()
{
	vec3 ambient = 0.4 * vec3(205, 176, 235) / 255;

	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(lightPos - fragPos);

	float diffCoeff = max( dot(norm, lightDir), 0.0);
	vec3 diffuse = diffCoeff * lightColor * lightIntensity;

	vec4 lighting = vec4(diffuse + ambient, 1.0);

	FragColor = texture2D(tex0, texCoord) * lighting;
}