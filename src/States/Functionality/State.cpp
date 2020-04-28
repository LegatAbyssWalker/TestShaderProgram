#include "State.h"


State::State(StateMachine& machine, Window& glWindow, bool replace)
	: machine{ machine }
	, window{ window }
	, replacing{ replace } {
}

std::unique_ptr<State> State::nextState() {
	return std::move(next);
}

bool State::isReplacing() {
	return replacing;
}