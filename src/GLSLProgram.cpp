#include "GLSLProgram.h"
#include "Errors.h"

#include <fstream>
#include <vector>

GLSLProgram::GLSLProgram() :
    _numAttributes(0),
    _programId(0),
    _vertexShaderId(0),
    _fragmentShaderId(0)
{

}

GLSLProgram::~GLSLProgram()
{

}

void GLSLProgram::compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath)
{
    _vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    if (_vertexShaderId == 0)
    {
        fatalError("Vertex shader failed to be created!");
    }

    _fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    if (_fragmentShaderId == 0)
    {
        fatalError("Fragment shader failed to be created!");
    }

    compileShader(vertexShaderFilePath, _vertexShaderId);
    compileShader(fragmentShaderFilePath, _fragmentShaderId);
}

void GLSLProgram::linkShaders()
{
    _programId = glCreateProgram();

    glAttachShader(_programId, _vertexShaderId);
    glAttachShader(_programId, _fragmentShaderId);

    glLinkProgram(_programId);

    GLint isLinked = 0;
    glGetProgramiv(_programId, GL_LINK_STATUS, (int *)&isLinked);
    if (isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(_programId, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<char> errorLog(maxLength);
        glGetProgramInfoLog(_programId, maxLength, &maxLength, &errorLog[0]);

        glDeleteProgram(_programId);

        glDeleteShader(_vertexShaderId);
        glDeleteShader(_fragmentShaderId);

        std::printf("%s\n", &(errorLog[0]));
        fatalError("Shaders failed to link!");
    }

    glDetachShader(_programId, _vertexShaderId);
    glDetachShader(_programId, _fragmentShaderId);
    glDeleteShader(_vertexShaderId);
    glDeleteShader(_fragmentShaderId);
}

void GLSLProgram::compileShader(const std::string& filePath, GLuint id)
{
    std::ifstream vertexFile(filePath);
    if (vertexFile.fail())
    {
        perror(filePath.c_str());
        fatalError("Shader could not be opened at " + filePath);
    }

    std::string fileContent;
    std::string line;

    while (std::getline(vertexFile, line))
    {
        fileContent += line + "\n";
    }

    vertexFile.close();

    const char* contentPtr = fileContent.c_str();
    glShaderSource(id, 1, &contentPtr, nullptr);
    glCompileShader(id);

    GLint success = 0;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);

    if (success == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<char> errorLog(maxLength);
        glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

        glDeleteShader(id);

        std::printf("%s\n", &errorLog[0]);
        fatalError("Shader " + filePath + " failed to compile!");
    }
}

void GLSLProgram::addAttribute()
{
    _numAttributes++;
}

void GLSLProgram::use()
{
    glUseProgram(_programId);
    
    for (int i = 0; i < _numAttributes; i++)
    {
        glEnableVertexAttribArray(i);
    }
}

void GLSLProgram::unuse()
{
    glUseProgram(0);

    for (int i = 0; i < _numAttributes; i++)
    {
        glDisableVertexAttribArray(i);
    }
}