

#include "mesh.hpp"

//#include "util.h"
//#include "debugTimer.h"
#include <map>
# ifndef __INCLUDES465__
# include "../includes465/include465.hpp"

# define __INCLUDES465__
# endif
#include <glm/glm.hpp>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdlib.h>

Mesh::Mesh(const std::string& fileName, GLuint vao[], GLuint buffer[], int nModels, int meshIndex, bool isText)
{
    InitMesh(OBJModel(fileName, isText).ToIndexedModel(), vao, buffer, nModels, meshIndex);
	

}

glm::mat4 Mesh::getModelMatrix() {
	return glm::mat4();
	//return(translationMatrixM * rotationMatrixM * scaleMatrixM);
}

 void Mesh::update()
{
	
	translationMatrixM = glm::mat4();
}

void Mesh::InitMesh(const IndexedModel& model, GLuint vao[], GLuint buffer[], int nModels, int meshIndex)
{
    m_numIndices = model.indices.size();

    glGenVertexArrays(1, &vao[nModels+meshIndex]);
	//glBindVertexArray(m_vertexArrayObject);
	glBindVertexArray(vao[nModels + meshIndex]);
	
	//glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
	glGenBuffers(NUM_BUFFERS, &buffer[nModels + meshIndex*NUM_BUFFERS]);
	
	glBindBuffer(GL_ARRAY_BUFFER, buffer[nModels+POSITION_VB + meshIndex*NUM_BUFFERS]);
	//glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(model.positions[0]) * model.positions.size(), &model.positions[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, buffer[nModels + TEXCOORD_VB + meshIndex*NUM_BUFFERS]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(model.texCoords[0]) * model.texCoords.size(), &model.texCoords[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, buffer[nModels + NORMAL_VB + meshIndex*NUM_BUFFERS]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(model.normals[0]) * model.normals.size(), &model.normals[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[nModels + INDEX_VB + meshIndex*NUM_BUFFERS]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(model.indices[0]) * model.indices.size(), &model.indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
	
}

Mesh::Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices
	, GLuint vao[], GLuint buffer[], int nModels, int meshIndex)
{
	
    IndexedModel model;

	for(unsigned int i = 0; i < numVertices; i++)
	{
		model.positions.push_back(*vertices[i].GetPos());
		model.texCoords.push_back(*vertices[i].GetTexCoord());
		model.normals.push_back(*vertices[i].GetNormal());
	}
	
	for(unsigned int i = 0; i < numIndices; i++)
        model.indices.push_back(indices[i]);

    InitMesh(model, vao, buffer, nModels, meshIndex);
}

Mesh::~Mesh()
{
	glDeleteBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
	glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void Mesh::Draw(GLuint vao[], GLuint buffer[], int nModels, int meshIndex)
{
	glBindVertexArray(vao[nModels+meshIndex]);

	//glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, 0);
	glDrawElementsBaseVertex(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, 0, 0);

	glBindVertexArray(0);
}
