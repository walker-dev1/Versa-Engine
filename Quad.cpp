#include "Versa.h"


using namespace std;

static const char* vShader = "                             \n\
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

static const char* fShader = "                             \n\
#version 330                                               \n\
                                                           \n\
out vec4 colour;                                           \n\
                                                           \n\
void main()                                                \n\
{														   \n\
	 colour = vec4(1.0,0.5, 0.2,1.0);                     \n\
                                                           \n\
}                                                          \n\
";

Quad ShapeManager;

void Quad::InitQuad()
{
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vShader, NULL);
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
	glShaderSource(fragShader, 1, &fShader, NULL);
	glCompileShader(fragShader);



	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
		cout << "fragment shader Compile Error" << endl;
	}

	ShapeManager.Program = glCreateProgram();
	glAttachShader(ShapeManager.Program, vertexShader);
	glAttachShader(ShapeManager.Program, fragShader);
	glLinkProgram(ShapeManager.Program);
	glGetProgramiv(ShapeManager.Program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(ShapeManager.Program, 512, NULL, infoLog);
		cout << "linking Error" << endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragShader);

	float verticices[] = {
		 0.5f,  0.5f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};
	unsigned int indecies[] = {  //
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	
	glGenVertexArrays(1, &ShapeManager.VAO);
	glGenBuffers(1, &ShapeManager.VBO);
	glGenBuffers(1, &ShapeManager.EBO);


	glBindVertexArray(ShapeManager.VAO);

	glBindBuffer(GL_ARRAY_BUFFER, ShapeManager.VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticices), verticices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ShapeManager.EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indecies), indecies, GL_STATIC_DRAW);

	glUseProgram(ShapeManager.Program);
	glBindVertexArray(ShapeManager.VAO);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Quad::DrawQuad()
{	
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Quad::transform()
{
	
}
