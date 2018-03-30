#pragma once
#include <utils/ResourceHolder.hpp>
#include <utils/ResourceIdentifiers.hpp>
#include <memory>

namespace sm
{
	class Waypoint;

	class Application
	{
	public:
		Application();
		~Application();

	public:
		void run();
		void shutdown();
		
	private:
		void loadObjects();
		void loadTextures();
		void render();
		void processEvents();
		void update();
		void updateGUI();
		void reset();

	private:
		sf::RenderWindow m_window;
		TextureHolder m_textures;
		sf::Sprite m_agent;

	private:
		std::unique_ptr<Waypoint> m_waypoints;
	};
}
