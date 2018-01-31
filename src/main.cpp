#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cmath>
#include <iostream>

int compile_shader(int shader_type, const char* filename);
void make_rectangle(unsigned int VAO, unsigned int VBO, unsigned int EBO);

const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;
float SCR_RATIO = (float)SCR_WIDTH / (float)SCR_HEIGHT;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	SCR_RATIO = (float)width / (float)height;
    glViewport(0, 0, width, height);
}

int main()
{
	// Initialise window
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Mandelbrot", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// Compile Shaders
	int vertexShader = compile_shader(GL_VERTEX_SHADER, "vertShader.glsl");
	int fragmentShader = compile_shader(GL_FRAGMENT_SHADER, "fragShader.glsl");

	// Link Shaders
	int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// Link Errors?
	int success;
	char infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	make_rectangle(VAO, VBO, EBO);

	float startx = -0.5;
	float starty = 0.0;
	float finishx = -0.66445;
	float finishy = 0.4536;
	float rangex = (finishx - startx);
	float rangey = (finishy - starty);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		float timeValue = glfwGetTime();

		// Rougly how long it takes before precision failure
		if (timeValue >= 18)
		{
			break;
		}

		float zoom = pow(2.0f, 1-timeValue);
		float pan = 1 - exp(-timeValue);

		glUseProgram(shaderProgram);

		// Move to location
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "center");
		glUniform2f(vertexColorLocation, 
			startx + pan * rangex, 
			starty + pan * rangey);

		// Zoom in
		vertexColorLocation = glGetUniformLocation(shaderProgram, "size");
		glUniform2f(vertexColorLocation, zoom * SCR_RATIO, zoom);

		// Draw Rectangle
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return 0;
}