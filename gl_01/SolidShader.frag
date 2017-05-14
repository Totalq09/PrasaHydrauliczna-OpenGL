#version 330 core

struct Material
{
	sampler2D diffuse;
	float specularStrength;
};

struct Light
{
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

uniform vec3 viewPos;
uniform Material material;
uniform Light light;

out vec4 color;

void main()
{
	float shininess = 32.0;

	//ambient
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));

	//diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDirection = normalize(light.position - FragPos);
	float diff = max(dot(norm, lightDirection), 0.0);
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));

	//specular
	vec3 viewDirection = normalize(viewPos - FragPos);
	vec3 reflectDirection = reflect(-lightDirection, norm);
	float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), shininess);
	vec3 specular = light.specular * spec * material.specularStrength;

	color = vec4(ambient + diffuse + specular, 1.0f);
}