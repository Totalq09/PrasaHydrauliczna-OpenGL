#define _USE_MATH_DEFINES
#include "Cylinder.h"

Cylinder::Cylinder(GLfloat radius, GLfloat height, GLuint segments)
{
	this->radius = radius;
	this->height = height;
	this->segments = segments;

	initialize();
}

Cylinder::Cylinder(const Cylinder & c)
{
	this->radius = c.radius;
	this->height = c.height;
	this->segments = c.segments;
	
	model = c.model;

	verticesBase_1 = new Vertex3D[(segments + 1) /** sizeof(Vertex3D)*/];
	std::copy(c.verticesBase_1, c.verticesBase_1 + (segments +1), verticesBase_1);

	indicesBase_1 = new GLuint[3 * segments];
	std::copy(c.indicesBase_1, c.indicesBase_1 + (segments * 3), indicesBase_1);

	verticesBase_2 = new Vertex3D[(segments + 1) /** sizeof(Vertex3D)*/];
	std::copy(c.verticesBase_2, c.verticesBase_2 + (segments + 1), verticesBase_2);

	indicesBase_2 = new GLuint[3 * segments];
	std::copy(c.indicesBase_2, c.indicesBase_2 + (segments * 3), indicesBase_2);

	verticesSide = new Vertex3D[2 * segments /** sizeof(Vertex3D)*/];
	indicesSide = new GLuint[3 * 2 * segments];

	std::copy(c.verticesSide, c.verticesSide + (2 * segments), verticesSide);
	std::copy(c.indicesSide, c.indicesSide + (2 * 3 * segments), indicesSide);

	glGenVertexArrays(1, &VAOBase_1);
	glGenBuffers(1, &VBOBase_1);
	glGenBuffers(1, &EBOBase_1);

	glBindVertexArray(VAOBase_1);

	glBindBuffer(GL_ARRAY_BUFFER, VBOBase_1);
	glBufferData(GL_ARRAY_BUFFER, (segments + 1) * sizeof(Vertex3D), verticesBase_1, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOBase_1);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * segments*sizeof(GLuint), indicesBase_1, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);

	glGenVertexArrays(1, &VAOBase_2);
	glGenBuffers(1, &VBOBase_2);
	glGenBuffers(1, &EBOBase_2);

	glBindVertexArray(VAOBase_2);

	glBindBuffer(GL_ARRAY_BUFFER, VBOBase_2);
	glBufferData(GL_ARRAY_BUFFER, (segments + 1) * sizeof(Vertex3D), verticesBase_2, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOBase_2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * segments*sizeof(GLuint), indicesBase_2, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);

	glGenVertexArrays(1, &VAOSide);
	glGenBuffers(1, &VBOSide);
	glGenBuffers(1, &EBOSide);

	glBindVertexArray(VAOSide);

	glBindBuffer(GL_ARRAY_BUFFER, VBOSide);
	glBufferData(GL_ARRAY_BUFFER, 2 * segments * sizeof(Vertex3D), verticesSide, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOSide);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * 2 * segments*sizeof(GLuint), indicesSide, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);
}

Cylinder::~Cylinder()
{
	//BOTTOM BASE
	//glDeleteVertexArrays(1, &VAOBase_1);
	//glDeleteVertexArrays(1, &EBOBase_1);
	//glDeleteBuffers(1, &VBOBase_1);
	//if (verticesBase_1 != nullptr)
	//	delete[] verticesBase_1;
	//if (indicesBase_1 != nullptr)
	//	delete[] indicesBase_1;

	//TOP BASE
	//glDeleteVertexArrays(1, &VAOBase_2);
	//glDeleteVertexArrays(1, &EBOBase_2);
	//glDeleteBuffers(1, &VBOBase_2);
	//if (verticesBase_2 != nullptr)
	//	delete[] verticesBase_2;
	//if (indicesBase_2 != nullptr)
	//	delete[] indicesBase_2;

	////SIDE
//	glDeleteVertexArrays(1, &VAOSide);
	//glDeleteVertexArrays(1, &EBOSide);
	//glDeleteBuffers(1, &VBOSide);
	/*if (verticesSide != nullptr)
		delete[] verticesSide;
	if (indicesSide != nullptr)
		delete[] indicesSide;*/

}

Cylinder::Cylinder(GLfloat radius, GLfloat height, GLuint segments, Transformation mod)
{
	this->radius = radius;
	this->height = height;
	this->segments = segments;
	model = mod;
	initialize();
}

Cylinder::Cylinder(glm::vec3 translation)
{
	this->radius = 1.0f;
	this->height = 1.0f;
	this->segments = 1.0f;
	model.setPosition(translation);
	initialize();
}

void Cylinder::initialize()
{
	initializeBase_1();
	initializeBase_2();
	initializeSide();
}

void Cylinder::initializeBase_1()
{
	float deltaAngle = 2 * M_PI / segments;

	verticesBase_1 = new Vertex3D[(segments + 1) /** sizeof(Vertex3D)*/];
	indicesBase_1 = new GLuint[3 * segments];

	verticesBase_1[0].x = 0.0f;
	verticesBase_1[0].y = 0.0f;
	verticesBase_1[0].z = 0.0f;
	verticesBase_1[0].xNormal = 0.0f;
	verticesBase_1[0].yNormal = -1.0f;
	verticesBase_1[0].zNormal = 0.0f;
	verticesBase_1[0].xTex = 0.5f;
	verticesBase_1[0].yTex = 0.5f;

	for (int i = 1; i <= segments; i++)
	{
		GLfloat theta = deltaAngle * (i - 1);

		GLfloat x = radius * cosf(theta);
		GLfloat z = radius * sinf(theta);

		GLfloat xTex = 0.5f + 0.5f *cosf(theta);
		GLfloat yTex = 0.5f + 0.5f *sinf(theta);

		verticesBase_1[i].x = x;
		verticesBase_1[i].y = 0.0f;
		verticesBase_1[i].z = z;

		verticesBase_1[i].xNormal = 0.0f;
		verticesBase_1[i].yNormal = -1.0f;
		verticesBase_1[i].zNormal = 0.0f;

		verticesBase_1[i].xTex = xTex;
		verticesBase_1[i].yTex = yTex;
	}

	for (int i = 0; i < segments; i++)
	{
		indicesBase_1[i * 3] = 0;
		indicesBase_1[i * 3 + 1] = i + 1;
		indicesBase_1[i * 3 + 2] = i + 2;
	}

	indicesBase_1[3 * segments - 1] = 1;

	glGenVertexArrays(1, &VAOBase_1);
	glGenBuffers(1, &VBOBase_1);
	glGenBuffers(1, &EBOBase_1);

	glBindVertexArray(VAOBase_1);

	glBindBuffer(GL_ARRAY_BUFFER, VBOBase_1);
	glBufferData(GL_ARRAY_BUFFER, (segments + 1) * sizeof(Vertex3D), verticesBase_1, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOBase_1);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * segments*sizeof(GLuint), indicesBase_1, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);
}

void Cylinder::initializeBase_2()
{
	float deltaAngle = 2 * M_PI / segments;

	verticesBase_2 = new Vertex3D[(segments + 1) /** sizeof(Vertex3D)*/];
	indicesBase_2 = new GLuint[3 * segments];

	for (int i = 0; i <= segments; i++)
	{
		verticesBase_2[i].x = verticesBase_1[i].x;
		verticesBase_2[i].y = height;
		verticesBase_2[i].z = verticesBase_1[i].z;
		verticesBase_2[i].xNormal = 0.0f;
		verticesBase_2[i].yNormal = 1.0f;
		verticesBase_2[i].zNormal = 0.0f;
		verticesBase_2[i].xTex = verticesBase_1[i].xTex;
		verticesBase_2[i].yTex = verticesBase_1[i].yTex;
	}

	for (int i = 0; i < segments; i++)
	{
		indicesBase_2[i * 3] = 0;
		indicesBase_2[i * 3 + 1] = i + 1;
		indicesBase_2[i * 3 + 2] = i + 2;
	}

	indicesBase_2[3 * segments - 1] = 1;

	glGenVertexArrays(1, &VAOBase_2);
	glGenBuffers(1, &VBOBase_2);
	glGenBuffers(1, &EBOBase_2);

	glBindVertexArray(VAOBase_2);

	glBindBuffer(GL_ARRAY_BUFFER, VBOBase_2);
	glBufferData(GL_ARRAY_BUFFER, (segments + 1) * sizeof(Vertex3D), verticesBase_2, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOBase_2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * segments*sizeof(GLuint), indicesBase_2, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);
}

void Cylinder::initializeSide()
{
	verticesSide = new Vertex3D[2 * segments /** sizeof(Vertex3D)*/];
	indicesSide = new GLuint[3 * 2 * segments];

	//a
	verticesSide[0].x = verticesBase_1[1].x;
	verticesSide[0].y = verticesBase_1[1].y;
	verticesSide[0].z = verticesBase_1[1].z;

	//b
	verticesSide[1].x = verticesBase_1[2].x;
	verticesSide[1].y = verticesBase_1[2].y;
	verticesSide[1].z = verticesBase_1[2].z;

	//c
	verticesSide[2].x = verticesBase_2[1].x;
	verticesSide[2].y = verticesBase_2[1].y;
	verticesSide[2].z = verticesBase_2[1].z;

	//d
	verticesSide[3].x = verticesBase_2[2].x;
	verticesSide[3].y = verticesBase_2[2].y;
	verticesSide[3].z = verticesBase_2[2].z;

	for (int i = 2; i < segments; i++)
	{
		verticesSide[i*2].x = verticesBase_1[i+1].x;
		verticesSide[i*2].y = verticesBase_1[i+1].y;
		verticesSide[i*2].z = verticesBase_1[i+1].z;

		verticesSide[i*2 + 1].x = verticesBase_2[i+1].x;
		verticesSide[i*2 + 1].y = verticesBase_2[i+1].y;
		verticesSide[i*2 + 1].z = verticesBase_2[i+1].z;
	}

	//////////////////////////////////////////////////////////

	sideTextureComputing();
	sideNormalsComputing();
	sideIndicesComputing();

	/////////////////////////////////////////////////////////////

	glGenVertexArrays(1, &VAOSide);
	glGenBuffers(1, &VBOSide);
	glGenBuffers(1, &EBOSide);

	glBindVertexArray(VAOSide);

	glBindBuffer(GL_ARRAY_BUFFER, VBOSide);
	glBufferData(GL_ARRAY_BUFFER, 2* segments * sizeof(Vertex3D), verticesSide, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOSide);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * 2 * segments*sizeof(GLuint), indicesSide, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);
}

void Cylinder::sideTextureComputing()
{
	float offset = 1.0f / (segments / 2);
	float textureOffset = 1.0f / (segments / 2);

	verticesSide[0].xTex = 0.0f;
	verticesSide[0].yTex = 0.0f;

	verticesSide[1].xTex = textureOffset;
	verticesSide[1].yTex = 0.0f;

	verticesSide[2].xTex = 0.0f;
	verticesSide[2].yTex = 1.0f;

	verticesSide[3].xTex = textureOffset;
	verticesSide[3].yTex = 1.0f;

	textureOffset += offset;

	int i = 4;
	for (; i < segments; i += 2)
	{
		verticesSide[i].xTex = textureOffset;
		textureOffset += offset;

		verticesSide[i].yTex = 0.0f;
	}

	for (; i < 2 * segments; i += 2)
	{
		verticesSide[i].xTex = textureOffset;
		textureOffset -= offset;

		verticesSide[i].yTex = 0.0f;

	}

	///////////////////////////////////////

	textureOffset = 1.0f / (segments / 2);
	textureOffset += offset;

	i = 5;
	for (; i < segments; i += 2)
	{
		verticesSide[i].xTex = textureOffset;
		textureOffset += offset;

		verticesSide[i].yTex = 1.0f;

	}

	for (; i < 2 * segments; i += 2)
	{
		verticesSide[i].xTex = textureOffset;
		textureOffset -= offset;

		verticesSide[i].yTex = 1.0f;
	}
}

void Cylinder::sideIndicesComputing()
{
	indicesSide[0] = 0;
	indicesSide[1] = 1;
	indicesSide[2] = 2;

	indicesSide[3] = 3;
	indicesSide[4] = 2;
	indicesSide[5] = 1;

	for (int i = 1; i < segments - 1; i++)
	{
		indicesSide[i * 6] = indicesSide[(i - 1) * 6 + 1];
		indicesSide[i * 6 + 1] = i * 2 + 2;
		indicesSide[i * 6 + 2] = indicesSide[(i - 1) * 6 + 3];

		indicesSide[i * 6 + 3] = i * 2 + 2 + 1;
		indicesSide[i * 6 + 4] = indicesSide[(i - 1) * 6 + 3];
		indicesSide[i * 6 + 5] = i * 2 + 2;
	}

	indicesSide[6 * segments - 6] = indicesSide[(segments - 2) * 6 + 1];
	indicesSide[6 * segments - 5] = 0;
	indicesSide[6 * segments - 4] = indicesSide[(segments - 2) * 6 + 3];

	indicesSide[6 * segments - 3] = 2;
	indicesSide[6 * segments - 2] = indicesSide[(segments - 2) * 6 + 3];
	indicesSide[6 * segments - 1] = 0;
}

void Cylinder::sideNormalsComputing()
{
	//UWAGA
	/*kod tej funkcji wyglada nieco "dziko", ale to poniewaz, numeracja wierzcholkow nie byla najlepsza
	i nie ktore sciany/wierzcholki musialem liczyc oddzielnie (pierwsze dwie sciany + ew. ostatnia)*/
	NormalVector * normals = new NormalVector[segments];

	//first face
	NormalVector a, b, n;

	a.x = verticesSide[1].x - verticesSide[0].x;
	a.y = verticesSide[1].y - verticesSide[0].y;
	a.z = verticesSide[1].z - verticesSide[0].z;

	b.x = verticesSide[2].x - verticesSide[0].x;
	b.y = verticesSide[2].y - verticesSide[0].y;
	b.z = verticesSide[2].z - verticesSide[0].z;

	n.x = (a.y * b.z) - (a.z * b.y);
	n.y = (a.z * b.x) - (a.x * b.z);
	n.z = (a.x * b.y) - (a.y * b.x);

	float l = sqrt(n.x * n.x + n.y * n.y + n.z * n.z);

	n.x /= l;
	n.y /= l;
	n.z /= l;

	normals[0].x = n.x;
	normals[0].y = n.y;
	normals[0].z = n.z;

	//second face
	a.x = verticesSide[4].x - verticesSide[1].x;
	a.y = verticesSide[4].y - verticesSide[1].y;
	a.z = verticesSide[4].z - verticesSide[1].z;

	b.x = verticesSide[3].x - verticesSide[1].x;
	b.y = verticesSide[3].y - verticesSide[1].y;
	b.z = verticesSide[3].z - verticesSide[1].z;

	n.x = (a.y * b.z) - (a.z * b.y);
	n.y = (a.z * b.x) - (a.x * b.z);
	n.z = (a.x * b.y) - (a.y * b.x);

	l = sqrt(n.x * n.x + n.y * n.y + n.z * n.z);

	n.x /= l;
	n.y /= l;
	n.z /= l;

	normals[1].x = n.x;
	normals[1].y = n.y;
	normals[1].z = n.z;

	//rest faces - 1
	for (int i = 2; i < segments - 1; i++)
	{
		NormalVector a, b, n;

		a.x = verticesSide[i * 2 + 2].x - verticesSide[i * 2].x;
		a.y = verticesSide[i * 2 + 2].y - verticesSide[i * 2].y;
		a.z = verticesSide[i * 2 + 2].z - verticesSide[i * 2].z;

		b.x = verticesSide[i * 2 + 1].x - verticesSide[i * 2].x;
		b.y = verticesSide[i * 2 + 1].y - verticesSide[i * 2].y;
		b.z = verticesSide[i * 2 + 1].z - verticesSide[i * 2].z;

		n.x = (a.y * b.z) - (a.z * b.y);
		n.y = (a.z * b.x) - (a.x * b.z);
		n.z = (a.x * b.y) - (a.y * b.x);

		float l = sqrt(n.x * n.x + n.y * n.y + n.z * n.z);
		
		n.x /= l;
		n.y /= l;
		n.z /= l;

		normals[i].x = n.x;
		normals[i].y = n.y;
		normals[i].z = n.z;
	}

	//last face
	a, b, n;

	a.x = verticesSide[0].x - verticesSide[2*segments-2].x;
	a.y = verticesSide[0].y - verticesSide[2 * segments - 2].y;
	a.z = verticesSide[0].z - verticesSide[2 * segments - 2].z;

	b.x = verticesSide[2 * segments - 1].x - verticesSide[2 * segments - 2].x;
	b.y = verticesSide[2 * segments - 1].y - verticesSide[2 * segments - 2].y;
	b.z = verticesSide[2 * segments - 1].z - verticesSide[2 * segments - 2].z;

	n.x = (a.y * b.z) - (a.z * b.y);
	n.y = (a.z * b.x) - (a.x * b.z);
	n.z = (a.x * b.y) - (a.y * b.x);

	l = sqrt(n.x * n.x + n.y * n.y + n.z * n.z);

	n.x /= l;
	n.y /= l;
	n.z /= l;

	normals[segments-1].x = n.x;
	normals[segments-1].y = n.y;
	normals[segments-1].z = n.z;

	//already we have face normals, now we need to mix them and asign to vertexes

	//first face
	n.x = normals[0].x + normals[segments - 1].x;
	n.y = normals[0].y + normals[segments - 1].y;
	n.z = normals[0].z + normals[segments - 1].z;

	l = sqrt(n.x * n.x + n.y * n.y + n.z * n.z);

	n.x /= l;
	n.y /= l;
	n.z /= l;

	verticesSide[0].xNormal = -n.x;
	verticesSide[0].yNormal = -n.y;
	verticesSide[0].zNormal = -n.z;

	verticesSide[2].xNormal = -n.x;
	verticesSide[2].yNormal = -n.y;
	verticesSide[2].zNormal = -n.z;

	//second face

	n.x = normals[1].x + normals[0].x;
	n.y = normals[1].y + normals[0].y;
	n.z = normals[1].z + normals[0].z;

	l = sqrt(n.x * n.x + n.y * n.y + n.z * n.z);

	n.x /= l;
	n.y /= l;
	n.z /= l;

	verticesSide[1].xNormal = -n.x;
	verticesSide[1].yNormal = -n.y;
	verticesSide[1].zNormal = -n.z;

	verticesSide[3].xNormal = -n.x;
	verticesSide[3].yNormal = -n.y;
	verticesSide[3].zNormal = -n.z;

	//rest faces

	for (int i = 2; i < segments; i++)
	{
		n.x = normals[i].x + normals[i - 1].x;
		n.y = normals[i].y + normals[i - 1].y;
		n.z = normals[i].z + normals[i - 1].z;

		l = sqrt(n.x * n.x + n.y * n.y + n.z * n.z);

		n.x /= l;
		n.y /= l;
		n.z /= l;

		verticesSide[i*2].xNormal = -n.x;
		verticesSide[i*2].yNormal = -n.y;
		verticesSide[i*2].zNormal = -n.z;

		verticesSide[i*2+1].xNormal = -n.x;
		verticesSide[i*2+1].yNormal = -n.y;
		verticesSide[i*2+1].zNormal = -n.z;
	}

	delete[] normals;
}

void Cylinder::renderBases(ShaderProgram & shader)
{
	GLint modelLoc = glGetUniformLocation(shader.getProgramID(), "model");
	glm::mat4 model = this->model.getModel();
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, material.diffuse);
	glUniform1i(glGetUniformLocation(shader.getProgramID(), "material.diffuse"), 0);
	glUniform1f(glGetUniformLocation(shader.getProgramID(), "material.specularStrength"), material.specularStrength);

	//Draw the container (using container's vertex attributes)
	glBindVertexArray(VAOBase_1);
	glDrawElements(GL_TRIANGLES, 3 * segments, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glBindVertexArray(VAOBase_2);
	glDrawElements(GL_TRIANGLES, 3 * segments, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Cylinder::renderSide(ShaderProgram & shader)
{
	GLint modelLoc = glGetUniformLocation(shader.getProgramID(), "model");
	glm::mat4 model = this->model.getModel();
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, material.diffuse);
	glUniform1i(glGetUniformLocation(shader.getProgramID(), "material.diffuse"), 0);
	glUniform1f(glGetUniformLocation(shader.getProgramID(), "material.specularStrength"), material.specularStrength);

	//Draw the container (using container's vertex attributes)
	glBindVertexArray(VAOSide);
	glDrawElements(GL_TRIANGLES, 3 * 2 * segments, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Cylinder::render(ShaderProgram & shader)
{
	renderBases(shader);
	renderSide(shader);
}


void Cylinder::setMaterial(Material material)
{
	this->material = material;
}

