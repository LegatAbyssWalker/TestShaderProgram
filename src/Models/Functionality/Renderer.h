#pragma once

#include "RawModel.h"

#include "glm/glm.hpp"

#include <memory>

class Renderer {
	public:
		Renderer() = default;

		void prepare(int r, int g, int b, int alpha) { 
			glClearColor(r, g, b, alpha); 
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void render(std::unique_ptr<RawModel>& model);

};

