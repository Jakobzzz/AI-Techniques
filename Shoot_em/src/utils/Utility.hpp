#pragma once
#define _USE_MATH_DEFINES
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <math.h>
#include <assert.h>

namespace sm
{
	namespace utils
	{
		inline float toRadians(const float & degree)
		{
			return static_cast<float>(degree * (M_PI / 180.f));
		}

		inline float toDegrees(const float & radians)
		{
			return static_cast<float>(radians * (180.f / M_PI));
		}

		inline float dot(const sf::Vector2f & a, const sf::Vector2f & b)
		{
			return a.x * b.x + a.y * b.y;
		}

		inline float length(const sf::Vector2f & v)
		{
			return sqrtf(v.x * v.x + v.y * v.y);
		}

		inline sf::Vector2f lerp(const sf::Vector2f & start, const sf::Vector2f & end, const float & alpha)
		{
			return (start * (1 - alpha) + end * alpha);
		}

		inline float lerp(const float & start, const float & end, const float & alpha)
		{
			return (start * (1 - alpha) + end * alpha);
		}

		//Return the angle between a and b in radians
		inline float getAngle(const sf::Vector2f & a, const sf::Vector2f & b)
		{
			return acosf(dot(a, b) / (length(a) * length(b)));
		}

		inline sf::RectangleShape getBoundingRect(const sf::FloatRect & rect)
		{
			sf::RectangleShape shape;
			shape.setPosition(sf::Vector2f(rect.left, rect.top));
			shape.setSize(sf::Vector2f(rect.width, rect.height));
			shape.setFillColor(sf::Color::Transparent);
			shape.setOutlineColor(sf::Color::Green);
			shape.setOutlineThickness(1.f);
			return shape;
		}

		inline sf::Vector2f unitVec(const sf::Vector2f & v)
		{
			assert(v != sf::Vector2f(0.f, 0.f));
			return v / length(v);
		}

		inline void rotateTowards(sf::Sprite & sprite, sf::Vector2f target)
		{
			sf::Vector2f dir = target - sprite.getPosition();
			float angle = atan2f(dir.y, dir.x);
			sprite.setRotation(utils::toDegrees(angle) + 90.f);
		}

		inline void centerOrigin(sf::Sprite & sprite)
		{
			sf::FloatRect bounds = sprite.getLocalBounds();
			sprite.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
		}
	}
}
