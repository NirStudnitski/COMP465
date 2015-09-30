# version 330 core

in vec4 vPosition;
in vec4 vColor;
in vec3 vNormal;  

uniform vec4 colR;

uniform mat4 ModelViewProjection;  // = projection * view * model
out vec4 color;

void main() {

  color = vec4(0.3f*vNormal.x+colR.x, 0.3f*vNormal.y+colR.y, 0.3f*vNormal.z+colR.z, 1.0f);
  gl_Position = ModelViewProjection * vPosition;
  }
