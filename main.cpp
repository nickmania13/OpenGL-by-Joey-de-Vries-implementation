#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>


void framebuffer_size_callback(GLFWwindow* window, int width, int height); 
void proccessInput(GLFWwindow* window);


const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"out vec3 ourColor;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(aPos, 1.0);\n"
"ourColor = aColor;\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 ourColor;\n"
"void main()\n"
"{\n"
"FragColor = vec4(ourColor, 1.0);\n"
"}\0";




int main()
{
	// Initialize GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a window object
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Make the context of the window the main context on the current thread
	glfwMakeContextCurrent(window);

	// iNITIALIZE GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// Give the viewport the same size as the window
	glViewport(0, 0, 800, 600);

	// Resize the viewport when the window is resized
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Create the element buffer object and copy the indices array in a buffer for OpenGL to use
	float vertices[] = {
		// positions      |     colors          
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
		 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f  // top

	};
	
	// Generate a buffer and bind it to the GL_ARRAY_BUFFER target
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Create a shader object and compile the vertex shader
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); // Attach the shader source code to the shader object 
	glCompileShader(vertexShader);                              //and compile the shader

	// Check for shader compile errors
	int successVertexShader;
	char infoLogVertex[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &successVertexShader);
	if (!successVertexShader)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLogVertex);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLogVertex << std::endl;
	}

	// Compiling the fragment shader
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// Check for shader compile errors
	int successFragmentShader;
	char infoLogFragment[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &successFragmentShader);
	if (!successFragmentShader)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLogFragment);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLogFragment << std::endl;
	}

	// Create a shader program and link the vertex and fragment shaders to it
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// Check for linking errors
	int successShaderProgram;
	char infoLogShaderProgram[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &successShaderProgram);
	if (!successShaderProgram)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLogShaderProgram);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLogShaderProgram << std::endl;
	}

	// Activate the shader program object
	glUseProgram(shaderProgram);
	// Delete the shader objects once we've linked them into the shader program object
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Telling OpenGL how to interpret the vertex data
	
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	
	// Define the indices for the triangle
	unsigned int indices[] = {
	0, 1, 2,  // first tringle
	};
	
	// Generate the EBO object
	unsigned int EBO;
	glGenBuffers(1, &EBO);

	// Generate a vertex array object and bind it
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	// Copy the vertices array in a vertex buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// Copy the index array in an element buffer for OpenGL to use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	
	

	


	// Render loop
	while(!glfwWindowShouldClose(window))
	{
		// input
		proccessInput(window);

		// rendering commands
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// activate the shader
		glUseProgram(shaderProgram);
		

		// Using uniform to change the color of the rectangle
		float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		
		glUniform4f(vertexColorLocation, 0.5f, greenValue, 0.0f, 1.0f);  // Set the color of the rectangle to a changing green value

		// Draw the rectangle
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 3,GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Wireframe mode
		


		// check and call events and swap the buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	glfwTerminate();
	return 0;

}





// So that the viewport is resized when the window is resized
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

// Handle input
void proccessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

}


// Debugging
void APIENTRY glDebugOutput(GLenum source,
	GLenum type,
	unsigned int id,
	GLenum severity,
	GLsizei length,
	const char* message,
	const void* userParam)
{
	// ignore non-significant error/warning codes
	if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

	std::cout << "---------------" << std::endl;
	std::cout << "Debug message (" << id << "): " << message << std::endl;

	switch (source)
	{
	case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
	case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
	case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
	} std::cout << std::endl;

	switch (type)
	{
	case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break;
	case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
	case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
	case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
	case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
	case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
	case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
	} std::cout << std::endl;

	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
	case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
	case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
	case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
	} std::cout << std::endl;
	std::cout << std::endl;
}
