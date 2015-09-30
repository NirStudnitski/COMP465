# version 330 core

in vec4 vPosition;
in vec4 vColor;
in vec3 vNormal;  

/*
this shader creates two suns: ruber and duo, 
of different shades. It also calculates intensity based on distance. 
finally, there is ambient light from around the star field
*/
uniform mat4 ModelViewProjection;  // = projection * view * model
uniform mat4 rotation;
uniform mat4 translation;
uniform mat4 transD;

//normalized pointers to ruber and duo
uniform vec3 R;
uniform vec3 posD;

uniform float intensityD;
uniform float intensityR;

uniform vec4 colR;
uniform vec4 colD;

out vec4 color;
out vec3 vN;
out vec3 nE;

void main() {

//rotate the normal
vN = vec3(
rotation[0][0]*vNormal.x + rotation[1][0]*vNormal.y+ rotation[2][0]*vNormal.z,
rotation[0][1]*vNormal.x + rotation[1][1]*vNormal.y+ rotation[2][1]*vNormal.z,
rotation[0][2]*vNormal.x + rotation[1][2]*vNormal.y+ rotation[2][2]*vNormal.z

);
vec3 N = normalize (vN);

float intensity = dot(N,R);
float intensity2 = dot(N,posD);
intensity = max(intensity, 0);

intensity2*=-1;
intensity2 = max(intensity2, 0);
intensity = intensity* intensityR;
intensity2 = intensity2* intensityD;
vec4 colRmod = vec4(colR.x * intensity, colR.y * intensity, colR.z * intensity, 1.0f);
vec4 colDmod = vec4(colD.x * intensity2, colD.y * intensity2, colD.z * intensity2, 1.0f);
vec4 ambient = vec4(0.1f,0.1f,0.1f,0.1f);
 color = vec4(colRmod + colDmod + ambient);

  gl_Position = ModelViewProjection * vPosition;
  }
