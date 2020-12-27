#pragma once

class Quad {
public:
	void InitQuad();
	void DrawQuad();
	int Program;
	unsigned int VBO, VAO, EBO;
	void transform();
};