#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "GL/glew.h"
#include "glm/glm.hpp"

class ShaderProgram {
    public:
        ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);
        virtual ~ShaderProgram();

        inline void useShader() { glUseProgram(programID); }
        inline void unUseShader() { glUseProgram(0); }

    private:
        GLuint programID;
        GLuint vertexShaderID;
        GLuint fragmentShaderID;

        GLuint loadShader(const std::string& fileName, GLenum type);
        void checkLinkErrors(GLuint programID);

    protected:
        void bindAttribute(int attribute, const std::string& variableName);
        GLuint getUniformLocation(const std::string& name);

        void setBool(const std::string& name, bool value) const;
        void setInt(const std::string& name, int value) const;
        void setFloat(const std::string& name, float value) const;

        void setVec2(const std::string& name, const glm::vec2& value) const;
        void setVec2(const std::string& name, GLfloat x, GLfloat y) const;

        void setVec3(const std::string& name, const glm::vec3& value) const;
        void setVec3(const std::string& name, GLfloat x, GLfloat y, GLfloat z) const;

        void setVec4(const std::string& name, const glm::vec4& value) const;
        void setVec4(const std::string& name, GLfloat x, GLfloat y, GLfloat z, GLfloat w) const;

        void setMat2(const std::string& name, const glm::mat2& mat) const;
        void setMat3(const std::string& name, const glm::mat3& mat) const;
        void setMat4(const std::string& name, const glm::mat4& mat) const;
};