#include "Player.h"


Player::~Player() {
	Shape::~Shape();
}

void Player::Inputs(GLFWwindow* window) {
	Point currentPos = getPosition();
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		currentPos.x += m_walkValue;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		currentPos.x -= m_walkValue;
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		currentPos.y += m_jumpValue;
	}
	setPos(currentPos.x, currentPos.y);
}

bool HasCollided(Shape shape) {
	return false;
}