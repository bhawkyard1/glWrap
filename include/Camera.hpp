#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <utility>

#include "glm/matrix.hpp"

class Camera
{
public:
	Camera(double _aspect, double _fov, double _near, double _far);

	glm::mat4 getProjectMatrix() const {return m_project;}

private:
	double m_aspect;
	double m_fov;
	std::pair<double, double> m_clippingDistances;

	glm::mat4 m_project;
};

#endif