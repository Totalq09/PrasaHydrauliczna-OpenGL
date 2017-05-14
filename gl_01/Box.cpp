#include "Box.h"

Box::Box()
{
	initialize();
}

Box::~Box()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

Box::Box(Transformation mod)
{
	model = mod;
	initialize();
}

Box::Box(glm::vec3 translation)
{
	model.setPosition(translation);
	initialize();
}

////////////////////////////////////////////////////

void Box::initialize()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, BoxVertices::size, BoxVertices::vertices, GL_STATIC_DRAW);

	glBindVertexArray(VAO);
	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);
}

void Box::setMaterial(Material material)
{
	this->material = material;
}

void Box::render(ShaderProgram & shader)
{
	GLint modelLoc = glGetUniformLocation(shader.getProgramID(), "model");
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, material.diffuse);
	glUniform1i(glGetUniformLocation(shader.getProgramID(), "material.diffuse"), 0);
	glUniform1f(glGetUniformLocation(shader.getProgramID(), "material.specularStrength"), material.specularStrength);

	// Draw the container (using container's vertex attributes)
	glBindVertexArray(VAO);
	glm::mat4 model = this->model.getModel();
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}
