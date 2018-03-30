#include <graphics/Application.hpp>
#include <graphics/Waypoint.hpp>
#include <utils/Utility.hpp>
#include <imgui.h>
#include <imgui-SFML.h>

#define WIDTH 1400U
#define HEIGHT 900U

namespace sm
{
	static bool g_isPlaying = false;
	static bool g_isReset = false;
	static bool g_isGUIHoovered = false;

	Application::Application() : m_window(sf::VideoMode(WIDTH, HEIGHT), "Techniques", sf::Style::Close)
	{
		m_window.setVerticalSyncEnabled(true);

		//Init ImGUI
		ImGui::SFML::Init(m_window);
		ImGui::StyleColorsDark();

		//Load resources
		loadObjects();
		loadTextures();

		//Init agent
		m_agent.setPosition(sf::Vector2f((WIDTH / 2.f - 25.f), HEIGHT - 100.f));
		m_agent.setTexture(m_textures.getResource(Textures::ID::Agent));
		m_agent.setScale(sf::Vector2f(0.6f, 0.6f));
		utils::centerOrigin(m_agent);
	}

	Application::~Application() = default;

	void Application::loadObjects()
	{
		m_waypoints = std::make_unique<Waypoint>(m_textures);
	}

	void Application::loadTextures()
	{
		m_textures.loadResource(Textures::ID::Agent, "src/res/sprites/agent.png");
		m_textures.loadResource(Textures::ID::Waypoint, "src/res/sprites/waypoint.png");
	}

	void Application::run()
	{
		sf::Clock guiClock;
		while (m_window.isOpen())
		{
			processEvents();
			update();
			ImGui::SFML::Update(m_window, guiClock.restart());
			updateGUI();
			render();		
		}
	}

	void Application::shutdown()
	{
		ImGui::SFML::Shutdown();
	}

	void Application::render()
	{
		m_window.clear();

		//Draw techniques
		m_window.draw(*m_waypoints.get());

		m_window.draw(m_agent);
		ImGui::SFML::Render(m_window);
		m_window.display();
	}

	void Application::processEvents()
	{
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
				m_window.close();

			//Add waypoints on left-click
			if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left)
			{
				if(!g_isGUIHoovered && !g_isPlaying)
					m_waypoints->add(sf::Mouse::getPosition(m_window));
			}

			//Remove waypoints on right-click
			if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Right)
			{
				if(!g_isGUIHoovered && !g_isPlaying)
					m_waypoints->remove(sf::Mouse::getPosition(m_window));
			}
		}
	}

	void Application::update()
	{
		//Update techniques
		if(g_isPlaying)
			m_waypoints->update(m_agent, 30.f, static_cast<float>(1 / 60.f));
	}

	void Application::updateGUI()
	{
		ImGui::Begin("Settings", NULL, ImVec2(0, 0), 1.f);
		g_isGUIHoovered = ImGui::IsWindowHovered();
		ImGui::Text("Techniques: ");
		ImGui::Spacing();
		ImGui::Separator();
		ImGui::Checkbox("Play", &g_isPlaying);
		ImGui::Spacing();
		if (ImGui::Button("Reset"))
		{
			reset();
		}
		ImGui::SameLine();
		if (ImGui::Button("Clear"))
		{
			reset();
			m_waypoints->clear();
		}

		//Description of the technique
		ImGui::Separator();
		ImGui::Spacing();
		ImGui::TextWrapped("Waypoints can be used as position targets for an agent.");
		ImGui::Text("\nControls:");
		ImGui::BulletText("Left-click to add.");
		ImGui::BulletText("Right-click to remove.");
		ImGui::End();
	}

	void Application::reset()
	{
		//Reset the agent and current technique
		g_isPlaying = false;
		m_agent.setPosition(sf::Vector2f((WIDTH / 2.f - 25.f), HEIGHT - 100.f));
		m_agent.setRotation(0);
		m_waypoints->reset();
	}
}