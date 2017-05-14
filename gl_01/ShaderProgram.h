#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

class ShaderProgram
{
	GLuint programID;

public:

	ShaderProgram(const GLchar* vertexPath, const GLchar* fragmentPath);

	void use() const
	{
		glUseProgram(getProgramID());
	}

	GLuint getProgramID() const
	{
		return programID;
	}

	~ShaderProgram();
};

