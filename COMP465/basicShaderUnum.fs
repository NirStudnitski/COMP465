
#version 120

varying vec2 texCoord0;
varying vec3 normal0;

uniform sampler2D sampler;
uniform vec3 lightDirection;

varying in vec4 color; 

void main()
{
	//gl_FragColor = texture2D(sampler, texCoord0) ;
	gl_FragColor = texture2D(sampler, texCoord0) *  color;
	//gl_FragColor =  color;
		//clamp(dot(-lightDirection, normal0), 0.0, 1.0);

}
