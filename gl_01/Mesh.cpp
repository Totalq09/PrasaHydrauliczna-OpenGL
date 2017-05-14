#include "Mesh.h"

Mesh::Mesh(vector<Vertex> & vertices, vector<GLuint> & indices, GLuint texture, Material mat)
{
	this->vertices = vertices;
	this->indices = indices;
	this->texture = texture;

	material = mat;

	setupMesh();
}

void Mesh::setupMesh()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex),
		&vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint),
		&indices[0], GL_STATIC_DRAW);

	// Vertex Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(GLvoid*)0);
	// Vertex Normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(GLvoid*)offsetof(Vertex, Normal));
	// Vertex Texture Coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(GLvoid*)offsetof(Vertex, TexCoords));

	glBindVertexArray(0);
}

void Mesh::Draw(ShaderProgram & shader)
{
	glActiveTexture(GL_TEXTURE0); // Activate proper texture unit before binding

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, material.diffuse);

	GLint modelLoc = glGetUniformLocation(shader.getProgramID(), "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model.getModel()));
	glUniform1i(glGetUniformLocation(shader.getProgramID(), "material.diffuse"), 0);
	glUniform1f(glGetUniformLocation(shader.getProgramID(), "material.specularStrength"), material.specularStrength);

	// Draw mesh
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

///////////////////////////////////////////////////////////////////

void Mesh::translate(glm::vec3 vec)
{
	model.translate(vec);
}

void Mesh::rotate(float angle, glm::vec3 axis)
{
	model.rotate(angle, axis);
}

void Mesh::scale(glm::vec3 ratio)
{
	model.scale(ratio);
}

void Mesh::scale(float ratio)
{
	model.scale(ratio);
}

Mesh::~Mesh()
{
}
