#include "Player.h"

Player::Player(Window& window, glm::vec3 cameraPosition, glm::mat4 projection)
	: window(window) {

	// Camera
	camera = Camera(cameraPosition, glm::vec3(0.f, 1.f, 0.f), -90.f, 0.f, PLAYER_SPEED, 0.3f);
	
}

void Player::keyboardUpdate(Movement movement, GLfloat deltaTime) {
	// Camera event updates
	camera.processKeyboard(movement, deltaTime);

}


void Player::update() {
	camera.processMouseMovement(window);
}
