#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/quaternion.hpp>

#include "Transform.hpp"

Transform::Transform() : 
    m_dirty(false),
    m_matrix(1.0),
    m_scale(1.0, 1.0, 1.0)
{
    m_parent = nullptr;
}

Transform::Transform(const glm::mat4 &_matrix) :
    m_dirty(false),
    m_matrix(_matrix)
{
    m_parent = nullptr;
}

Transform::~Transform()
{
    for(auto child: m_children)
    {
        child.setParent(nullptr);
    }
}

void Transform::addChild(const Transform &_child)
{
    m_children.push_back(_child);
}

void Transform::calculateLocalMatrix()
{
    m_matrix = glm::mat4(1.0);
    m_matrix = glm::scale(m_matrix, m_scale);
    m_matrix = glm::toMat4(m_rotation) * m_matrix;
    m_matrix = glm::translate(m_matrix, m_translation);
}

glm::mat4 Transform::getMatrix(Space _space)
{
    if(m_dirty)
    {
        calculateLocalMatrix();
    }

    if(_space == Space::LOCAL)
    {
        return m_matrix;
    }
    
    Transform * cur = getParent();
    std::vector<glm::mat4> stack;
    while(cur != nullptr)
    {
        stack.push_back(cur->getMatrix());
        cur = cur->getParent();
    }

    glm::mat4 curMat = m_matrix;
    for(auto &m : stack)
    {
        curMat = curMat * m;
    }

    return curMat;
}

glm::quat Transform::getRotation(Space _space)
{
    if(_space == Space::LOCAL)
    {
        return m_rotation;
    }

    glm::mat4 transformation = getMatrix(_space);
    glm::vec3 scale;
    glm::quat rotation;
    glm::vec3 translation;
    glm::vec3 skew;
    glm::vec4 perspective;
    glm::decompose(transformation, scale, rotation, translation, skew,perspective);
    return rotation;
}

glm::vec3 Transform::getScale(Space _space)
{
    if(_space == Space::LOCAL)
    {
        return m_scale;
    }

    glm::mat4 transformation = getMatrix(_space);
    glm::vec3 scale;
    glm::quat rotation;
    glm::vec3 translation;
    glm::vec3 skew;
    glm::vec4 perspective;
    glm::decompose(transformation, scale, rotation, translation, skew,perspective);
    return scale;
}

glm::vec3 Transform::getTranslation(Space _space)
{
    if(_space == Space::LOCAL)
    {
        return m_translation;
    }
    else if(_space == Space::WORLD)
    {
        return getMatrix(Space::WORLD)[3];
    }
}

void Transform::setParent(Transform * _parent)
{
    m_parent = _parent;
}

void Transform::setRotation(const glm::vec3& _rot, Space _space)
{
    setRotation(glm::quat(_rot), _space);
}

void Transform::setRotation(const glm::quat& _rot, Space _space)
{
    if(_space == Space::LOCAL)
    {
        m_rotation = _rot;
    }
    else if(_space == Space::WORLD)
    {
        //glm::quat curRot = getRotation(Space::WORLD);
        //m_rotation = _rot - curRot;
    }

    m_dirty = true;
}

void Transform::setScale(const glm::vec3& _scale, Space _space)
{
    if(_space == Space::LOCAL)
    {
        m_scale = _scale;
    }
    else if(_space == Space::WORLD)
    {
        glm::vec3 curScale = getScale(Space::WORLD);
        m_scale = glm::vec3(
            _scale.x / curScale.x,
            _scale.y / curScale.y,
            _scale.z / curScale.z
        );
    }

    m_dirty = true;
}

void Transform::setTranslation(const glm::vec3 &_trans, Space _space)
{
    if(_space == Space::LOCAL)
    {
        m_translation = _trans;
    }
    else if(_space == Space::WORLD)
    {
        glm::vec3 curTrans = getTranslation(Space::WORLD);
        m_translation = _trans - curTrans;
    }

    m_dirty = true;
}