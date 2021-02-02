#include <glm/gtc/matrix_transform.hpp>

#include "Camera.hpp"

Camera::Camera(double _aspect, double _fov, double _near, double _far) :
	m_aspect(_aspect),
	m_fov(_fov),
	m_clippingDistances(_near, _far)
{
	m_project = glm::perspective(
		m_fov,
		m_aspect,
		m_clippingDistances.first,
		m_clippingDistances.second
	);
}