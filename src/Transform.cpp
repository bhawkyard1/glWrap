#include <glm/gtc/matrix_transform.hpp>

#include "Transform.hpp"

Transform::Transform() : 
	m_matrix(1.0)
{
	m_parent = nullptr;
}

Transform::Transform(const glm::mat4 &_matrix) :
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

glm::mat4 Transform::getMatrix(Space _space) const
{
	if(_space == LOCAL)
	{
		return m_matrix;
	}
	
	const Transform * cur = this;
	std::vector<glm::mat4> stack;
	while(cur->getParent() != nullptr)
	{
		cur = cur->getParent();
		stack.push_back(cur->getMatrix());
	}

	glm::mat4 curMat = m_matrix;
	for(auto &m : stack)
	{
		curMat = curMat * m;
	}

	return curMat;
}

glm::vec3 Transform::getTranslation(Space _space) const
{
	glm::mat4 mat = getMatrix(_space);
	return glm::vec3(mat[3]);
}

void Transform::setParent(Transform * _parent)
{
	m_parent = _parent;
}

void Transform::setTranslation(const glm::vec3 &_trans, Space _space)
{
	if(_space == LOCAL)
	{
		glm::vec3 curTrans = getTranslation(LOCAL);
		m_matrix = glm::translate(
			m_matrix, -curTrans
		);
		m_matrix = glm::translate(
			m_matrix, _trans
		);
	}
	else if(_space == WORLD)
	{
		glm::vec3 curTrans = getTranslation(LOCAL);
		glm::vec3 diff = _trans - curTrans;
		m_matrix = glm::translate(
			m_matrix, diff
		);
	}
}