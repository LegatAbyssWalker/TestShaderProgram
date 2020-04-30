#pragma once

#include <vector>
#include <string>

#include "glm/glm.hpp"
#include "SFML/Graphics.hpp"

#include "RawModel.h"

class Loader {
	public:
		Loader();
		virtual ~Loader();

		RawModel loadToVAO(std::vector<float> positions);
		RawModel loadToVAO(std::vector<float> positions, std::vector<int> indices);

		RawModel loadToVAO(std::vector<glm::vec3> vertices, std::vector<glm::vec2> textures, 
			std::vector<glm::vec3> normals, std::vector<int> indices);

		GLuint loadTexture(const std::string& fileName, bool repeat = false);
		inline void unbindVAO() { glBindVertexArray(0); }

	private:
		std::vector<GLuint> vaos;
		std::vector<GLuint> vbos;
		std::vector<GLuint> textures;

		GLuint createVAO();
		void storeDataInAttributeList(GLuint attributeNumber, int attributeSize, void* data, int dataSize);
		void bindIndicesBuffer(int* indices, int& count);

};

