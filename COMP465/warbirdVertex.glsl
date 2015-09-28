# version 330 core

in vec4 vPosition;
in vec4 vColor;
in vec3 vNormal;  


uniform mat4 ModelViewProjection;  // = projection * view * model
uniform mat4 rotation;
out vec4 color;
out vec3 vN;
out vec3 nE;

void main() {
vN = vec3(
rotation[0][0]*vNormal.x + rotation[1][0]*vNormal.y+ rotation[2][0]*vNormal.z,
rotation[0][1]*vNormal.x + rotation[1][1]*vNormal.y+ rotation[2][1]*vNormal.z,
rotation[0][2]*vNormal.x + rotation[1][2]*vNormal.y+ rotation[2][2]*vNormal.z

);

 color = vec4(
 ((vNormal.x + vNormal.y+vNormal.z)/3+1)*vN.x,((vNormal.x + vNormal.y+vNormal.z)/3+1)*vN.x, ((vNormal.x + vNormal.y+vNormal.z)/3+1)*vN.x, 1.0f);
  gl_Position = ModelViewProjection * vPosition;
  }
