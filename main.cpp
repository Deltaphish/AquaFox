
#include "graphic.h"
#include "Input.h"
#include "Vertex.h"
#include "OBJ_Loader.h"

const float vertices[] = {
-0.5f,-0.5,-0.0f,
0.5f,-0.5f,-0.0f,
-0.5f,0.5f,0.0f,
0.5f,0.5f,0.0f
};


int main() {

    unsigned int vertexShader;
    unsigned int fragmentShader;

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
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    /*
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*6, indices, GL_STATIC_DRAW);
*/
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
	glEnableVertexAttribArray(0);

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    loadShaders(&shaderProgram, &vertexShader, &fragmentShader);
	
    glUseProgram(shaderProgram);
	while (!glfwWindowShouldClose(window)) {
		processInput(window);

        //Render
        glUseProgram(shaderProgram);
		glClear(GL_COLOR_BUFFER_BIT);
		glBindVertexArray(VAO);
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glDrawArrays(GL_TRIANGLES,0,3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glfwTerminate();
	
	return 0;
}

