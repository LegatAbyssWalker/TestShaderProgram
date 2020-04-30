#pragma once

#include "../../States/Functionality/State.h"
#include "../../States/Functionality/StateMachine.h"
class StateMachine;

#include <iostream>
#include <array>
#include <memory>
#include <vector>

#include "../../Window/Window.h"
#include "../../Player/Player.h"

#include "../../Models/Functionality/Loader.h"
#include "../../Models/Functionality/Renderer.h"
#include "../../Models/Functionality/RawModel.h"
#include "../../Program/ShaderProgram.h"


class PlayingState : public State {
	public:
		PlayingState(StateMachine& machine, Window& window, bool replace = true);

		void keyboardInput(sf::Keyboard::Key& key, bool isPressed);

		void updateEvents();
		void update();
		void render();

	private:
		Window& window;
		sf::Event sfEvent;
		sf::Clock clock;
		GLfloat deltaTime = 0, lastFrame = 0;

		std::unique_ptr<RawModel> model = nullptr;
		std::unique_ptr<ShaderProgram> program = nullptr;
		Loader loader;
		Renderer renderer;

		// std::unique_ptr<Player> player = nullptr;
};

