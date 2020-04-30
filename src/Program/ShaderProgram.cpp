#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader) {
    // Load shaders from file
    vertexShaderID = loadShader(vertexShader, GL_VERTEX_SHADER);
    fragmentShaderID = loadShader(fragmentShader, GL_FRAGMENT_SHADER);

    // Create shader program
    programID = glCreateProgram();

    // Attach shaders to program
    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);

    // Linking
    glLinkProgram(programID);
    checkLinkErrors(programID);
}

ShaderProgram::~ShaderProgram() {
    // Unuse shader
    unUseShader();

    // Detach shader
    glDetachShader(programID, vertexShaderID);
    glDetachShader(programID, fragmentShaderID);

    // Delete shaders
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);

    // Delete program
    glDeleteProgram(programID);
}

GLuint ShaderProgram::loadShader(const std::string& fileName, GLenum type) {
    std::ifstream shaderFile;

    // Ensure ifstream objects can throw exceptions
    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    // Open files
    shaderFile.open(fileName);

    std::stringstream shaderStream;

    // Read buffer contents into streams
    shaderStream << shaderFile.rdbuf();

    // close file handlers
    shaderFile.close();

    // Convert stream into string
    std::string shaderCode = shaderStream.str();
    const char* shaderSource = shaderCode.c_str();

    // Compile shader
    GLuint newShaderID = glCreateShader(type);
    glShaderSource(newShaderID, 1, &shaderSource, NULL);
    glCompileShader(newShaderID);

    // Checks compile status
    GLint status;
    glGetShaderiv(newShaderID, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        // Get info log length
        GLint infoLogLength;
        glGetShaderiv(newShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);

        // Get info log
        GLchar* infoLog = new GLchar[infoLogLength];
        glGetShaderInfoLog(newShaderID, infoLogLength, NULL, infoLog);
        std::cout << "Error: Could not compile shader!\n" << infoLog << '\n';

        // Delete array
        delete[] infoLog;
    }



    return newShaderID;
}

void ShaderProgram::checkLinkErrors(GLuint programID) {
    GLint success;
    GLchar infoLog[1024];

    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(programID, 1024, NULL, infoLog);
        std::cout << "ERROR::SHADER_LINKING_ERROR of type: " << programID << '\n' << infoLog << '\n';
    }
}

void ShaderProgram::bindAttribute(int attribute, const std::string& variableName) {
    glBindAttribLocation(programID, attribute, variableName.c_str());
}

GLuint ShaderProgram::getUniformLocation(const std::string& name) {
    return glGetUniformLocation(programID, name.c_str());
}

void ShaderProgram::setBool(const std::string& name, bool value) const {
    glUniform1i(glGetUniformLocation(programID, name.c_str()), (int)value);
}

void ShaderProgram::setInt(const std::string& name, int value) const {
    glUniform1i(glGetUniformLocation(programID, name.c_str()), value);
}

void ShaderProgram::setFloat(const std::string& name, float value) const {
    glUniform1i(glGetUniformLocation(programID, name.c_str()), value);
}

void ShaderProgram::setVec2(const std::string& name, const glm::vec2& value) const {
    glUniform2fv(glGetUniformLocation(programID, name.c_str()), 1, &value[0]);
}

void ShaderProgram::setVec2(const std::string& name, GLfloat x, GLfloat y) const {
    glUniform2f(glGetUniformLocation(programID, name.c_str()), x, y);
}

void ShaderProgram::setVec3(const std::string& name, const glm::vec3& value) const {
    glUniform3fv(glGetUniformLocation(programID, name.c_str()), 1, &value[0]);
}

void ShaderProgram::setVec3(const std::string& name, GLfloat x, GLfloat y, GLfloat z) const {
    glUniform3f(glGetUniformLocation(programID, name.c_str()), x, y, z);
}

void ShaderProgram::setVec4(const std::string& name, const glm::vec4& value) const {
    glUniform4fv(glGetUniformLocation(programID, name.c_str()), 1, &value[0]);
}

void ShaderProgram::setVec4(const std::string& name, GLfloat x, GLfloat y, GLfloat z, GLfloat w) const {
    glUniform4f(glGetUniformLocation(programID, name.c_str()), x, y, z, w);
}

void ShaderProgram::setMat2(const std::string& name, const glm::mat2& mat) const {
    glUniformMatrix2fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void ShaderProgram::setMat3(const std::string& name, const glm::mat3& mat) const {
    glUniformMatrix3fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void ShaderProgram::setMat4(const std::string& name, const glm::mat4& mat) const {
    glUniformMatrix4fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}