#include "ShaderProgram.h"


string readShaderCode(const GLchar* shaderPath)
{
	ifstream shaderFile;
	shaderFile.exceptions(ifstream::badbit);

	shaderFile.open(shaderPath);
	stringstream shaderStream;

	shaderStream << shaderFile.rdbuf();
	shaderFile.close();

	return shaderStream.str();
}

GLuint compileShader(const GLchar* shaderCode, GLenum shaderType)
{
	GLuint shaderID = glCreateShader(shaderType);
	glShaderSource(shaderID, 1, &shaderCode, NULL);
	glCompileShader(shaderID);

	GLint success = 0;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		GLchar infoLog[512];
		glGetShaderInfoLog(shaderID, sizeof(infoLog), NULL, infoLog);
		string msg = string("Shader compilation: ") + infoLog;
		throw exception(msg.c_str());
	}

	return shaderID;
}

ShaderProgram::ShaderProgram(const GLchar* vertexPath, const GLchar* fragmentPath)
{
	string vertexCode = readShaderCode(vertexPath);
	GLuint vertexID = compileShader(vertexCode.c_str(), GL_VERTEX_SHADER);

	string fragmentCode = readShaderCode(fragmentPath);
	GLuint fragmentID = compileShader(fragmentCode.c_str(), GL_FRAGMENT_SHADER);

	programID = glCreateProgram();
	glAttachShader(programID, vertexID);
	glAttachShader(programID, fragmentID);
	glLinkProgram(programID);

	GLint success;
	glGetProgramiv(programID, GL_LINK_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[512];
		glGetProgramInfoLog(programID, sizeof(infoLog), NULL, infoLog);
		string msg = string("Shader program linking: ") + infoLog;
		throw exception(msg.c_str());
	}

	// Delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(vertexID);
	glDeleteShader(fragmentID);
}


ShaderProgram::~ShaderProgram()
{
}
