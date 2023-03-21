#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<Tool.h>
#include"HelperFuncs.h"
#include "Cube.h"
#include"ParticleWrapper.h"
#pragma comment(lib,"mylib.lib")

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
	
	Camera camera(1, 1, WIN_WID, WIN_HEI);
	CameraControllor cc;
	cc.SetUpCamera(&camera);
	cc.SetUpCentre(WIN_WID / 2, WIN_HEI / 2);
	glfwSetKeyCallback(window, CameraControllor::KeyInputCallback);
	glfwSetCursorPosCallback(window, CameraControllor::MouseMoveCallback);


	YoungEngine::ParticleWrapper cube(new YoungEngine::Cube(glm::translate(glm::scale(glm::mat4(1), glm::vec3(0.2)), glm::vec3(0, 0, -5)), 1, 1, 1));
	GLuint drawcube = create_program("cube_vs.glsl", "cube_fs.glsl",0,0,"cube_gs.glsl");
	GLuint cubeBuffer = YoungEngine::moveVertexToBuffer(cube.getVertices());
	GLuint cubeVao = YoungEngine::generateVAOForCubeShader(cubeBuffer);
	glBindVertexArray(cubeVao);
	glUseProgram(drawcube);
	glUniformMatrix4fv(glGetUniformLocation(drawcube, "project"), 1, GL_FALSE, glm::value_ptr(camera.GetProjectMat()));
	glUniformMatrix4fv(glGetUniformLocation(drawcube, "proj_inv"), 1, GL_FALSE, glm::value_ptr(glm::inverse(camera.GetProjectMat())));
	glUniformMatrix4fv(glGetUniformLocation(drawcube, "model"), 1, GL_FALSE, glm::value_ptr(cube.getTransform()));

	double time = glfwGetTime();
	glEnable(GL_DEPTH_TEST);
	while (glfwWindowShouldClose(window) == false)
	{
		double t = glfwGetTime();
		double dt = t - time;
		cc.SetUpDeltaTime(dt);
		time = t;
		glUniformMatrix4fv(glGetUniformLocation(drawcube, "view"), 1, GL_FALSE, glm::value_ptr(camera.GetViewMat()));
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, &cube.trianglatedIndices()[0]);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	return 0;
}