#include <iostream>

#include "ShaderProgram.hpp"

ShaderProgram::ShaderProgram() :
    m_id(0)
{
    m_id = glCreateProgram();
}

ShaderProgram::~ShaderProgram()
{
    //dtor
}

void ShaderProgram::attachShader(Shader& _shader)
{
    glAttachShader(m_id, _shader.getID());
}

void ShaderProgram::bind()
{
    glUseProgram(m_id);
}

/*GLint ShaderProgram::getAttributeLocation(const std::string& _attr)
{
    GLint p = glGetAttribLocation(m_id, _attr.c_str());
    if(p == -1)
    {
        std::cerr << "Error! Could not find an attribute location for " << _attr << "!" << std::endl;
    }
    return p;
}*/

void ShaderProgram::linkProgram()
{
    glLinkProgram(m_id);

    //Check for errors
    GLint programSuccess = GL_TRUE;
    glGetProgramiv(m_id, GL_LINK_STATUS, &programSuccess);
    if(programSuccess != GL_TRUE)
    {
        std::cout << "Error linking program " << m_id << "\n" << ShaderProgram::getLinkingLog() << std::endl;
    }
}

std::string ShaderProgram::getLinkingLog()
{
    //Make sure name is shader
    if(glIsProgram(m_id))
    {
        //Program log length
        int infoLogLength = 0;
        int maxLength = infoLogLength;

        //Get info string length
        glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &maxLength);

        //Allocate string
        std::string infoLog(maxLength, ' ');

        //Get info log
        glGetProgramInfoLog(
            m_id,
            maxLength,
            &infoLogLength,
            const_cast<char*>(infoLog.c_str())
        );
        if( infoLogLength > 0 )
        {
            return infoLog;
        }
        else
        {
            return "No info returned from log.";
        }
    }
    else
    {
        return "Not a program.";
    }
}

void ShaderProgram::unbind()
{
    glUseProgram(NULL);
}
