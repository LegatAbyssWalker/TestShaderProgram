#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "../Utilities/FileLocations.h"
#include "../Utilities/Variables.h"

#include "GL/glew.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class Window {
	public:
		Window() = default;
		~Window();

		void initWindow();
		void swapBuffers();
	
		void setMouseVisible(bool visible);
		void setViewPort(glm::vec2 origin, glm::vec2 newWidthNewHeight);

		bool getMouseVisible() const { return mouseVisible; }

		bool isOpen() { return window.isOpen(); }
		sf::Window& getWindow() { return window; }


		glm::mat4 getPerspectiveMatrix() {
			return glm::perspective(glm::radians(45.f), 
				(GLfloat)getWindow().getSize().x / getWindow().getSize().y, 0.1f, 100.f);
		}

		glm::mat4 getOrthographicMatrix() {
			return glm::ortho(0.f, (float)window.getSize().x, (float)window.getSize().y, 0.f, -1.0f, 1.0f);
		}

	private:
		sf::Window window;

		bool mouseVisible = true;
};

