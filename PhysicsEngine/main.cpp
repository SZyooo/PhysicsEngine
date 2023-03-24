#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<Tool.h>
#include"HelperFuncs.h"
#include "Cube.h"
#include"ParticleWrapper.h"
#include"ParticleAnchoredSpring.h"
#include"ParticleGravity.h"
#include"ParticleBuoyancy.h"
#include"RigidBodyWrapper.h"
#include"Debug.h"
#include"AnchordBungee.h"
#include"Gravity.h"
#include "Geometry.h"
#include "Point.h"
#pragma comment(lib,"mylib.lib")

#define WIN_WID 1000
#define WIN_HEI 800
int main() {
	//init 
	auto initGL = [](int wid, int hei)->GLFWwindow* {
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
	auto window = initGL(WIN_WID, WIN_HEI);

	Camera camera(3, 5, WIN_WID, WIN_HEI, 0, -90, { 0,0,5 });
	CameraControllor cc;
	cc.SetUpCamera(&camera);
	cc.SetUpCentre(WIN_WID / 2, WIN_HEI / 2);
	glfwSetKeyCallback(window, CameraControllor::KeyInputCallback);
	glfwSetCursorPosCallback(window, CameraControllor::MouseMoveCallback);

	GLuint defaultVao;
	glCreateVertexArrays(1, &defaultVao);

	glm::mat4 model = glm::scale(glm::mat4(1), vec3(0.5));
	YoungEngine::ParticleWrapper cube(new YoungEngine::Geometry::Cube(model, 1, 1, 1));
	YoungEngine::RigidBodyWrapper cubeBody(new YoungEngine::Geometry::Cube(model, 1, 1, 1));
	cube.setMass(10);
	cube.setDamping(0.9);
	cubeBody.setAngularDamping(0.9);
	float _1_12 = 1.f / 12;
	float cubeBodyMass = 100;
	float dxdx = 0.25, dydy = 0.25, dzdz = 0.25;
	glm::mat3 inertiaTensor;
	inertiaTensor[0] = { _1_12 * cubeBodyMass * (dydy + dzdz),0,0 };
	inertiaTensor[1] = { 0,_1_12 * cubeBodyMass * (dxdx + dzdz),0 };
	inertiaTensor[2] = { 0,0,_1_12 * cubeBodyMass * (dxdx + dydy) };
	cubeBody.setMass(cubeBodyMass);
	cubeBody.setInertiaTensor(inertiaTensor);
	cubeBody.setLinearDamping(0.9);
	cubeBody.setOrientation({ 0,1,0 }, 0);
	cubeBody.move({2, 0, 0});
	//cubeBody.setRotation({ 1,1,1 });

	GLuint drawcube = create_program("default_vs.glsl", "default_fs.glsl");
	GLuint cubeBuffer = YoungEngine::moveVertexToBuffer(cube.getVertices());
	GLuint cubeVao = YoungEngine::generateVAOForCubeShader(cubeBuffer);
	glBindVertexArray(cubeVao);
	glUseProgram(drawcube);
	glUniformMatrix4fv(glGetUniformLocation(drawcube, "project"), 1, GL_FALSE, glm::value_ptr(camera.GetProjectMat()));
	glUniformMatrix4fv(glGetUniformLocation(drawcube, "proj_inv"), 1, GL_FALSE, glm::value_ptr(glm::inverse(camera.GetProjectMat())));
	glUniformMatrix4fv(glGetUniformLocation(drawcube, "model"), 1, GL_FALSE, glm::value_ptr(cube.getTransform()));
	

	YoungEngine::ParticleAnchoredSpring anchoredSpring({ 0,0,0 }, 100, 0.1);
	YoungEngine::ParticleGravity gravity({ 0,-10,0 });
	YoungEngine::ParticleBuoyancy buoyancy(0.5, 0.5 * 0.5 * 0.5, 0, 1000, {0,1,0});
	YoungEngine::AnchoredBungee bungee({ 0,0,0 }, { 0.5,0.5,0.5 }, 0.2, 100);
	YoungEngine::Gravity rigidGravity({ 0,-10,0 });

	GLuint drawSpring = create_program("line_vs.glsl", "line_fs.glsl");
	glm::vec3 anchorPos = YoungEngine::convertVector3ToGLMVec3(anchoredSpring.getAnchorPosition());
	glUseProgram(drawSpring);
	glUniform3fv(glGetUniformLocation(drawSpring, "pos[0]"), 1, glm::value_ptr(anchorPos));
	glUniformMatrix4fv(glGetUniformLocation(drawSpring, "proj"), 1, GL_FALSE, glm::value_ptr(camera.GetProjectMat()));
	
	cube.setPosition({ 0, -10, 0 });

	double time = glfwGetTime();
	glEnable(GL_DEPTH_TEST);

	//Test Barycentric
	YoungEngine::Point a(1, 1, -2);
	YoungEngine::Point b(-1, 0, 1);
	YoungEngine::Point c(4, 1, -5);
	YoungEngine::Point p(8,8,-16);
	float u, v, w;
	YoungEngine::Barycentric(a, b, c, p, u, v, w);
	YoungEngine::PrintFloat(u);
	YoungEngine::PrintFloat(v);
	YoungEngine::PrintFloat(w);
	YoungEngine::PrintVector(u * a + v * b + w * c);
	YoungEngine::BarycentricCramerRule(a, b, c, p, u, v, w);
	YoungEngine::PrintFloat(u);
	YoungEngine::PrintFloat(v);
	YoungEngine::PrintFloat(w);
	YoungEngine::PrintVector(u * a + v * b + w * c);

	while (glfwWindowShouldClose(window) == false)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		double t = glfwGetTime();
		double dt = t - time;
		cc.SetUpDeltaTime(dt);
		time = t;
		float slowedDt = dt * 0.01;
		//anchoredSpring.updateForce(cube, dt);
		//buoyancy.updateForce(cube, dt);
		//gravity.updateForce(cube, dt);
		//cube.integrate(dt);
		//YoungEngine::PrintVector(cube.getVelocity(),"velocity");
		rigidGravity.updateForce(&cubeBody, dt);
		bungee.updateForce(&cubeBody, dt);
		//YoungEngine::PrintVector(cubeBody.getRotation(), "rotation");
		cubeBody.integrate(dt);
		
		glUseProgram(drawcube);
		glBindVertexArray(cubeVao);
		glUniformMatrix4fv(glGetUniformLocation(drawcube, "view"), 1, GL_FALSE, glm::value_ptr(camera.GetViewMat()));
		glUniformMatrix4fv(glGetUniformLocation(drawcube, "model"), 1, GL_FALSE, glm::value_ptr(cubeBody.getTransform()));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, &cubeBody.trianglatedIndices()[0]);
		glUseProgram(drawSpring);
		glBindVertexArray(defaultVao);
		YoungEngine::Vector3 cnn = cubeBody.transformLocalPointToWorldSpace({ 0.5,0.5,0.5 });
		glm::vec3 particle_pos = YoungEngine::convertVector3ToGLMVec3(cnn);
		glUniform3fv(glGetUniformLocation(drawSpring, "pos[1]"), 1, glm::value_ptr(particle_pos));
		glUniformMatrix4fv(glGetUniformLocation(drawSpring, "view"), 1, GL_FALSE, glm::value_ptr(camera.GetViewMat()));
		glLineWidth(2);
		glDrawArrays(GL_LINES, 0, 2);
		YoungEngine::drawBasis({ 0,0,0 }, camera.GetViewMat(), camera.GetProjectMat());
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	return 0;
}