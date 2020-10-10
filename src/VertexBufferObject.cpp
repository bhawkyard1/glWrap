#include "VertexBufferObject.hpp"

GLuint VertexBufferObject::s_currentlyBound = NULL;

VertexBufferObject::VertexBufferObject()
{
    //ctor
}

VertexBufferObject::~VertexBufferObject()
{
    //dtor
}


GLuint VertexBufferObject::getCurrentlyBound() const
{
    return s_currentlyBound;
}

void VertexBufferObject::setCurrentlyBound(const GLuint _currentlyBound)
{
    s_currentlyBound = _currentlyBound;
}
