
#include "graphic.h"
#include "Input.h"
#include "Vertex.h"
#include "OBJ_Loader.h"
#include <string>

const char * vertexShaderSrc = "#version 330 core \n \
layout(location = 0) in vec3 aPos;\n \
void main() { \
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0); \
}";

const GLchar * fragShaderSrc = "#version 330 core \n\
\
uniform float nodes[8];\
int nNodes = 4;\
layout(origin_upper_left) in vec4 gl_FragCoord;\
out vec4 FragColor; \
in vec2 vpos; \
\
float dist(in vec2 a, in vec2 b) {\
	return(abs(length(b-a)));\
}\
\
void main()\
{\
	float fac = 0.5;\
	FragColor = vec4(0.0f,0.0f,0.0f,1.0f);\
	for(int i = 0; i != nNodes;i++){\
	vec2 n = vec2(nodes[i*2],nodes[i*2+1]);\
	if(dist(gl_FragCoord.yx/vec2(600,800),n) <= 1){\
		switch(i){\
			case 0: FragColor.r = pow(1 - pow(dist(gl_FragCoord.yx/vec2(600,800), n), 2), 2)*fac; \
					break;\
			case 1: FragColor.g = pow(1 - pow(dist(gl_FragCoord.yx/vec2(600,800), n), 2), 2)*fac; \
				break;\
			case 2: FragColor.b = pow(1 - pow(dist(gl_FragCoord.yx/vec2(600,800), n), 2), 2)*fac; \
				break;\
			case 3: FragColor.a = pow(1 - pow(dist(gl_FragCoord.yx/vec2(600,800), n), 2), 2)*fac; \
				break;\
		}\
	}}\
}\n";

int fragShaderLen = 562;

int main() {

	GLFWwindow* window = graphicInit();
	if (!window) {
		return -1;
	}

	// Load 3d model
	objl::Loader loader = objl::Loader();

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*3*4, vertices, GL_STATIC_DRAW);

	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*6, indices, GL_STATIC_DRAW);


	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSrc, NULL);
	glCompileShader(vertexShader);

	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "Error compiling vertex shader: " << infoLog << std::endl;
	}


	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragShaderSrc, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "Error compiling frag shader: " << infoLog << std::endl;
	}

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	GLfloat n[8] = { 2,3,-2,1,-4,-1,3,-2 };

	int nodesLoc = glGetUniformLocation(shaderProgram, "nodes");
	glUniform1fv(nodesLoc, 8, n);
	

	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		//Render

		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glfwTerminate();
	
	return 0;
}

