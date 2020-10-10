#include "VertexArrayObject.hpp"

GLuint VertexArrayObject::s_currentlyBound = NULL;
int VertexArrayObject::s_currentAttribArraySlot = NULL;

VertexArrayObject::VertexArrayObject() :
    GLBindable()
{
    glGenVertexArrays(1, &m_id);
}

VertexArrayObject::~VertexArrayObject()
{
    //dtor
}

void VertexArrayObject::bind()
{
    GLuint toBind = m_id;
    glBindVertexArray(toBind);
    setCurrentlyBound(toBind);
}

void VertexArrayObject::enableVertexAttribArray(const int _slot)
{
    glEnableVertexAttribArray(_slot);
    s_currentAttribArraySlot = _slot;
}

GLuint VertexArrayObject::getCurrentlyBound() const
{
    return s_currentlyBound;
}

void VertexArrayObject::setCurrentlyBound(const GLuint _currentlyBound)
{
    s_currentlyBound = _currentlyBound;
}

void VertexArrayObject::unbind()
{
    GLuint toBind = NULL;
    glBindVertexArray(toBind);
    setCurrentlyBound(toBind);
}

void VertexArrayObject::vertexAttribPointer(const GLint _size, const GLenum _type)
{
    glVertexAttribPointer(
        s_currentAttribArraySlot,
        _size,
        _type,
        GL_FALSE,
        NULL,
        NULL
    );
}
