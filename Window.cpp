#include "Versa.h"


void WindowManager::BackgroundColor(float red, float green, float blue, float alpha)
{
	glClearColor(red, green, blue, alpha);
}

void Window::CreateWindow(const char* title, int width, int height)
{
	if (!glfwInit())
	{
		printf("Working not Fine/n");
		glfwTerminate();
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* mainWindow = glfwCreateWindow(width,height, "Sandbox", NULL, NULL);
	if (!mainWindow)
	{
		printf("GLFW WINDOW FAILD");
		glfwTerminate();
	}

	int BufferWidth, BufferHeight;
	glfwGetFramebufferSize(mainWindow, &BufferWidth, &BufferHeight);

	glfwMakeContextCurrent(mainWindow);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		printf("GLEW DIDNT WORK");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
	}

	glViewport(0, 0, BufferWidth, BufferHeight);

	WindowManager WindowManager;
	WindowManager.Start();


	while (!glfwWindowShouldClose(mainWindow))
	{
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT);
		WindowManager.Update();

		glfwSwapBuffers(mainWindow);
	}
}
