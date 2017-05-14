//#include <iostream>
//#include <cmath>
//
//#define GLEW_STATIC
//#include <GL/glew.h>
//
//#include <GLFW/glfw3.h>
//
//#include <SOIL.h>
//
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//
//#include "ShaderProgram.h"
//#include "Camera.h"
//#include "Transformation.h"
//#include "BoxVertices.h"
//#include "Light.h"
//#include "Material.h"
//
//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void do_movement();
//
//void drawObject(GLuint & VBO, GLuint & VAO, Transformation box, ShaderProgram & shader, Material material, bool light = false);
//
//const GLuint WIDTH = 1600, HEIGHT = 800;
//
//// Camera
//Camera  camera(glm::vec3(4.0f, 2.0f, 3.0f));
//GLfloat lastX = WIDTH / 2.0;
//GLfloat lastY = HEIGHT / 2.0;
//bool    keys[1024];
//
//// Deltatime
//GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
//GLfloat lastFrame = 0.0f;  	// Time of last frame
//
//int main()
//{
//	///////////////////INITIALIZE OPENGL///////////////////////////////////////
//
//	glfwInit();
//
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
//
//
//	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Prasa hydrauliczna", nullptr, nullptr);
//	glfwMakeContextCurrent(window);
//
//	glfwSetKeyCallback(window, key_callback);
//	glfwSetCursorPosCallback(window, mouse_callback);
//	glfwSetScrollCallback(window, scroll_callback);
//
//
//	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//	glewExperimental = GL_TRUE;
//	glewInit();
//	glEnable(GL_DEPTH_TEST);
//
//	glfwWindowHint(GLFW_SAMPLES, 4);
//	glEnable(GL_MULTISAMPLE);
//
//	glViewport(0, 0, WIDTH, HEIGHT);
//
//	////////////////////////SHADERS///////////////////////////////////
//
//	ShaderProgram solidShader("SolidShader.vert", "SolidShader.frag");
//	ShaderProgram lightShader("LightShader.vert", "LightShader.frag");
//
//	///////////////////////TEXTURES//////////////////////////////////
//
//	GLuint floorTexture;
//	glGenTextures(1, &floorTexture);
//	int width, height;
//	unsigned char* image;
//	image = SOIL_load_image("wood.png", &width, &height, 0, SOIL_LOAD_RGB);
//	glBindTexture(GL_TEXTURE_2D, floorTexture);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
//	glGenerateMipmap(GL_TEXTURE_2D);
//	SOIL_free_image_data(image);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
//
//	glBindTexture(GL_TEXTURE_2D, 0);
//
//	GLuint metalTexture;
//	glGenTextures(1, &metalTexture);
//	image = SOIL_load_image("metal1.png", &width, &height, 0, SOIL_LOAD_RGB);
//	glBindTexture(GL_TEXTURE_2D, metalTexture);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
//	glGenerateMipmap(GL_TEXTURE_2D);
//	SOIL_free_image_data(image);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
//
//	glBindTexture(GL_TEXTURE_2D, 0);
//
//	//////////////////////LIGHTS///////////////////////
//
//	Light normalLight;
//	normalLight.position = glm::vec3(1.2f, 1.0f, 2.0f);
//	normalLight.transformation.translate(normalLight.position);
//	normalLight.transformation.scale(0.2f);
//	normalLight.ambient = glm::vec3(0.2f, 0.2f, 0.2f);
//	normalLight.diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
//	normalLight.specular = glm::vec3(1.0f, 1.0f, 1.0f);
//
//	/////////////////////MATERIALS//////////////////////
//
//	Material floorMaterial;
//	floorMaterial.diffuse = floorTexture;
//	floorMaterial.specularStrength = 0.15f;
//
//	Material metalicMaterial;
//	metalicMaterial.diffuse = metalTexture;
//	metalicMaterial.specularStrength = 0.75f;
//
//	////////////////////OBJECTS////////////////////////////////////
//
//	Transformation floor;
//
//	floor.translate(glm::vec3(0.0f, -2.0f, 0.0f));
//	floor.scale(glm::vec3(8.0f, 0.2f, 5.0f));
//
//	Transformation box1;
//
//	box1.translate(glm::vec3(0.0f, -1.1f, -1.0f));
//	box1.scale(glm::vec3(0.5f, 1.75f, 0.5f));
//
//	Transformation box2;
//
//	box2.translate(glm::vec3(0.0f, -1.1f, 1.0f));
//	box2.scale(glm::vec3(0.5f, 1.75f, 0.5f));
//
//	Transformation box3;
//
//	box3.rotate(90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
//	box3.scale(glm::vec3(0.55f, 3.5f, 0.55f));
//
//	/////////////////////VAO + VBO///////////////////////////////
//
//	// First, set the container's VAO (and VBO)
//	GLuint VBO, boxVAO;
//	glGenVertexArrays(1, &boxVAO);
//	glGenBuffers(1, &VBO);
//
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, BoxVertices::size, BoxVertices::vertices, GL_STATIC_DRAW);
//
//	glBindVertexArray(boxVAO);
//	// Position attribute
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
//	glEnableVertexAttribArray(0);
//	// Normal attribute
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
//	glEnableVertexAttribArray(1);
//
//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
//	glEnableVertexAttribArray(2);
//	glBindVertexArray(0);
//
//	GLuint lightVAO;
//	glGenVertexArrays(1, &lightVAO);
//	glBindVertexArray(lightVAO);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
//	glEnableVertexAttribArray(0);
//	glBindVertexArray(0);
//
//	//////////////////////MAIN LOOP//////////////////////////
//
//	while (!glfwWindowShouldClose(window))
//	{
//		GLfloat currentFrame = glfwGetTime();
//		deltaTime = currentFrame - lastFrame;
//		lastFrame = currentFrame;
//
//		glfwPollEvents();
//		do_movement();
//
//		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//		////////////////////////OBJECTS/////////////////////////////
//
//		solidShader.use();
//		///////////////////The same for every object in scene////////////////////////
//		GLint lightPosLoc = glGetUniformLocation(solidShader.getProgramID(), "light.position");
//		GLint viewPosLoc = glGetUniformLocation(solidShader.getProgramID(), "viewPos");
//		glUniform3f(viewPosLoc, camera.getPosition().x, camera.getPosition().y, camera.getPosition().z);
//		glUniform3f(lightPosLoc, normalLight.position.x, normalLight.position.y, normalLight.position.z);
//
//		glUniform3f(glGetUniformLocation(solidShader.getProgramID(), "light.ambient"), normalLight.ambient.x, normalLight.ambient.y, normalLight.ambient.z);
//		glUniform3f(glGetUniformLocation(solidShader.getProgramID(), "light.diffuse"), normalLight.diffuse.x, normalLight.diffuse.y, normalLight.diffuse.z);
//		glUniform3f(glGetUniformLocation(solidShader.getProgramID(), "light.specular"), normalLight.specular.x, normalLight.specular.y, normalLight.specular.z);
//
//		// Create camera transformations
//		glm::mat4 view;
//		view = camera.GetViewMatrix();
//		glm::mat4 projection = glm::perspective(camera.getZoom(), (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);
//		// Get the uniform locations
//
//		GLint viewLoc = glGetUniformLocation(solidShader.getProgramID(), "view");
//		GLint projLoc = glGetUniformLocation(solidShader.getProgramID(), "projection");
//		// Pass the matrices to the shader
//		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
//		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
//
//		drawObject(VBO, boxVAO, floor, solidShader, floorMaterial);
//		drawObject(VBO, boxVAO, box1, solidShader, metalicMaterial);
//		drawObject(VBO, boxVAO, box2, solidShader, metalicMaterial);
//		drawObject(VBO, boxVAO, box3, solidShader, metalicMaterial);
//
//		///////////////LIGHTS///////////////////////////
//
//		lightShader.use();
//
//		viewLoc = glGetUniformLocation(lightShader.getProgramID(), "view");
//		projLoc = glGetUniformLocation(lightShader.getProgramID(), "projection");
//		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
//		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
//
//		drawObject(VBO, lightVAO, normalLight.transformation, lightShader, floorMaterial, true);
//
//		// Swap the screen buffers
//		glfwSwapBuffers(window);
//	}
//
//	// Terminate GLFW, clearing any resources allocated by GLFW.
//	glDeleteVertexArrays(1, &boxVAO);
//	glDeleteBuffers(1, &VBO);
//
//	glfwTerminate();
//	return 0;
//}
//
//void drawObject(GLuint & VBO, GLuint & VAO, Transformation box, ShaderProgram & shader, Material material, bool light)
//{
//	GLint modelLoc = glGetUniformLocation(shader.getProgramID(), "model");
//
//	if (light == false)
//	{
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_2D, material.diffuse);
//		glUniform1i(glGetUniformLocation(shader.getProgramID(), "material.diffuse"), 0);
//		glUniform1f(glGetUniformLocation(shader.getProgramID(), "material.specularStrength"), material.specularStrength);
//	}
//
//	// Draw the container (using container's vertex attributes)
//	glBindVertexArray(VAO);
//	glm::mat4 model = box.getModel();
//	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
//	glDrawArrays(GL_TRIANGLES, 0, 36);
//
//	glBindVertexArray(0);
//}
//
////////////////////FUNCTIONS RELATED TO CAMERA//////////////////////////////////
//
//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
//{
//	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, GL_TRUE);
//	if (key >= 0 && key < 1024)
//	{
//		if (action == GLFW_PRESS)
//			keys[key] = true;
//		else if (action == GLFW_RELEASE)
//			keys[key] = false;
//	}
//}
//
//void do_movement()
//{
//	// Camera controls
//	if (keys[GLFW_KEY_W])
//		camera.ProcessKeyboard(FORWARD, deltaTime);
//	if (keys[GLFW_KEY_S])
//		camera.ProcessKeyboard(BACKWARD, deltaTime);
//	if (keys[GLFW_KEY_A])
//		camera.ProcessKeyboard(LEFT, deltaTime);
//	if (keys[GLFW_KEY_D])
//		camera.ProcessKeyboard(RIGHT, deltaTime);
//}
//
//bool firstMouse = true;
//void mouse_callback(GLFWwindow* window, double xpos, double ypos)
//{
//	if (firstMouse)
//	{
//		lastX = xpos;
//		lastY = ypos;
//		firstMouse = false;
//	}
//
//	GLfloat xoffset = xpos - lastX;
//	GLfloat yoffset = lastY - ypos;  // Reversed since y-coordinates go from bottom to left
//
//	lastX = xpos;
//	lastY = ypos;
//
//	camera.ProcessMouseMovement(xoffset, yoffset);
//}
//
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
//{
//	camera.ProcessMouseScroll(yoffset);
//}