#include "PlayingState.h"


PlayingState::PlayingState(StateMachine& machine, Window& window, bool replace)
	: State(machine, window, replace), window(window) {

	// Player
//	player = std::make_unique<Player>(window, glm::vec3(0, 0, 0), window.getPerspectiveMatrix());

	// Model
	std::vector<float> vertices = {
	   -0.5f, 0.5f, 0.f,
	   -0.5f, -0.5f, 0.f,
	   0.5f, -0.5f, 0.f,
	   0.5f, -0.5f, 0.f,
	   0.5f, 0.5f, 0.f,
	   -0.5f, 0.5f, 0.f
	};

	program = std::make_unique<ShaderProgram>(BASIC_VERTEX_SHADER, BASIC_FRAGMENT_SHADER);
	model = std::make_unique<RawModel>(loader.loadToVAO(vertices));

}

void PlayingState::keyboardInput(sf::Keyboard::Key& key, bool isPressed) {
	if (key == sf::Keyboard::Escape) { machine.quit(); }
}

void PlayingState::updateEvents() {
	while (window.getWindow().pollEvent(sfEvent)) {
		auto keyCode = sfEvent.key.code;
		switch (sfEvent.type) {
			case sf::Event::Resized:
				this->window.setViewPort(glm::vec2(0), glm::vec2(sfEvent.size.width, sfEvent.size.height));
				break;

			case sf::Event::Closed:
				machine.quit();
				break;

			case sf::Event::KeyPressed:
				keyboardInput(keyCode, true);
				break;

			case sf::Event::KeyReleased:
				keyboardInput(keyCode, false);
				break;
		}
/*
		// Keyboard
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))	 { player->keyboardUpdate(Movement::FORWARD,  deltaTime); }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))	 { player->keyboardUpdate(Movement::LEFT,     deltaTime); }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))	 { player->keyboardUpdate(Movement::BACKWARD, deltaTime); }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))	 { player->keyboardUpdate(Movement::RIGHT,    deltaTime); }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) { player->keyboardUpdate(Movement::SHOOTING, deltaTime); }

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))    { player->keyboardUpdate(Movement::UP,       deltaTime); }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))  { player->keyboardUpdate(Movement::DOWN,     deltaTime); }*/
	}
}

void PlayingState::update() {
	GLfloat now = clock.getElapsedTime().asSeconds();
	deltaTime = now - lastFrame;
	lastFrame = now;

	// Player
	// player->update();


}

void PlayingState::render() {
	renderer.prepare(0.5f, 1.f, 1.f, 1.f);
	program->useShader();

	renderer.render(model);

	program->unUseShader();
	window.swapBuffers();
}
