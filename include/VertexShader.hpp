#ifndef VERTEXSHADER_HPP
#define VERTEXSHADER_HPP

#include "Shader.hpp"

class VertexShader : public Shader
{
    public:
        VertexShader(const std::string& _sourceCode);
        ~VertexShader()=default;
    protected:

    private:
};

#endif // VERTEXSHADER_HPP
