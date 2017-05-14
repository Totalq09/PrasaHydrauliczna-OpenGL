#pragma once

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

#include "ShaderProgram.h"
#include "Transformation.h"

using namespace std;

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

class Mesh
{
public:
	/*  Mesh Data  */
	vector<Vertex> vertices;
	vector<GLuint> indices;
	GLuint texture;
	/*  Functions  */
	Mesh(vector<Vertex> & vertices, vector<GLuint> & indices, GLuint texture, Material mat);
	void Draw(ShaderProgram & shader);

	void translate(glm::vec3 vec);
	void rotate(float angle, glm::vec3 axis = glm::vec3(0.0f, 1.0f, 0.0f));
	void scale(glm::vec3 ratio);
	void scale(float ratio);

private:
	/*  Render data  */
	GLuint VAO, VBO, EBO;
	Transformation model;
	Material material;
	/*  Functions    */
	void setupMesh();
};

