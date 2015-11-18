#ifndef SHADER_INCLUDED_H
#define SHADER_INCLUDED_H

#include <string>
#include <GL/glew.h>
#include "transform.h"



class Shader
{
public:
	Shader(const std::string& fileName);
	

	void Bind();
	void Update(glm::mat4 mM, glm::mat4 viewM, glm::mat4 projM, const Transform& transform, const Camera& camera);
	void Update(glm::mat4 mM, glm::mat4 viewM, glm::mat4 projM, const Transform& transform, const Camera& camera, 
		glm::vec3 Rin, glm::vec3 posDin, glm::vec4 ruberLightColorIn, glm::vec4 duoLightColorIn, float intensityRin, float intensityDin, glm::mat4 stat);

	virtual ~Shader();
protected:
private:
	static const unsigned int NUM_SHADERS = 2;
	static const unsigned int NUM_UNIFORMS = 3;
	void operator=(const Shader& shader) {}
	Shader(const Shader& shader) {}

	std::string LoadShader(const std::string& fileName);
	void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	GLuint CreateShader(const std::string& text, unsigned int type);
	GLuint PRu, PDu, CRu, CDu, intensDu, intensRu, dirRu, dirDu, statu;
	glm::vec3 Ru, posDu;
	glm::vec4 ruberLightColoru, duoLightColoru;
	float intensityRu, intensityDu;
	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];
	GLuint m_uniforms[NUM_UNIFORMS];
};

#endif
