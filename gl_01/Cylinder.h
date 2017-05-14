#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

#include "Transformation.h"
#include "BoxVertices.h"
#include "Material.h"
#include "ShaderProgram.h"

typedef struct
{
	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLfloat xNormal;
	GLfloat yNormal;
	GLfloat zNormal;
	GLfloat xTex;
	GLfloat yTex;

} Vertex3D;

typedef struct
{
	GLfloat x;
	GLfloat y;
	GLfloat z;

} NormalVector;

class Cylinder
{
private:
	GLfloat radius;
	GLfloat height;
	GLuint segments;

	GLuint VAOBase_1, VBOBase_1, EBOBase_1;
	GLuint VAOBase_2, VBOBase_2, EBOBase_2;
	GLuint VAOSide, VBOSide, EBOSide;

	GLuint * indicesBase_1 = nullptr, * indicesBase_2 = nullptr, * indicesSide = nullptr;

	Vertex3D * verticesBase_1 = nullptr;
	Vertex3D * verticesBase_2 = nullptr;
	Vertex3D * verticesSide = nullptr;

	Material material;

	void initialize();
	void initializeBase_1();
	void initializeBase_2();
	void initializeSide();

	void sideIndicesComputing();
	void sideTextureComputing();
	void sideNormalsComputing();
	void createBuffer();

	void renderBases(ShaderProgram & shader);
	void renderSide(ShaderProgram & shader);
public:
	Transformation model;

	Cylinder(GLfloat radius, GLfloat height, GLuint segments, Transformation mod);
	Cylinder(glm::vec3 translation);
	Cylinder(GLfloat radius = 1.0f, GLfloat height = 1.0f, GLuint segments = 32);
	Cylinder(const Cylinder & c);
	~Cylinder();

	void setMaterial(Material);

	void render(ShaderProgram & shader);

	float getHeight() { return height * model.getScale().y; };
};

