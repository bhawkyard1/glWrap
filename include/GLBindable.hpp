#ifndef GLBINDABLE_HPP
#define GLBINDABLE_HPP

#include "GLHeaders.hpp"

class GLBindable
{
    public:
        GLBindable()=default;
        ~GLBindable()=default;

        bool operator==(const GLBindable& _other);
        bool operator==(const GLuint& _other);

        void bind() {};
        virtual GLuint getCurrentlyBound() const {return 0;};
        virtual void setCurrentlyBound(const GLuint& _currentlyBound) {};

        GLuint getID() const {return m_id;}
        bool isBound() const {return m_id == getCurrentlyBound();}
        void unbind() {};

    protected:
        GLuint m_id;

    private:
};

#endif // GLBINDABLE_HPP
