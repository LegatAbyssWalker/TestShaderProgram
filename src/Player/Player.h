#pragma once

#include "Camera.h"
#include "../States/Functionality/State.h"
#include "../Window/Window.h"
#include "../Utilities/FileLocations.h"
#include "../Utilities/Variables.h"
#include "../Program/ShaderProgram.h"

#include <iostream>
#include <memory>


class Player {
	public:
		Player(Window& window, glm::vec3 cameraPosition, glm::mat4 projection);

		void keyboardUpdate(Movement movement, GLfloat deltaTime);

		void update();
		

		Camera& getCamera() { return camera; }


	private:
		Movement movement;
		Window& window;

		Camera camera;
		GLfloat lastX = window.getWindow().getSize().x / 2.f;
		GLfloat lastY = window.getWindow().getSize().y / 2.f;
		bool firstMouse = true;
};