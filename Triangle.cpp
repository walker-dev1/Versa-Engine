#include "Versa.h"


using namespace std;

static const char* vertexShadersource = "                             \n\
#version 330                                               \n\
                                                           \n\
layout (location = 0) in vec3 pos;                         \n\
				                   \n\
void main()                                                \n\
{														   \n\
	gl_Position = vec4(pos, 1.0); \n\
                                                           \n\
}                                                          \n\
";

static const char* fragmentShadersource = "                             \n\
#version 330                                               \n\
                                                           \n\
out vec4 color;                                            \n\                                  \n\
                                                           \n\
void main()                                                \n\
{														   \n\
	 color = vec4(1.0,0.5, 0.2,1.0);              \n\
                                                           \n\
}                                                          \n\
";


void Triangle::InitTriangle()
{
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShadersource, NULL);
	glCompileShader(vertexShader);


	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		cout << "Vertex shader Compile Error" << endl;
	}

	int fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &fragmentShadersource, NULL);
	glCompileShader(fragShader);



	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
		cout << "fragment shader Compile Error" << endl;
	}

	int Program = glCreateProgram();
	glAttachShader(Program, vertexShader);
	glAttachShader(Program, fragShader);
	glLinkProgram(Program);
	glGetProgramiv(Program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(Program, 512, NULL, infoLog);
		cout << "linking Error" << endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragShader);

	float verticices[] = {

		-0.5f,-0.5f,0.0f,
		0.5f,-0.5f,0.0f,
		0.0f,0.5f,0.0f
	};

	unsigned int indecies[] = {
	0, 1, 3,
	1, 2, 3
	};

	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);


	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticices), verticices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glUseProgram(Program);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void Triangle::DrawTriangle()
{


	glDrawArrays(GL_TRIANGLES, 0, 3);
}
