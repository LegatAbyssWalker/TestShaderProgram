#pragma once

#include "GL/glew.h"

class RawModel {
	public:
		RawModel(GLuint& vaoID, const int& vertexCount) : vaoID(vaoID), vertexCount(vertexCount) { }

		inline GLuint getVaoID() { return vaoID; }
		inline int getVertexCount() { return vertexCount; }

	private:
		GLuint vaoID;
		int vertexCount;
};
