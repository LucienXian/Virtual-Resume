#include "Common.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include"model.h"
#include "camera.h"
//#include "Resumes.h"
#include "resume_creator.h"
#include "TextRender.h"
#include <iostream>


// settings of window size


std::vector<glm::vec3> vec_resume_pos;
std::vector<glm::vec3> vec_resume_size;

//把简历集合定为全局变量
//Resume *resume;

Camera camera(glm::vec3(-23.0f, 7.0f, 0.0f));
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void load_texture(GLuint &texture, const std::string& path);
void add_texture(std::vector<GLuint>& v);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
unsigned int loadCubemap(std::vector<std::string> faces);
float* generound(int n); 
void init_resume_para();


int load_resume_id = 0;
bool firstMouse = true;
GLfloat yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
GLfloat pitch = 0.0f;
GLfloat lastX = 800.0f / 2.0;
GLfloat lastY = 600.0 / 2.0;
GLfloat fov = 45.0f;

// timing
GLfloat deltaTime = 0.0f;	// time between current frame and last frame
GLfloat lastFrame = 0.0f;

void InitWindow()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif
	
}

int main()
{
	InitWindow();

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, window_name, NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// tell GLFW to capture our mouse
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST);//configure opengl state;
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Shader roundShader("Shader/vertex.vs", "Shader/fragment.fs");
	Shader skyboxShader("Shader/skybox.vs", "Shader/skybox.fs");
	Shader modelShader("Shader/3Dmodel.vs", "Shader/3Dmodel.fs");


	int number_round = 80;//把圆柱划分的份数
	int slice = number_round / 8;//份数除以8份简历
	GLfloat *vertices = generound(number_round);
	unsigned int VBO[8], VAO[8];
	unsigned int EBO;

	for (int i = 0; i < 8; i++) {
		glGenVertexArrays(1, &VAO[i]);
		glGenBuffers(1, &VBO[i]);

		glBindVertexArray(VAO[i]);
		int size = sizeof(float) * 30 * number_round;
		glBindBuffer(GL_ARRAY_BUFFER, VBO[i]);
		glBufferData(GL_ARRAY_BUFFER, size / 8, vertices + i * 30 * slice, GL_DYNAMIC_DRAW);
		// 复制到一个索引缓冲
		/*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/

		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		// texture coord attribute
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
	}
	std::vector<GLuint> v_texture;
	add_texture(v_texture);
	float skyboxVertices[] = {
		// positions          
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f,  1.0f
	};


	//skybox VAO
	unsigned int skyboxVAO, skyboxVBO;
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	std::vector<std::string> faces{
		"skybox/ame_nebula/purplenebula_rt.tga",
		"skybox/ame_nebula/purplenebula_lf.tga",
		"skybox/ame_nebula/purplenebula_up.tga",
		"skybox/ame_nebula/purplenebula_dn.tga",
		"skybox/ame_nebula/purplenebula_bk.tga",
		"skybox/ame_nebula/purplenebula_ft.tga"
	};
	unsigned int cubemapTexture = loadCubemap(faces);//load skybox


													 // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
													 // -------------------------------------------------------------------------------------------
	roundShader.use();
	roundShader.setInt("resume1", 0);

	//skybox configuration
	skyboxShader.use();
	skyboxShader.setInt("skybox", 0);

	init_resume_para();


	//给类分配资源空间
	//resume = new Resume();
	Resume_creator resume_creator(vec_resume_pos, vec_resume_size, vec_resume_pos.size());
	TextRender *t = new TextRender();
	while (!glfwWindowShouldClose(window))
	{
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);

		// render
		// ------
		glClearColor(0, 0, 0, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!

		glm::mat4 view;
		glm::mat4 projection;
		projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		view = camera.GetViewMatrix();

		//绘制模型
		{
			modelShader.use();
			modelShader.setMat4("projection", projection);
			modelShader.setMat4("view", view);
			resume_creator.setmat4(view, projection);
			resume_creator.show_resume(load_resume_id, modelShader);
		}
		//分别画八张简历缩影，形成圆柱
		roundShader.use();
		roundShader.setMat4("projection", projection); // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
		roundShader.setMat4("view", view);
		for (unsigned int i = 0; i <8; i++)//v_texture.size()
		{
			glBindVertexArray(VAO[i]);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, v_texture[i]);
			// calculate the model matrix for each object and pass it to shader before drawing
			glm::mat4 model;

			model = glm::rotate(model, (float)(0.1*glfwGetTime()), glm::vec3(0, 1.0f, 0));
			model = glm::scale(model, glm::vec3(0.8f, 0.8f, 0.8f));
			roundShader.setMat4("model", model);
			// camera/view transformation
			glm::mat4 view = camera.GetViewMatrix();
			roundShader.setMat4("view", view);
			glDrawArrays(GL_TRIANGLES, 0, 6 * number_round / 8 - 6);

		}

		// draw skybox as last
		glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
		skyboxShader.use();
		view = glm::mat4(glm::mat3(camera.GetViewMatrix())); // remove translation from the view matrix
		skyboxShader.setMat4("view", view);
		skyboxShader.setMat4("projection", projection);
		// skybox cube
		glBindVertexArray(skyboxVAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glDepthFunc(GL_LESS); // set depth function back to default
							  //glDrawArrays(GL_TRIANGLES, 0, 6);


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	for (int i = 0; i < 8; i++)
	{
		glDeleteBuffers(1, &VBO[i]);
		glDeleteVertexArrays(1, &VAO[i]);
	}
	glDeleteVertexArrays(1, &skyboxVAO);
	glDeleteBuffers(1, &skyboxVBO);
	//delete(resume);
	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

	

void add_texture(std::vector<GLuint>& v)
{
	std::string path = "resume/";
	for (int i = 0; i < 8; i++)
	{
		
		GLuint texture;
		path = path + std::to_string(i+1) + ".jpg";
		std::cout << path << std::endl;
		load_texture(texture, path);
		v.push_back(texture);
		path = path.substr(0, 7);
	}
}

void load_texture(GLuint &texture, const std::string& path)
{
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST);

	int width, height, nrChannels;
	unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	//float cameraSpeed = 2.5 * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)
		load_resume_id = 0;
		//resume->ChangeModel(0);
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		load_resume_id = 1;
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		load_resume_id = 2;
		//resume->ChangeModel(1);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}

unsigned int loadCubemap(std::vector<std::string> faces)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;
}
//生成圆柱简历所需要的坐标
float* generound(int n)
{
	float *vertice = (float*)malloc(sizeof(float) * 30 * n);
	float z = 5.0;
	float x = 5.0;
	float y = 1.2;
	double u = 1.0 * 2 * PI / n;
	int slice = n / 8;
	float rx[80], rz[80], tx[80];
	for (int i = 0; i < n; i++)
	{
		rx[i] = x*cos(u*i);
		rz[i] = z*sin(u*i);
		tx[i] = 1 - (i%slice)*1.0 / (slice - 1);
		//cout << "rx: " << rx[i] << "  rz:  " << rz[i] << endl;
	}
	for (int i = 0; i < n; i++)
	{
		int m = 30 * i;
		int j = (i + 1) % n;
		vertice[m] = rx[i];
		vertice[m + 1] = -y;
		vertice[m + 2] = rz[i];
		vertice[m + 3] = tx[i];
		vertice[m + 4] = 0;

		vertice[m + 5] = rx[j];
		vertice[m + 6] = -y;
		vertice[m + 7] = rz[j];
		vertice[m + 8] = tx[j];
		vertice[m + 9] = 0;

		vertice[m + 10] = rx[j];
		vertice[m + 11] = y;
		vertice[m + 12] = rz[j];
		vertice[m + 13] = tx[j];
		vertice[m + 14] = 1;

		vertice[m + 15] = rx[j];
		vertice[m + 16] = y;
		vertice[m + 17] = rz[j];
		vertice[m + 18] = tx[j];
		vertice[m + 19] = 1;

		vertice[m + 20] = rx[i];
		vertice[m + 21] = y;
		vertice[m + 22] = rz[i];
		vertice[m + 23] = tx[i];
		vertice[m + 24] = 1;

		vertice[m + 25] = rx[i];
		vertice[m + 26] = -y;
		vertice[m + 27] = rz[i];
		vertice[m + 28] = tx[i];
		vertice[m + 29] = 0;
	}
	/*for (int i = 0; i < 30; i++)
	cout << vertice[i] << ",";*/
	return vertice;
}

void init_resume_para() {
	vec_resume_pos.push_back(glm::vec3(0.0f, 15.0f, -8.0f));//infomation
	vec_resume_pos.push_back(glm::vec3(0.0f, 12.0f, -5.0f));//skill
	vec_resume_pos.push_back(glm::vec3(0.0f, 8.2f, -1.7f));//job intention

	vec_resume_size.push_back(glm::vec3(0.12f, 0.12f, 0.12f));
	vec_resume_size.push_back(glm::vec3(0.05f, 0.05f, 0.05f));
	vec_resume_size.push_back(glm::vec3(0.01f, 0.01f, 0.01f));
}