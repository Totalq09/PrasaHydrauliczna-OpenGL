#pragma once

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class BoxVertices
{
public:
	static const GLfloat vertices[288];
	static const GLuint size;

	BoxVertices();
	~BoxVertices();
};


