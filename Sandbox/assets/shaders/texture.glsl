#type vertex
#version 450
			
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TexCoord;

uniform mat4 u_ViewProjection;
uniform mat4 u_Model;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoord;

void main()
{
	gl_Position = u_ViewProjection * u_Model * vec4(a_Position, 1.0);
	FragPos = vec3(u_Model * vec4(a_Position, 1.0));
	Normal = mat3(transpose(inverse(u_Model))) * a_Normal;
	TexCoord = a_TexCoord;
}

#type fragment
#version 450

layout(location = 0) out vec4 color;

uniform vec3 u_LightColor;
uniform float u_Shininess;

uniform vec3 u_LightPos;
uniform vec3 u_CameraPos;

uniform float u_Gamma;

uniform sampler2D u_Texture;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;
			
void main()
{
	float ambientStrength = 0.2;
    vec3 ambient = u_LightColor * ambientStrength;

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(u_LightPos - FragPos);

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = u_LightColor * diff;

	float specularStrength = 0.8;
	vec3 viewDir = normalize(u_CameraPos - FragPos);
	vec3 halfwayDir = normalize(lightDir + viewDir);

	float spec = pow(max(dot(norm, halfwayDir), 0.0), u_Shininess);
	vec3 specular = specularStrength * spec * u_LightColor;

	vec4 result = vec4((ambient + diffuse + specular), 1.0) * texture(u_Texture, TexCoord);
	color = result;
}