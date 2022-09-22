#version 330 core

out vec4 FragColor;

in vec3 color;
in vec2 texCoord;

uniform sampler2D tex0;

void main()
{
	FragColor = texture2D(tex0, texCoord) * vec4(color, 0.5);
}