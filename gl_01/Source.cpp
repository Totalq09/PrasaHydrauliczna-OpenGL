#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <SOIL.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ShaderProgram.h"
#include "Camera.h"
#include "Transformation.h"
#include "BoxVertices.h"
#include "Light.h"
#include "Material.h"
#include "Box.h"
#include "Cylinder.h"

#include <algorithm>

GLuint loadCubemap(vector<const GLchar*> faces);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void do_movement();

void drawLight(GLuint & VBO, GLuint & VAO, Transformation box, ShaderProgram & shader);

const GLuint WIDTH = 1600, HEIGHT = 800;

// Camera
Camera  camera(glm::vec3(4.0f, 2.0f, 3.0f));
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool    keys[1024];

// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame

typedef struct
{
	GLfloat x;
	GLfloat y;
	GLfloat z;
} Vertex3D2;

const float pressY = -0.7f;

int main()
{
	GLfloat cubeVertices[] = {
		// Positions          // Texture Coords
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

		-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f
	};
	GLfloat skyboxVertices[] = {
		// Positions          
		-1.0f, 1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f,

		-1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,

		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,

		-1.0f, 1.0f, -1.0f,
		1.0f, 1.0f, -1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 1.0f
	};

	///////////////////INITIALIZE OPENGL////////////////////

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	glfwWindowHint(GLFW_SAMPLES, 4);
	glEnable(GL_MULTISAMPLE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Prasa hydrauliczna", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glewExperimental = GL_TRUE;
	glewInit();
	glEnable(GL_DEPTH_TEST);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glViewport(0, 0, WIDTH, HEIGHT);

	/////////////////////////////SHADERS///////////////////////////////////

	ShaderProgram solidShader("SolidShader.vert", "SolidShader.frag");
	ShaderProgram lightShader("LightShader.vert", "LightShader.frag");
	//ShaderProgram circleShader("SolidNoTexShader.vert", "SolidNoTexShader.frag");
	ShaderProgram movingShader("SolidShader.vert", "movingTextureShader.frag");
	ShaderProgram skyboxShader("Skybox.vert", "Skybox.frag");

	////////////////////////////TEXTURES//////////////////////////////////

	GLuint floorTexture;
	glGenTextures(1, &floorTexture);
	int width, height;
	unsigned char* image;
	image = SOIL_load_image("wood2.png", &width, &height, 0, SOIL_LOAD_RGB);
	//image = SOIL_load_image("tiles1.png", &width, &height, 0, SOIL_LOAD_RGB);
	glBindTexture(GL_TEXTURE_2D, floorTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);

	glBindTexture(GL_TEXTURE_2D, 0);

	GLuint metalTexture;
	glGenTextures(1, &metalTexture);
	image = SOIL_load_image("metal3.png", &width, &height, 0, SOIL_LOAD_RGB);
	glBindTexture(GL_TEXTURE_2D, metalTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);

	GLuint conveyorTexture;
	glGenTextures(1, &conveyorTexture);
	image = SOIL_load_image("rubber.png", &width, &height, 0, SOIL_LOAD_RGB);
	glBindTexture(GL_TEXTURE_2D, conveyorTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);

	glBindTexture(GL_TEXTURE_2D, 0);

	GLuint electronicTexture;
	glGenTextures(1, &electronicTexture);
	image = SOIL_load_image("electronicBlue.png", &width, &height, 0, SOIL_LOAD_RGB);
	glBindTexture(GL_TEXTURE_2D, electronicTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);

	glBindTexture(GL_TEXTURE_2D, 0);

	GLuint electronic2Texture;
	glGenTextures(1, &electronic2Texture);
	image = SOIL_load_image("electronic2.png", &width, &height, 0, SOIL_LOAD_RGB);
	glBindTexture(GL_TEXTURE_2D, electronic2Texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);

	glBindTexture(GL_TEXTURE_2D, 0);

	GLuint metalNetTexture;
	glGenTextures(1, &metalNetTexture);
	image = SOIL_load_image("metalNet.png", &width, &height, 0, SOIL_LOAD_RGB);
	glBindTexture(GL_TEXTURE_2D, metalNetTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);

	glBindTexture(GL_TEXTURE_2D, 0);

	GLuint rollerTexture;
	glGenTextures(1, &rollerTexture);
	image = SOIL_load_image("roller.png", &width, &height, 0, SOIL_LOAD_RGB);
	glBindTexture(GL_TEXTURE_2D, rollerTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);

	glBindTexture(GL_TEXTURE_2D, 0);

	//GLuint skyboxTexture;
	//glGenTextures(1, &skyboxTexture);
	//image = SOIL_load_image("skybox.png", &width, &height, 0, SOIL_LOAD_RGB);
	//// Assign texture to ID
	//glBindTexture(GL_TEXTURE_2D, skyboxTexture);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	//glGenerateMipmap(GL_TEXTURE_2D);

	//// Parameters
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glBindTexture(GL_TEXTURE_2D, 0);

	//SOIL_free_image_data(image);

	//glBindTexture(GL_TEXTURE_2D, 0);

	////////////////////SKYBOX////////////////////////

	GLuint cubeVAO, cubeVBO;
	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &cubeVBO);
	glBindVertexArray(cubeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glBindVertexArray(0);
	// Setup skybox VAO
	GLuint skyboxVAO, skyboxVBO;
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glBindVertexArray(0);


	// Cubemap (Skybox)
	vector<const GLchar*> faces;
	faces.push_back("skybox/right.png");
	faces.push_back("skybox/left.png");
	faces.push_back("skybox/top.png");
	faces.push_back("skybox/bottom.png");
	faces.push_back("skybox/back.png");
	faces.push_back("skybox/front.png");
	GLuint cubemapTexture = loadCubemap(faces);

	//////////////////////LIGHTS///////////////////////

	Light normalLight;
	normalLight.position = glm::vec3(1.5f, 2.0f, 2.0f);
	normalLight.transformation.setPosition(normalLight.position);
	normalLight.transformation.setScale(0.2f);
	normalLight.ambient = glm::vec3(0.34f, 0.35f, 0.37f);
	normalLight.diffuse = glm::vec3(0.74f, 0.75f, 0.75f);
	normalLight.specular = glm::vec3(1.0f, 1.0f, 1.0f);

	/////////////////////MATERIALS//////////////////////

	Material floorMaterial;
	floorMaterial.diffuse = floorTexture;
	floorMaterial.specularStrength = 0.15f;

	Material metalicMaterial;
	metalicMaterial.diffuse = metalTexture;
	metalicMaterial.specularStrength = 0.75f;

	Material electronicMaterial;
	electronicMaterial.diffuse = electronicTexture;
	electronicMaterial.specularStrength = 0.25;

	Material electronic2Material;
	electronic2Material.diffuse = electronic2Texture;
	electronic2Material.specularStrength = 0.5;

	Material conveyorMaterial;
	conveyorMaterial.diffuse = conveyorTexture;
	conveyorMaterial.specularStrength = 0.65;

	Material metalNet;
	metalNet.diffuse = metalNetTexture;
	metalNet.specularStrength = 0.8;

	Material rollerMaterial;
	rollerMaterial.diffuse = rollerTexture;
	rollerMaterial.specularStrength = 0.1;

	////////////////////OBJECTS//////////////////////

	Box floor;
	floor.model.setPosition(glm::vec3(0.0f, -2.0f, 0.0f));
	floor.model.setScale(glm::vec3(8.0f, 0.2f, 5.0f));
	floor.setMaterial(floorMaterial);

	Box box1;

	box1.model.setPosition(glm::vec3(0.0f, -1.1f, -1.0f));
	box1.model.setScale(glm::vec3(0.5f, 1.75f, 0.5f));
	box1.setMaterial(metalicMaterial);

	Box box2;

	box2.model.setPosition(glm::vec3(0.0f, -1.1f, 1.0f));
	box2.model.setScale(glm::vec3(0.5f, 1.75f, 0.5f));
	box2.setMaterial(metalicMaterial);

	Box box3;

	box3.model.setRotation(90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	box3.model.setScale(glm::vec3(0.75f, 3.5f, 0.55f));
	box3.setMaterial(electronicMaterial);

	Box machineEntry1;
	machineEntry1.model.setPosition(glm::vec3(-3.0f, -1.0f, 0.0f));
	machineEntry1.model.setScale(glm::vec3(1.2f, 2.0f, 1.2f));
	machineEntry1.setMaterial(electronicMaterial);

	Box machineEntry2;
	machineEntry2.model.setPosition(glm::vec3(3.0f, -1.0f, 0.0f));
	machineEntry2.model.setScale(glm::vec3(1.2f, 2.0f, 1.2f));
	machineEntry2.setMaterial(electronicMaterial);

	Box box6;
	box6.model.setPosition(glm::vec3(0.0f, 0.0f, -1.0f));
	box6.model.setScale(0.9f);
	box6.setMaterial(electronic2Material);

	Box conveyor;
	conveyor.model.setPosition(glm::vec3(0.0f, -1.2f, 0.0f));
	conveyor.model.setRotation(90.0f);
	conveyor.model.setScale(glm::vec3(0.7f, 0.1f, 6.5f));
	conveyor.setMaterial(conveyorMaterial);

	///////

	Cylinder press(0.125f, 1.0f, 128);
	press.model.setPosition(glm::vec3(0.0f, pressY, 0.0f));
	press.model.setScale(glm::vec3(2.0f, 2.0f, 2.0f));
	press.setMaterial(metalNet);

	std::vector<Cylinder *> rollers;
	Cylinder c1(0.125f, 0.25f, 128);
	rollers.push_back(new Cylinder(0.125f, 0.25f, 128));

	auto iter = rollers.end() - 1;
	(*iter)->setMaterial(rollerMaterial);
	(*iter)->model.setPosition(machineEntry2.model.getPosition());
	(*iter)->model.move(glm::vec3(0.0f, -0.15f, 0.0f));

	/////////////////////VAO + VBO///////////////////////////////

	// First, set the container's VAO (and VBO)
	GLuint VBO;
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, BoxVertices::size, BoxVertices::vertices, GL_STATIC_DRAW);

	GLuint lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	//////////////////////MAIN LOOP//////////////////////////
	float dt = 0;
	bool rollerReady = false;
	bool rollerScaling = false;
	bool goingUp = false;
	float velocity;
	float suppres = 0;
	while (!glfwWindowShouldClose(window))
	{
	
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glDepthMask(GL_FALSE);// Remember to turn depth writing off
		skyboxShader.use();
		glm::mat4 view = glm::mat4(glm::mat3(camera.GetViewMatrix()));	// Remove any translation component of the view matrix
		glm::mat4 projection = glm::perspective(camera.getZoom(), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
		glUniformMatrix4fv(glGetUniformLocation(skyboxShader.getProgramID(), "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(skyboxShader.getProgramID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		// skybox cube
		glBindVertexArray(skyboxVAO);
		glActiveTexture(GL_TEXTURE0);
		glUniform1i(glGetUniformLocation(skyboxShader.getProgramID(), "skybox"), 0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glDepthMask(GL_TRUE);

		////////////////////////////////////////////////

		suppres += deltaTime;

		glfwPollEvents();
		do_movement();

		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		////////////////////////OBJECTS/////////////////////////////

		solidShader.use();
		///////////////////The same for every object in scene////////////////////////
		GLint lightPosLoc = glGetUniformLocation(solidShader.getProgramID(), "light.position");
		GLint viewPosLoc = glGetUniformLocation(solidShader.getProgramID(), "viewPos");
		glUniform3f(viewPosLoc, camera.getPosition().x, camera.getPosition().y, camera.getPosition().z);
		glUniform3f(lightPosLoc, normalLight.position.x, normalLight.position.y, normalLight.position.z);

		glUniform3f(glGetUniformLocation(solidShader.getProgramID(), "light.ambient"), normalLight.ambient.x, normalLight.ambient.y, normalLight.ambient.z);
		glUniform3f(glGetUniformLocation(solidShader.getProgramID(), "light.diffuse"), normalLight.diffuse.x, normalLight.diffuse.y, normalLight.diffuse.z);
		glUniform3f(glGetUniformLocation(solidShader.getProgramID(), "light.specular"), normalLight.specular.x, normalLight.specular.y, normalLight.specular.z);

		// Create camera transformations
		view = camera.GetViewMatrix();
		projection = glm::perspective(camera.getZoom(), (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);
		// Get the uniform locations

		GLint viewLoc = glGetUniformLocation(solidShader.getProgramID(), "view");
		GLint projLoc = glGetUniformLocation(solidShader.getProgramID(), "projection");
		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		//////////////////////////BOXES///////////////////////////////

		floor.render(solidShader);
		box1.render(solidShader);
		box2.render(solidShader);
		box3.render(solidShader);
		machineEntry1.render(solidShader);
		machineEntry2.render(solidShader);
		box6.render(solidShader);

		////////////////////////DYNAMICS///////////////////////////

		velocity = 0.03 * deltaTime;
		std::vector<Cylinder *>::iterator iter = rollers.begin();

		if (rollerReady == false)
		{
			for (iter = rollers.begin() ; iter != rollers.end(); iter++)
			{
				if (abs((*iter)->model.getPosition().x - press.model.getPosition().x) < 0.01 && suppres > 2.0f)
				{
					rollerReady = true;
				}
			}

			if (rollerReady == false)
			{
				for (auto iter = rollers.begin(); iter != rollers.end(); iter++)
				{
					(*iter)->model.move(glm::vec3(-velocity * 7, 0.0f, 0.0f));
				//	(*iter)->render(solidShader);
				}

				for (auto iter = rollers.begin(); iter != rollers.end(); iter++)
				{
					if (abs((*iter)->model.getPosition().x - machineEntry1.model.getPosition().x) < 0.1)
					{
						delete *iter;
						iter = rollers.erase(iter);
						break;
					}
						
				}

				if (abs((*(rollers.end() - 1))->model.getPosition().x - machineEntry2.model.getPosition().x) > 1.0)
				{
					rollers.push_back(new Cylinder(0.125f, 0.25f, 128));
					
					auto iter = rollers.end() - 1;
					(*iter)->setMaterial(rollerMaterial);
					(*iter)->model.setPosition(machineEntry2.model.getPosition());
					(*iter)->model.move(glm::vec3(0.0f, -0.15f, 0.0f));
				}

				dt += velocity;
			}
		}

		if (rollerReady == true)
		{
			for (iter = rollers.begin(); iter != rollers.end(); iter++)
			{
				if (abs((*iter)->model.getPosition().x - press.model.getPosition().x) < 0.01 && suppres > 2.0f)
				{
					break;
				}
			}

			if (goingUp == false)
			{
				press.model.move(glm::vec3(0.0f, -velocity*2, 0.0f));

				if (rollerScaling == false)
				{
					if (abs((*iter)->model.getPosition().y + (*iter)->getHeight() - press.model.getPosition().y) < 0.01)
						rollerScaling = true;
				}
				else
				{
					(*iter)->model.scale(glm::vec3(velocity * 8, -velocity*7, velocity * 8));

					if ((*iter)->model.getScale().y < 0.4)
					{
						goingUp = true;
					}
				}
			}
			else
			{
				press.model.move(glm::vec3(0.0f, velocity*2, 0.0f));

				if (abs(pressY - press.model.getPosition().y) < 0.005f)
				{
					press.model.setPosition(glm::vec3(0.0f, pressY, 0.0f));
					goingUp = false;
					rollerScaling = false;
					rollerReady = false;
					suppres = 0;
				}
			}
		}
		

		press.render(solidShader);
		
		for (auto iter = rollers.begin(); iter != rollers.end(); iter++)
		{
			(*iter)->render(solidShader);
		}

		///////////////////////CONVEYOR////////////////////////////

		movingShader.use();

		lightPosLoc = glGetUniformLocation(movingShader.getProgramID(), "light.position");
		viewPosLoc = glGetUniformLocation(movingShader.getProgramID(), "viewPos");
		glUniform3f(viewPosLoc, camera.getPosition().x, camera.getPosition().y, camera.getPosition().z);
		glUniform3f(lightPosLoc, normalLight.position.x, normalLight.position.y, normalLight.position.z);

		glUniform3f(glGetUniformLocation(movingShader.getProgramID(), "light.ambient"), normalLight.ambient.x, normalLight.ambient.y, normalLight.ambient.z);
		glUniform3f(glGetUniformLocation(movingShader.getProgramID(), "light.diffuse"), normalLight.diffuse.x, normalLight.diffuse.y, normalLight.diffuse.z);
		glUniform3f(glGetUniformLocation(movingShader.getProgramID(), "light.specular"), normalLight.specular.x, normalLight.specular.y, normalLight.specular.z);

		viewLoc = glGetUniformLocation(movingShader.getProgramID(), "view");
		projLoc = glGetUniformLocation(movingShader.getProgramID(), "projection");
		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		glUniform1f(glGetUniformLocation(movingShader.getProgramID(), "Time"), dt);

		conveyor.render(movingShader);

		///////////////LIGHTS///////////////////////////
	
		//lightShader.use();

		//viewLoc = glGetUniformLocation(lightShader.getProgramID(), "view");
		//projLoc = glGetUniformLocation(lightShader.getProgramID(), "projection");
		//glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		//glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		//drawLight(VBO, lightVAO, normalLight.transformation, lightShader);

		glfwSwapBuffers(window);
	}

	// Terminate GLFW, clearing any resources allocated by GLFW.
	glDeleteVertexArrays(1, &lightVAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();

	rollers.clear();

	return 0;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////


void drawLight(GLuint & VBO, GLuint & VAO, Transformation trans, ShaderProgram & shader)
{
	GLint modelLoc = glGetUniformLocation(shader.getProgramID(), "model");

	// Draw the container (using container's vertex attributes)
	glBindVertexArray(VAO);
	glm::mat4 model = trans.getModel();
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}

// Loads a cubemap texture from 6 individual texture faces
// Order should be:
// +X (right)
// -X (left)
// +Y (top)
// -Y (bottom)
// +Z (front) 
// -Z (back)
GLuint loadCubemap(vector<const GLchar*> faces)
{
	GLuint textureID;
	glGenTextures(1, &textureID);

	int width, height;
	unsigned char* image;

	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	for (GLuint i = 0; i < faces.size(); i++)
	{
		image = SOIL_load_image(faces[i], &width, &height, 0, SOIL_LOAD_RGB);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		SOIL_free_image_data(image);
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	return textureID;
}

//////////////////FUNCTIONS RELATED TO CAMERA//////////////////////////////////

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}

void do_movement()
{
	// Camera controls
	if (keys[GLFW_KEY_W])
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (keys[GLFW_KEY_S])
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (keys[GLFW_KEY_A])
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (keys[GLFW_KEY_D])
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

bool firstMouse = true;
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos;  // Reversed since y-coordinates go from bottom to left

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}