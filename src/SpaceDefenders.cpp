#include "SpaceDefenders.hpp"

SpaceDefenders::SpaceDefenders()
{
    m_window.create(sf::VideoMode(1280, 720, 32), "Space Defenders");

    m_luaHandler.loadFile("data/scripts/main.lua");
    m_luaHandler.execute();
}

void SpaceDefenders::run()
{
    gameLoop();
}

void SpaceDefenders::gameLoop()
{
    sf::Event e;
    sf::Clock frameClock;
    sf::Time prevFrameTime = sf::seconds(1.f/60.f);

    while (m_window.isOpen())
    {
        while (m_window.pollEvent(e))
        {
            handleEvent(e);
        }

        update(prevFrameTime.asSeconds());
        draw();
    }
}

void SpaceDefenders::handleEvent(const sf::Event& e)
{
    switch (e.type)
    {
        case sf::Event::Closed:
        {
            m_window.close();
        } break;

        default:
        {

        } break;
    }

}

void SpaceDefenders::update(float dt)
{
    for (auto& func : m_luaHandler.getHookFunctions("tick"))
    {
        func();
    }
}

void SpaceDefenders::draw()
{
    m_window.clear(sf::Color(40, 40, 40));
    m_window.display();
}
