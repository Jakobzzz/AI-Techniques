#pragma once
#include <SFML/Graphics.hpp>

namespace Textures
{
	enum class ID
	{
		Agent,
		Waypoint
	};
}

namespace Fonts
{
	enum class ID
	{
		Main
	};
}

//Forward declaration and a few type definitions
namespace sm
{
	namespace utils
	{
		template <typename Resource, typename Identifier>
		class ResourceHolder;
	}
}

using TextureHolder = sm::utils::ResourceHolder<sf::Texture, Textures::ID>;
using FontHolder = sm::utils::ResourceHolder<sf::Font, Fonts::ID>;