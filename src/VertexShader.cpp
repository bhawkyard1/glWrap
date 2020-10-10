#include "VertexShader.hpp"

VertexShader::VertexShader(const std::string& _sourceCode):
    Shader(_sourceCode)
{
    m_id = glCreateShader(GL_VERTEX_SHADER);
}
