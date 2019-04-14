#version 330 core
out vec4 FragColor;

in vec4 vertexColor; // the input variable from the vertex shader (same name and same type)

void main()
{
    FragColor = vec4(0.3f,0.1f,0.0f,1.0f);
}
