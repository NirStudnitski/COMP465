
#version 120

varying vec2 texCoord0;
varying vec3 normal0;

uniform sampler2D sampler;
uniform vec3 lightDirection;

void main()
{
	gl_FragColor = vec4(0.0f , 1.0f , 0.0f , 1.0f) ;
	
}
