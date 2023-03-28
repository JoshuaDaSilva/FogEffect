#version 400 core

out vec4 color;                                                   

in vec2 UV;
in vec3 normalVec;
in vec3 lightVec;
in vec3 viewVec;

//Fog
in float visibility;
uniform vec3 SkyColor = vec3(1.48, 0.13, 0.13);

uniform sampler2D texture0;
uniform vec3 ambientLight = vec3(0.0,0.0,0.0);
uniform vec3 diffuse_albedo = vec3(1.0, 1.0, 1.0);
uniform float specular_power = 128.0;

void main(void)                                                   
{                               
    // Normalize the incoming N, L and V vectors
    vec3 N = normalize(normalVec);
    vec3 L = normalize(lightVec);
	vec3 V = normalize(viewVec);
	vec3 R = reflect(N,L);

	//the dot product of the normals and the light vector identifies whether the angle to the light is direct or not.
	float ReflectivePercentage = max(dot(R,V), 0.0);
	float Reflection = dot(N, L);

	// Compute the diffuse based off the materials properties and the amount the face is visible to the light
    vec3 specular = vec3(pow(ReflectivePercentage, specular_power));
	vec3 diffuse = max(Reflection, 0.0) * diffuse_albedo;
	
	color = texture( texture0, UV ) * vec4(diffuse + (specular * diffuse) + ambientLight, 1.0f);

	//Fog
	color = mix( vec4(SkyColor, 1.0), color, visibility);
}                                 