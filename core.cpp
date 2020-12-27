#include "Versa.h"


Triangle triangle;
Quad quad;
WindowManager windowmanager;


void WindowManager::Start()
{
	quad.InitQuad();
}
void WindowManager::Update()
{
	//On Update
	windowmanager.BackgroundColor(0.1f, 0.1f, 0.1f, 1.0f);
	quad.DrawQuad();
}