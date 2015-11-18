# ifndef __INCLUDES465__
# include "../includes465/include465.hpp"

# define __INCLUDES465__
# endif


#ifndef MESH_INCLUDED_H
#define MESH_INCLUDED_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "obj_loader.h"


struct Vertex
{
public:
	Vertex(const glm::vec3& pos, const glm::vec2& texCoord, const glm::vec3& normal)
	{
		this->pos = pos;
		this->texCoord = texCoord;
		this->normal = normal;
	}

	glm::vec3* GetPos() { return &pos; }
	glm::vec2* GetTexCoord() { return &texCoord; }
	glm::vec3* GetNormal() { return &normal; }

private:
	glm::vec3 pos;
	glm::vec2 texCoord;
	glm::vec3 normal;
};

enum MeshBufferPositions
{
	POSITION_VB,
	TEXCOORD_VB,
	NORMAL_VB,
	INDEX_VB
};

class Mesh
{
public:
	
		glm::mat4 rotationMatrixM;
		glm::mat4 scaleMatrixM;
		glm::mat4 translationMatrixM;
		glm::vec3 rotationAxisM;
    Mesh(const std::string& fileName, GLuint vao[], GLuint buffer[], int nModels , int meshIndex, bool isText);
	
	Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices
		, GLuint vao[], GLuint buffer[], int nModels, int meshIndex);
	void update();
	void Draw(GLuint vao[], GLuint buffer[], int nModels, int meshIndex);
	glm::mat4 getModelMatrix();

	virtual ~Mesh();
protected:
private:
	static const unsigned int NUM_BUFFERS = 4;
	void operator=(const Mesh& mesh) {}
	Mesh(const Mesh& mesh) {}
	
    void InitMesh(const IndexedModel& model, GLuint vao[], GLuint buffer[], int nModels, int meshIndex);

	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];
	unsigned int m_numIndices;
};

#endif
