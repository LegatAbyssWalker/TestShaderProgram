#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "../../Window/Window.h"

#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <array>
#include <memory>

class StateMachine;

class State {
	public:
		State(StateMachine& machine, Window& window, bool replace = true);

		State(const State&) = delete;
		State& operator = (const State&) = delete;

		virtual void updateEvents() = 0;
		virtual void update() = 0;
		virtual void render() = 0;

		std::unique_ptr<State> nextState();

		bool isReplacing();

	protected:
		StateMachine& machine;
		Window& window;

		bool replacing;

		std::unique_ptr<State> next;
};
