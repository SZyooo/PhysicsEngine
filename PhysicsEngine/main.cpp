#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<Tool.h>
#include"HelperFuncs.h"
#include "Cube.h"
#define WIN_WID 800
#define WIN_HEI 600
int main() {
	//init 
	auto initGL = [](int wid,int hei)->GLFWwindow* {
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		GLFWwindow* window = glfwCreateWindow(wid, hei, "opengl window", NULL, NULL);
		glfwMakeContextCurrent(window);
		if (glewInit() != GLEW_OK) {
			return nullptr;
		}
		return window;
	};
	auto window = initGL(WIN_WID,WIN_HEI);
	
	Camera camera(0.1,0.1,WIN_WID,WIN_HEI),

	YoungEngine::Cube cube(glm::mat4(1), 1, 1, 1);
	GLuint drawcube = create_program("cube_vs.glsl", "cube_fs.glsl");
	GLuint cubeBuffer = YoungEngine::moveVertexToBuffer(cube.getVertices());
	GLuint cubeVao = YoungEngine::generateVAOForCubeShader(cubeBuffer);
	glBindVertexArray(cubeVao);


	return 0;
}