#include "Transformation.h"

Transformation::Transformation(glm::vec3 vec, float angle, glm::vec3 axis, glm::vec3 ratio)
{
	model = glm::mat4();

	position = vec;
	this->angle = angle;
	this->axis = axis;
	this->ratio = ratio;
}

Transformation::~Transformation()
{

}

///////////////////////////////////////////////////////////

void Transformation::setPosition(glm::vec3 pos)
{
	position = pos;
}

void Transformation::setScale(glm::vec3 scale)
{
	this->ratio = scale;
}

void Transformation::setScale(float ratio)
{
	this->ratio = glm::vec3(ratio, ratio, ratio);
}

void Transformation::scale(glm::vec3 scale)
{
	ratio += scale;
}

void Transformation::setRotation(float angle, glm::vec3 axis)
{
	this->angle = angle;
	this->axis = axis;
}

void Transformation::move(glm::vec3 vec)
{
	position += vec;
}

glm::mat4 Transformation::getModel()
{
	model = glm::mat4();

	model = glm::translate(model, position);
	model = glm::rotate(model, glm::radians(angle), axis);
	model = glm::scale(model, ratio);

	return model;
}

