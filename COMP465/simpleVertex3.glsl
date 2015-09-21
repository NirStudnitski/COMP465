# version 330 core

in vec4 vPosition;
in vec4 vColor;
in vec3 vNormal;  // not used

uniform mat4 ModelViewProjection;  // = projection * view * model
out vec4 color;

void main() {

  color = vec4(0.5f, 0.5f*vNormal.y-0.2f, 0, 1.0f);
  gl_Position = ModelViewProjection * vPosition;
  }
