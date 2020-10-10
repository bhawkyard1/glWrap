#include <iostream>

#include "Shader.hpp"

Shader::Shader(const std::string& _sourceCode) :
    m_sourceCode(_sourceCode + "\0")
{
}

void Shader::compile()
{
    const char *data = m_sourceCode.c_str();
    glShaderSource(
        m_id,
        1,
        &data,
        nullptr
    );

    glCompileShader(m_id);

    //Check vertex shader for errors
    GLint vShaderCompiled = GL_FALSE;
    glGetShaderiv(m_id, GL_COMPILE_STATUS, &vShaderCompiled);
    if(vShaderCompiled == GL_FALSE)
    {
        std::cout << "Unable to compile shader " << m_id << std::endl;
        std::cout << Shader::getCompileLog() << std::endl;
    }
}

std::string Shader::getCompileLog()
{
    //Make sure name is shader
    if(glIsShader(m_id))
    {
        //Shader log length
        int infoLogLength = 0;
        int maxLength = infoLogLength;

        //Get info string length
        glGetShaderiv(m_id, GL_INFO_LOG_LENGTH, &maxLength);

        //Allocate string
        std::string infoLog(maxLength, ' ');

        //Get info log
        glGetShaderInfoLog(
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
        return "Not a shader.";
    }

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
