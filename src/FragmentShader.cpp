#include "FragmentShader.hpp"

FragmentShader::FragmentShader(const std::string& _sourceCode) :
    Shader(_sourceCode)
{
    m_id = glCreateShader(GL_FRAGMENT_SHADER);
}

