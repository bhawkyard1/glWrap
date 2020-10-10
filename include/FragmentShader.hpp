#ifndef FRAGMENTSHADER_HPP
#define FRAGMENTSHADER_HPP

#include "Shader.hpp"

class FragmentShader : public Shader
{
    public:
        FragmentShader(const std::string& _sourceCode);
        ~FragmentShader()=default;

    protected:
    private:
};

#endif // FRAGMENTSHADER_HPP
