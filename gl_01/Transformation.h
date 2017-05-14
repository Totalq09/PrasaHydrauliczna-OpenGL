#pragma once

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Transformation
{
	glm::mat4 model;

	glm::vec3 position;
	glm::vec3 ratio;
	float angle;
	glm::vec3 axis;

public:
	Transformation(glm::vec3 vec = glm::vec3(0.0f, 0.0f, 0.0f), float angle = 0.0f, glm::vec3 axis = glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3 ratio = glm::vec3(1.0f, 1.0f, 1.0f));
	~Transformation();
	
	//void translate(glm::vec3 vec);
	//void rotate(float angle, glm::vec3 axis = glm::vec3(0.0f, 1.0f, 0.0f));
	//void scale(glm::vec3 ratio);
	//void scale(float ratio);

	glm::mat4 getModel();	

	glm::vec3 getPosition() { return position; };
	glm::vec3 getScale() { return ratio; };
	
	void setPosition(glm::vec3 pos);
	void setScale(glm::vec3 scale);
	void setScale(float ratio);
	void scale(glm::vec3 scale);
	void setRotation(float angle, glm::vec3 axis = glm::vec3(0.0f, 1.0f, 0.0f));


	void move(glm::vec3 vec);

};

