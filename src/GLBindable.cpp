#include "GLBindable.hpp"

bool GLBindable::operator==(const GLBindable& _other)
{
    return m_id == _other.getID();
}

bool GLBindable::operator==(const GLuint& _other)
{
    return m_id == _other;
}
