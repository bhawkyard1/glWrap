#ifndef VERTEXBUFFEROBJECT_HPP
#define VERTEXBUFFEROBJECT_HPP

#include "BufferObject.hpp"


class VertexBufferObject : public BufferObject
{
    public:
        VertexBufferObject();
        virtual ~VertexBufferObject();
        GLuint getCurrentlyBound() const;
        void setCurrentlyBound(const GLuint _currentlyBound);
    protected:

    private:
        GLuint getEnum() {return GL_ARRAY_BUFFER;}
        static GLuint s_currentlyBound;
};

#endif // VERTEXBUFFEROBJECT_HPP
