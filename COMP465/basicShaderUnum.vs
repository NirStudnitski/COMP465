#version 120

attribute vec3 position;
attribute vec2 texCoord;
attribute vec3 normal;



//normalized pointers to ruber and duo
uniform vec3 Ru;
uniform vec3 posDu;

uniform float intensityDu;
uniform float intensityRu;

uniform vec4 colRu;
uniform vec4 colDu;


varying vec2 texCoord0;
varying vec3 normal0;

uniform mat4 MVP;
uniform mat4 Normal;
uniform mat4 statMu;

varying out vec4 color;

void main()
{
	gl_Position = MVP * vec4(position, 1.0);
	texCoord0 = texCoord;
	normal0 = (Normal * vec4(normal, 0.0)).xyz;
	
	vec3 vN2 = vec3(
				statMu[0][0]*normal0.x + statMu[1][0]*normal0.y+ statMu[2][0]*normal0.z,
				statMu[0][1]*normal0.x + statMu[1][1]*normal0.y+ statMu[2][1]*normal0.z,
				statMu[0][2]*normal0.x + statMu[1][2]*normal0.y+ statMu[2][2]*normal0.z

				);
	vec3 N2 = normalize (vN2);
	//vec3 N2 = normalize (normal0);
				
	
	float intensityA  = dot(N2,Ru);
	float intensity2A = dot(N2,posDu);
	intensityA = max(intensityA, 0);

	intensity2A*=-1;
	intensity2A = max(intensity2A, 0);
	intensityA = intensityA* intensityRu;
	intensity2A = intensity2A* intensityDu; 
	vec4 colRmod2 = vec4(colRu.x * intensityA, colRu.y * intensityA, colRu.z * intensityA, 1.0f);
	vec4 colDmod2 = vec4(colDu.x * intensity2A, colDu.y * intensity2A, colDu.z * intensity2A, 1.0f);
	vec4 ambient2 = vec4(0.2f,0.2f,0.2f,1.0f);
    color = vec4(colRmod2 + colDmod2 + ambient2);
	
}
