#pragma once
#include "glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

GLFWwindow* graphicInit();
void loadShaders(unsigned int*,unsigned int*,unsigned int*);
