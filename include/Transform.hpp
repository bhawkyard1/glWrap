#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include <iostream>
#include <vector>
#include <glm/matrix.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/vec3.hpp>

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
	glm::mat4 getMatrix(Space _space=LOCAL);
	Transform * getParent() const {
		return m_parent;
	}
	//TODO
	glm::quat getRotation(Space _space=LOCAL);
	glm::vec3 getScale(Space _space=LOCAL);
	glm::vec3 getTranslation(Space _space=LOCAL);

	int numChildren() const {
		return m_children.size();
	}
	void setParent(Transform * _parent); 
	
	void setRotation(float _x, float _y, float _z, Space _space=LOCAL)
	{
		setRotation(glm::vec3(_x, _y, _z), _space);
	}
	void setRotation(const glm::vec3& _rot, Space _space=LOCAL);
	void setRotation(const glm::quat& _rot, Space _space=LOCAL);

	void setScale(float _x, float _y, float _z, Space _space=LOCAL)
	{
		setScale(glm::vec3(_x, _y, _z), _space);
	}
	void setScale(const glm::vec3& _scale, Space _space=LOCAL);
	
	void setTranslation(float _x, float _y, float _z, Space _space=LOCAL) {
		setTranslation(glm::vec3(_x, _y, _z));
	}
	void setTranslation(const glm::vec3& _trans, Space _space=LOCAL);
	
private:
	void calculateLocalMatrix();

	std::vector<Transform> m_children;
	bool m_dirty;
	glm::mat4 m_matrix;
	Transform * m_parent;
	glm::vec3 m_translation;
	glm::quat m_rotation;
	glm::vec3 m_scale;
};

#endif