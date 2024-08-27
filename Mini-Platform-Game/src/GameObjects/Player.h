#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../Utils/Shape.h"
#include "../Utils/Utilities.h"

class Player : public Shape {
private:
	float m_walkValue;
	float m_jumpValue;
public:
	Player() : Shape(100, 100, SQUARE), m_walkValue(10.0f), m_jumpValue(10.0f) {};
	~Player();
	void Inputs(GLFWwindow* window);
};