#include "MiniginPCH.h"
#include "Transform.h"

void dae::Transform::SetPosition(const float x, const float y, const float z)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}

void dae::Transform::SetPosition(const glm::vec3& pos)
{
	m_Position = pos;
}

const glm::vec3& dae::Transform::GetScale() const
{
	return m_Scale;
}

void dae::Transform::SetScale(const float x, const float y, const float z)
{
	m_Scale.x = x;
	m_Scale.y = y;
	m_Scale.z = z;
}

const glm::vec3& dae::Transform::GetPosition() const
{
	return m_Position;
}
