#include "BufferObject.hpp"

BufferObject::BufferObject()
{
    glGenBuffers(1, &m_id);
}

BufferObject::~BufferObject()
{
    //dtor
}

void BufferObject::bind()
{
    glBindBuffer(getEnum(), m_id);
    setCurrentlyBound(m_id);
}

void BufferObject::unbind()
{
    glBindBuffer(getEnum(), NULL);
    setCurrentlyBound(NULL);
}
