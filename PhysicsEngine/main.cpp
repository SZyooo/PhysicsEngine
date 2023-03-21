#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<Tool.h>
#include"HelperFuncs.h"
#include "Cube.h"
#include"ParticleWrapper.h"
#include"ParticleAnchoredSpring.h"
#include"ParticleGravity.h"
#include"Debug.h"
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
	
	Camera camera(2, 2, WIN_WID, WIN_HEI, 0, -90, {0,0,10});
	CameraControllor cc;
	cc.SetUpCamera(&camera);
	cc.SetUpCentre(WIN_WID / 2, WIN_HEI / 2);
	glfwSetKeyCallback(window, CameraControllor::KeyInputCallback);
	glfwSetCursorPosCallback(window, CameraControllor::MouseMoveCallback);

	GLuint defaultVao;
	glCreateVertexArrays(1, &defaultVao);

	glm::mat4 model = glm::scale(glm::mat4(1), vec3(0.1));
	YoungEngine::ParticleWrapper cube(new YoungEngine::Cube(model, 1, 1, 1));
	cube.setMass(10);
	cube.setDamping(0.9);

	GLuint drawcube = create_program("cube_vs.glsl", "cube_fs.glsl",0,0,"cube_gs.glsl");
	GLuint cubeBuffer = YoungEngine::moveVertexToBuffer(cube.getVertices());
	GLuint cubeVao = YoungEngine::generateVAOForCubeShader(cubeBuffer);
	glBindVertexArray(cubeVao);
	glUseProgram(drawcube);
	glUniformMatrix4fv(glGetUniformLocation(drawcube, "project"), 1, GL_FALSE, glm::value_ptr(camera.GetProjectMat()));
	glUniformMatrix4fv(glGetUniformLocation(drawcube, "proj_inv"), 1, GL_FALSE, glm::value_ptr(glm::inverse(camera.GetProjectMat())));
	glUniformMatrix4fv(glGetUniformLocation(drawcube, "model"), 1, GL_FALSE, glm::value_ptr(cube.getTransform()));
	

	YoungEngine::ParticleAnchoredSpring anchoredSpring({ 0,0,0 }, 100, 0.1);
	YoungEngine::ParticleGravity gravity({ 0,-10,0 });

	GLuint drawSpring = create_program("line_vs.glsl", "line_fs.glsl");
	glm::vec3 anchorPos = YoungEngine::convertVector3ToGLMVec3(anchoredSpring.getAnchorPosition());
	glUseProgram(drawSpring);
	glUniform3fv(glGetUniformLocation(drawSpring, "pos[0]"), 1, glm::value_ptr(anchorPos));
	glUniformMatrix4fv(glGetUniformLocation(drawSpring, "proj"), 1, GL_FALSE, glm::value_ptr(camera.GetProjectMat()));
	
	double time = glfwGetTime();
	glEnable(GL_DEPTH_TEST);
	while (glfwWindowShouldClose(window) == false)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		double t = glfwGetTime();
		double dt = t - time;
		cc.SetUpDeltaTime(dt);
		time = t;
		anchoredSpring.updateForce(cube, dt);
		gravity.updateForce(cube, dt);
		cube.integrate(dt);
		YoungEngine::PrintVector(cube.getVelocity(),"velocity");
		glUseProgram(drawcube);
		glBindVertexArray(cubeVao);
		glUniformMatrix4fv(glGetUniformLocation(drawcube, "view"), 1, GL_FALSE, glm::value_ptr(camera.GetViewMat()));
		glUniformMatrix4fv(glGetUniformLocation(drawcube, "model"), 1, GL_FALSE, glm::value_ptr(cube.getTransform()));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, &cube.trianglatedIndices()[0]);
		glUseProgram(drawSpring);
		glBindVertexArray(defaultVao);
		glm::vec3 particle_pos = YoungEngine::convertVector3ToGLMVec3(cube.getPosition());
		glUniform3fv(glGetUniformLocation(drawSpring, "pos[1]"), 1, glm::value_ptr(particle_pos));
		glUniformMatrix4fv(glGetUniformLocation(drawSpring, "view"), 1, GL_FALSE, glm::value_ptr(camera.GetViewMat()));
		glDrawArrays(GL_LINES, 0, 2);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	return 0;
}