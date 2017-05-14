#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Transformation.h"
#include "BoxVertices.h"
#include "Material.h"
#include "ShaderProgram.h"

class Box
{
private:
	GLuint VAO, VBO;
	Material material;

	void initialize();

public:
	Transformation model;

	Box();
	Box(Transformation mod);
	Box(glm::vec3 translation);
	~Box();

	void setMaterial(Material);

	void setShader(ShaderProgram);

	void render(ShaderProgram & shader);
};

