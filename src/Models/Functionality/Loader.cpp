#include "Loader.h"

Loader::Loader() {
	// Init variables
	vaos.clear();
	vbos.clear();
	textures.clear();
}

Loader::~Loader() {
	while (vaos.size() > 0) {
		glDeleteBuffers(1, &vaos.back());
		vaos.pop_back();
	}

	while (vbos.size() > 0) {
		glDeleteBuffers(1, &vbos.back());
		vbos.pop_back();
	}

	while (textures.size() > 0) {
		glDeleteTextures(1, &textures.back());
		textures.pop_back();
	}
}

RawModel Loader::loadToVAO(std::vector<float> positions) {
	// Create new VAO
	GLuint vaoID = createVAO();

	// Store data in attribute list
	storeDataInAttributeList(0, 3, &positions, positions.size() * sizeof(float));

	// Unbind VAO
	unbindVAO();

	return RawModel(vaoID, positions.size() / 3);
}

RawModel Loader::loadToVAO(std::vector<float> positions, std::vector<int> indices) {
	// Create new VAO
	GLuint vaoID = createVAO();

	// Indices
	int indicesSize = indices.size();
	bindIndicesBuffer(indices.data(), indicesSize);

	// Store data in attribute list
	storeDataInAttributeList(0, 3, &positions, positions.size() * sizeof(float));

	// Unbind VAO
	unbindVAO();

	return RawModel(vaoID, positions.size() / 3);
}

RawModel Loader::loadToVAO(std::vector<glm::vec3> vertices, std::vector<glm::vec2> textures, 
	std::vector<glm::vec3> normals, std::vector<int> indices) {

	// Create new VAO
	GLuint vaoID = createVAO();
	int indicesSize = indices.size();
	bindIndicesBuffer(indices.data(), indicesSize);

	// Store data in attribute list
	storeDataInAttributeList(0, 3, &vertices[0], vertices.size() * sizeof(glm::vec3));
	storeDataInAttributeList(1, 2, &textures[0], textures.size() * sizeof(glm::vec3));
	storeDataInAttributeList(2, 3, &normals[0],  normals.size()  * sizeof(glm::vec3));

	// Unbinding
	unbindVAO();


	return RawModel(vaoID, indicesSize);
}

GLuint Loader::loadTexture(const std::string& fileName, bool repeat) {
	GLuint texture;
	
	// Load images
	sf::Image image;
	image.loadFromFile(fileName);

	// Generate and bind OpenGL texture
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// Parameters
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Repeating
	if (!repeat) {
		// Clamping
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}

	// Store the OpenGL texture data
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getSize().x, image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
	textures.push_back(texture);

	// Unload image data
	// image.~Image(); not entirely sure

	return texture;
}

GLuint Loader::createVAO() {
	GLuint vaoID;

	// Creates a new vao
	glGenVertexArrays(1, &vaoID);

	// Stores in list
	vaos.push_back(vaoID);

	// Binds VAO
	glBindVertexArray(vaoID);

	return vaoID;
}

void Loader::storeDataInAttributeList(GLuint attributeNumber, int attributeSize, void* data, int dataSize) {
	GLuint vboID;

	// Create a new buffer
	glGenBuffers(1, &vboID);

	// Store buffer in list
	vbos.push_back(vboID);

	// Bind the buffer 
	glBindBuffer(GL_ARRAY_BUFFER, vboID);

	// Store data in buffer
	glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);

	// Tell OpenGL how and where to store this VBO in the VAO
	glVertexAttribPointer(attributeNumber, attributeSize, GL_FLOAT, GL_FALSE, 0, nullptr);
}

void Loader::bindIndicesBuffer(int* indices, int& count) {
	GLuint vboID;

	// Generate a buffer and bind it for use
	glGenBuffers(1, &vboID);

	// Store the buffer in the list
	vbos.push_back(vboID);

	// Bind the buffer to use it
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);

	// Store the indices in the buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * count, indices, GL_STATIC_DRAW);
}
