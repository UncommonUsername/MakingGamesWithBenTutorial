#pragma once

#include "GL/glew.h"

#include <string>

class GLSLProgram
{
public:
    GLSLProgram();
    ~GLSLProgram();

    void compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);

    void linkShaders();

    void addAttribute();

    GLuint getUniformLocation(const std::string& uniformName);
    void use();
    void unuse();

private:
    
    int _numAttributes;

    void compileShader(const std::string& filePath, GLuint id);

    GLuint _programId;

    GLuint _vertexShaderId;
    GLuint _fragmentShaderId;
};