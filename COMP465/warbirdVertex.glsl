# version 330 core

in vec4 vPosition;
in vec4 vColor;
in vec3 vNormal;  


uniform mat4 ModelViewProjection;  // = projection * view * model
uniform mat4 rotation;
uniform mat4 translation;
uniform vec3 posR;
uniform vec3 posD;
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
vec3 P = normalize (vec3 (-translation[3][0],-translation[3][1],  -translation[3][2]));

//D points to duo's position, normalized
vec3 D = normalize (vec3 (-translation[3][0]+posD.x,-translation[3][1]+posD.y,  -translation[3][2]+posD.z));
// dot the rotated normal N with location vector (assuming light source is at 0,0,0)
float intensity =dot (N,P);
float intensity2 = dot(N,D);
intensity = max(intensity, 0);
intensity2 = max(intensity2, 0);
 color = vec4(intensity2+0.5f,0.5f , 0.5f, 1.0f);
 
  gl_Position = ModelViewProjection * vPosition;
  }
