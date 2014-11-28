#include "SpaceDefenders.hpp"

SpaceDefenders::SpaceDefenders()
{
    m_window.create(sf::VideoMode(1280, 720, 32), "Space Defenders");
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

}

void SpaceDefenders::draw()
{
    m_window.clear(sf::Color(40, 40, 40));
    m_window.display();
}
