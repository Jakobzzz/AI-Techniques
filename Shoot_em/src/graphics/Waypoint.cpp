#include <graphics/Waypoint.hpp>
#include <utils/Utility.hpp>

namespace sm
{
	Waypoint::Waypoint(const TextureHolder & textures) : m_textures(textures), m_currentIndex(0)
	{
	}

	void Waypoint::update(sf::Sprite & sprite, const float & speed, double dt)
	{
		//Move sprite towards points in the waypoints vector
		if (!m_waypoints.empty())
		{
			sf::Vector2f movement(0.f, 0.f);
			sf::Vector2f unitDir = utils::unitVec(m_waypoints[m_currentIndex].getPosition() - sprite.getPosition());
			movement += unitDir * speed * (float)dt;
			utils::rotateTowards(sprite, m_waypoints[m_currentIndex].getPosition());
			sprite.setPosition(sprite.getPosition() + movement);

			//Update the index to the next waypoint
			if (m_waypoints[m_currentIndex].getGlobalBounds().intersects(sprite.getGlobalBounds()))
			{
				if (m_currentIndex < m_waypoints.size() - 1)
					m_currentIndex++;
			}
		}
	}

	void Waypoint::add(const sf::Vector2i & position)
	{
		sf::Sprite shape;
		shape.setPosition(sf::Vector2f((float)position.x, (float)position.y));
		shape.setTexture(m_textures.getResource(Textures::ID::Waypoint));
		shape.setScale(sf::Vector2f(0.1f, 0.1f));
		m_waypoints.push_back(shape);
		printf("Placed waypoint at position: (%d, %d)\n", position.x, position.y);
	}

	void Waypoint::remove(const sf::Vector2i & position)
	{
		for (unsigned i = 0; i < m_waypoints.size(); ++i)
		{
			if (m_waypoints[i].getGlobalBounds().contains((float)position.x, (float)position.y))
			{
				//Swap the index of the last entry
				if (i != m_waypoints.size() - 1)
					m_waypoints[i] = std::move(m_waypoints.back());

				//Remove waypoint from the vector
				m_waypoints.pop_back();
			}
		}
	}

	void Waypoint::reset()
	{
		m_currentIndex = 0;
	}

	void Waypoint::clear()
	{
		m_waypoints.clear();
	}

	void Waypoint::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		for (auto v : m_waypoints)
		{
			target.draw(v);
			//target.draw(utils::getBoundingRect(v.getGlobalBounds())); //Draw bounding rect of the shape
		}
	}
}