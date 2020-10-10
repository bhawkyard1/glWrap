#ifndef VERTEXARRAYOBJECT_HPP
#define VERTEXARRAYOBJECT_HPP

#include "GLBindable.hpp"

class VertexArrayObject : public GLBindable
{
    public:
        VertexArrayObject();
        virtual ~VertexArrayObject();

        void bind();
        void enableVertexAttribArray(const int _slot);
        GLuint getCurrentlyBound() const;
        void setCurrentlyBound(const GLuint _currentlyBound);
        void unbind();
        void vertexAttribPointer(
            const GLint _size,
            const GLenum _type
        );

    protected:

    private:
        static GLuint s_currentlyBound;
        static int s_currentAttribArraySlot;
};

#endif // VERTEXARRAYOBJECT_HPP
