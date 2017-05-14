//#define GLEW_STATIC
//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//#include <SOIL.h>
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//
//#include "ShaderProgram.h"
//#include "Camera.h"
//#include <iostream>
//using namespace std;
//
//const GLuint WIDTH = 800, HEIGHT = 600;
//
//Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
//
//bool keys[1024];
//GLfloat lastX = 400, lastY = 300;
//bool firstMouse = true;
//
//GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
//GLfloat lastFrame = 0.0f;  	// Time of last frame
//
//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
//{
//	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, GL_TRUE);
//
//	if (action == GLFW_PRESS)
//		keys[key] = true;
//	else if (action == GLFW_RELEASE)
//		keys[key] = false;
//}
//
//void doMovement()
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
//
//void mouse_callback(GLFWwindow* window, double xpos, double ypos)
//{
//	if (firstMouse)
//	{
//		lastX = xpos;
//		lastY = ypos;
//		firstMouse = false;
//		return;
//	}
//
//	GLfloat xoffset = xpos - lastX;
//	GLfloat yoffset = lastY - ypos;
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
//
///////////////////////////////////////////////////////////////////////////////
//
//int main()
//{
//	if (glfwInit() != GL_TRUE)
//	{
//		cout << "GLFW initialization failed" << endl;
//		return -1;
//	}
//
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//	// zeby sobie zycie ulatwic, scena 3d i rzut perspektywiczny - zmieniaja sie proporcje bokow okna i bum
//	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
//
//	try
//	{
//		GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "GKOM", nullptr, nullptr);
//		if (window == nullptr)
//			throw exception("GLFW window not created");
//
//
//		glfwMakeContextCurrent(window);
//		glfwSetKeyCallback(window, key_callback);
//		glfwSetCursorPosCallback(window, mouse_callback);
//		glfwSetScrollCallback(window, scroll_callback);
//
//		glewExperimental = GL_TRUE;
//		if (glewInit() != GLEW_OK)
//			throw exception("GLEW Initialization failed");
//
//		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//
//		glEnable(GL_DEPTH_TEST);
//
//		glViewport(0, 0, WIDTH, HEIGHT);
//
//		ShaderProgram shaderProgram("gl_01_test.vert", "gl_01_test.frag");
//
//		GLfloat vertices[] = {
//			-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
//			0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
//			0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
//			0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
//			-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
//			-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
//
//			-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
//			0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
//			0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
//			0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
//			-0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
//			-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
//
//			-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
//			-0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
//			-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
//			-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
//			-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
//			-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
//
//			0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
//			0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
//			0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
//			0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
//			0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
//			0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
//
//			-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
//			0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
//			0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
//			0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
//			-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
//			-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
//
//			-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
//			0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
//			0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
//			0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
//			-0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
//			-0.5f, 0.5f, -0.5f, 0.0f, 1.0f
//		};
//
//		glm::vec3 cubePositions[] = {
//			glm::vec3(0.0f, 0.0f, 0.0f),
//			glm::vec3(2.0f, 5.0f, -15.0f),
//			glm::vec3(-1.5f, -2.2f, -2.5f),
//			glm::vec3(-3.8f, -2.0f, -12.3f),
//			glm::vec3(2.4f, -0.4f, -3.5f),
//			glm::vec3(-1.7f, 3.0f, -7.5f),
//			glm::vec3(1.3f, -2.0f, -2.5f),
//			glm::vec3(1.5f, 2.0f, -2.5f),
//			glm::vec3(1.5f, 0.2f, -1.5f),
//			glm::vec3(-1.3f, 1.0f, -1.5f)
//		};
//	
//
//		GLuint texture1;
//		GLuint texture2;
//
//		glGenTextures(1, &texture1);
//		glBindTexture(GL_TEXTURE_2D, texture1);
//
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//		// Set texture filtering
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//		int width, height;
//		unsigned char* image = SOIL_load_image("container.jpg", &width, &height, 0, SOIL_LOAD_RGB);
//
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
//		glGenerateMipmap(GL_TEXTURE_2D);
//		SOIL_free_image_data(image);
//		glBindTexture(GL_TEXTURE_2D, 0);
//
//		glGenTextures(1, &texture2);
//		glBindTexture(GL_TEXTURE_2D, texture2);
//
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//		// Set texture filtering
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//		image = SOIL_load_image("awesomeface.png", &width, &height, 0, SOIL_LOAD_RGB);
//
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
//		glGenerateMipmap(GL_TEXTURE_2D);
//		SOIL_free_image_data(image);
//		glBindTexture(GL_TEXTURE_2D, 0);
//
//		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//
//		GLuint VBO;
//		GLuint VAO;
//		//GLuint EBO;
//
//		glGenVertexArrays(1, &VAO);
//		glGenBuffers(1, &VBO);
//		//glGenBuffers(1, &EBO);
//
//		glBindVertexArray(VAO);
//		// 0. Copy our vertices array in a buffer for OpenGL to use
//		glBindBuffer(GL_ARRAY_BUFFER, VBO);
//		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//		// 1. Then set the vertex attributes pointers
//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
//		glEnableVertexAttribArray(0);
//
//		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
//		glEnableVertexAttribArray(2);
//
//
//		/////////////////////////////////////////////////////////////
//		///////////////////////MAIN LOOP///////////////////////////////
//
//		while (!glfwWindowShouldClose(window))
//		{
//			glfwPollEvents();
//
//			GLfloat currentFrame = glfwGetTime();
//			deltaTime = currentFrame - lastFrame;
//			lastFrame = currentFrame;
//
//			doMovement();
//
//			glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
//			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//			shaderProgram.use();
//
//			glActiveTexture(GL_TEXTURE0);
//			glBindTexture(GL_TEXTURE_2D, texture1);
//			glUniform1i(glGetUniformLocation(shaderProgram.getProgramID(), "ourTexture1"), 0);
//			glActiveTexture(GL_TEXTURE1);
//			glBindTexture(GL_TEXTURE_2D, texture2);
//			glUniform1i(glGetUniformLocation(shaderProgram.getProgramID(), "ourTexture2"), 1);
//
//			/*glm::mat4 model;
//			model = glm::rotate(model, (GLfloat)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));*/
//
//			glm::mat4 view;
//			view = camera.GetViewMatrix();
//			
//			glm::mat4 projection;
//			projection = glm::perspective(camera.getZoom(), (GLfloat)800/600, 0.1f, 100.0f);
//
//			GLint modelLoc = glGetUniformLocation(shaderProgram.getProgramID(), "model");
//			GLint viewLoc = glGetUniformLocation(shaderProgram.getProgramID(), "view");
//			GLint projLoc = glGetUniformLocation(shaderProgram.getProgramID(), "projection");
//
//			//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
//			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
//			// Note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
//			glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
//	
//			glBindVertexArray(VAO);
//
//			for (int i = 0; i < 10; i++)
//			{
//				glm::mat4 model;
//				model = glm::translate(model, cubePositions[i]);
//
//				if (i % 2 == 1)
//				{
//					model = glm::rotate(model, glm::radians(GLfloat(glfwGetTime()*50.0f)), glm::vec3(1.0f, 0.3f, 0.5f));
//				}
//				else
//				{
//					GLfloat angle = 20.0f * i;
//					model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
//				}
//
//				glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
//
//				glDrawArrays(GL_TRIANGLES, 0, 36);
//			}
//	
//			glBindVertexArray(0);
//
//			glfwSwapBuffers(window);
//		}
//
//		glDeleteVertexArrays(1, &VAO);
//		glDeleteBuffers(1, &VBO);
//		//glDeleteBuffers(1, &EBO);
//	}
//	catch (exception ex)
//	{
//		cout << ex.what() << endl;
//	}
//
//	glfwTerminate();
//
//	return 0;
//}