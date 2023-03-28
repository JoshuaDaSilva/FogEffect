#version 400 core

layout(location = 0) in vec3 VertPos;
layout(location = 1) in vec2 UVs;
layout(location = 2) in vec3 normal;

uniform vec3 CamPos;
uniform mat4 proj_matrix;
uniform mat4 mv_matrix;

out vec2 UV;
out vec3 normalVec;
out vec3 lightVec;
out vec3 viewVec;

//Fog
out float visibility;

//Fog
uniform float density = 0.04;
uniform float gradient = 0.89;


vec3 light_pos = vec3(10.0, 10.0, 10.0);

void main(void)                                                   
{                                             
	UV = UVs;	
	
    // Calculate normal in view-space
    normalVec = mat3(mv_matrix) * normal;
	
	// new position using the projection and modelview matrices in addition to the position of each vertices
	// we  pass in 300 cubes, each cube is assigned a new gl_InstanceID, based off that we need to determine it's XY & Z
	float cubeX = VertPos.x + (mod((gl_InstanceID/10),10)/2.0f); // use mod 10 then /10 to find offset as we have a 10x10 area
	float cubeY = VertPos.y+ ((gl_InstanceID/100)/2.0f); // use /100 as we have 100 cubes per layer
	float cubeZ = VertPos.z -(mod(gl_InstanceID , 10)/2); // use mod 10 to determine the depth as we only have 10 depth max
	
	vec4 P = proj_matrix * mv_matrix * vec4( cubeX, cubeY, cubeZ, 1.0f);

    //caluculate the view vector
	viewVec = -CamPos;
	
	// Calculate light vector
    lightVec = light_pos;

	//Fog
	float distance = length(P.xyz);
	visibility = exp(-pow((distance*density), gradient));
	
	gl_Position = P;
}         
