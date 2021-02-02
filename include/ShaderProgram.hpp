#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP

#include "glm/matrix.hpp"

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

        void setUniform(const std::string& _uniformName, float _x);
        void setUniform(const std::string& _uniformName, float _x, float _y, float _z);
        void setUniform(const std::string& _uniformName, const glm::mat4& _mat);

    protected:

    private:
        std::string getLinkingLog();
        GLint getUniformLocation(const std::string& _uniformName);
        GLuint m_id;
};

#endif // SHADERPROGRAM_HPP
