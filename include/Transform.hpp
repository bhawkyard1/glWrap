#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include <vector>
#include "glm/matrix.hpp"
#include "glm/vec3.hpp"

enum Space {LOCAL, WORLD};

class Transform 
{
public:
	Transform();
	Transform(const glm::mat4 &_matrix);
	~Transform();
	//TODO Transform(const Transform &_other);
	//TODO Transform(const Transform &&_other);

	void addChild(const Transform &_child);
	Transform getChild(size_t _i) const {
		return m_children.at(_i);
	}
	glm::mat4 getMatrix(Space _space=LOCAL) const;
	Transform * getParent() const {
		return m_parent;
	}
	glm::vec3 getTranslation(Space _space=LOCAL) const;
	int numChildren() const {
		return m_children.size();
	}
	void setParent(Transform * _parent); 
	void setTranslation(const glm::vec3 &_trans, Space _space=LOCAL);

private:
	std::vector<Transform> m_children;
	glm::mat4 m_matrix;
	Transform * m_parent;
};

#endif