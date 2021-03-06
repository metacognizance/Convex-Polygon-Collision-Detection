#include "actor/LifeActor.hpp"


LifeActor::LifeActor() :
	Actor()
{
	setType(ActorType::CarrotLife);
}

LifeActor::~LifeActor()
{
}

void LifeActor::control(const float deltaTime)
{
	m_velocity.y += 9.82*3;
	m_counter += deltaTime*m_id.id;

	if (isColliding())
	{
		if (m_counter >= (rand()%10) + 5)
		{
			m_velocity.y = -250;
			m_counter = 0;
		}
		
		auto it = m_jumpPoints.begin();
		auto center = m_polygon.getCenter();

		while (it != m_jumpPoints.end())
		{
			if (math::distance<float>(center, *it) <= 16)
			{
				m_velocity.y = -900;
				m_jumpPoints.erase(it);
			}
			else
				++it;
		}
	}

	if (math::magnitude<float>(m_velocity) > 900)
	{
		math::normalize(m_velocity);
		m_velocity = {m_velocity.x*900, m_velocity.y*900};
	}
}

bool LifeActor::isPlayer() const
{
	return false;
}

