#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP

#include "GLHeaders.hpp"
#include "Shader.hpp"

class ShaderProgram
{
    public:
        ShaderProgram();
        virtual ~ShaderProgram();

        void attachShader(Shader &_shader);
        void bind();
        //GLint getAttributeLocation(const std::string& _attr);
        void linkProgram();
        void unbind();

    protected:

    private:
        std::string getLinkingLog();
        GLuint m_id;
};

#endif // SHADERPROGRAM_HPP
