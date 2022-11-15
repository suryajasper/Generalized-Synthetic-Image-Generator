#version 330 core

out vec4 FragColor;

in vec3 fragPos;
in vec3 normal;
in vec2 texCoord;

in mat4 projCam;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float     shininess;
};

struct Light {
	float intensity;
	vec3 position;
	vec3 color;
};

uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main()
{
	vec3 ambient = 0.6 * vec3(205, 176, 235) / 255;
	vec3 lightHDR = light.intensity * light.color;

	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(light.position - fragPos);

	float specularStrength = 2.0;
	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);

	float specCoeff = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	float diffCoeff = max( dot(norm, lightDir), 0.0 );

	vec3 specular = specularStrength * specCoeff * lightHDR * vec3(texture2D(material.specular, texCoord));
	vec3 diffuse = diffCoeff * lightHDR;

	vec4 texColor = texture2D(material.diffuse, texCoord);
	// texColor = vec4(0.4, 0.4, 0.0, 1.0);
	vec4 lighting = vec4(diffuse + ambient + specular, 1.0);

	FragColor = texColor * lighting;
}