#include "graphic.h"
void framebuffer_size_callback(GLFWwindow*, int, int);

void loadShaders (unsigned int * shaderProg, unsigned int * vertexShader, unsigned int * fragmentShader){
    std::ifstream vs("/home/j/AquaFox/Shaders/vertshader.vert");
    std::stringstream buffer;
    buffer << vs.rdbuf();
    std::string vertexShaderStr = buffer.str();
    const GLchar * vertexShaderSrc = vertexShaderStr.c_str();
    int vertexShaderSize = vertexShaderStr.length();

    std::ifstream fs("/home/j/AquaFox/Shaders/frag.frag");
    buffer << vs.rdbuf();
    std::string fragShaderStr = buffer.str();
    const GLchar * fragShaderSrc = fragShaderStr.c_str();
    int fragmentShaderSize = fragShaderStr.size();

    *vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(*vertexShader, 1, &vertexShaderSrc, &vertexShaderSize);
    glCompileShader(*vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(*vertexShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(*vertexShader, 512, NULL, infoLog);
        std::cout << "Error compiling vertex shader: " << infoLog << std::endl;
    }

    *fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(*fragmentShader, 1, &fragShaderSrc, &fragmentShaderSize);
    glCompileShader(*fragmentShader);

    glGetShaderiv(*fragmentShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(*fragmentShader, 512, NULL, infoLog);
        std::cout << "Error compiling frag shader: " << infoLog << std::endl;
    }

    glAttachShader(*shaderProg, *vertexShader);
    glAttachShader(*shaderProg, *fragmentShader);
    glLinkProgram(*shaderProg);
}

GLFWwindow* graphicInit() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "AquaFox", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return NULL;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return NULL;
	}

	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	return window;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}
