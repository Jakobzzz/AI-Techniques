#pragma once
#include <utils/ResourceHolder.hpp>
#include <utils/ResourceIdentifiers.hpp>
#include <vector>

namespace sm
{
	class Waypoint : public sf::Drawable
	{
	public:
		Waypoint(const TextureHolder & textures);
		~Waypoint() = default;

	public:
		void update(sf::Sprite & sprite, const float & speed, double dt);
		void add(const sf::Vector2i & position);
		void remove(const sf::Vector2i & position);
		void reset();
		void clear();

	public:
		virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

	private:
		std::vector<sf::Sprite> m_waypoints;
		const TextureHolder & m_textures;
		unsigned int m_currentIndex;
	};
}
