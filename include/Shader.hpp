#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>

#include "GLHeaders.hpp"

class Shader
{
    public:
        Shader(const std::string& _sourceCode);
        virtual ~Shader() {};

        void compile();
        GLuint getID() const {return m_id;}

    protected:
        GLuint m_id;

    private:
        std::string getCompileLog();
        std::string m_sourceCode;
};

#endif // SHADER_HPP
