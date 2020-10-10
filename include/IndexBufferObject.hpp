#ifndef INDEXBUFFEROBJECT_HPP
#define INDEXBUFFEROBJECT_HPP

#include "BufferObject.hpp"


class IndexBufferObject : public BufferObject
{
    public:
        IndexBufferObject();
        virtual ~IndexBufferObject();

    protected:

    private:
        GLuint getEnum() {return GL_ELEMENT_ARRAY_BUFFER;}
};

#endif // INDEXBUFFEROBJECT_HPP
