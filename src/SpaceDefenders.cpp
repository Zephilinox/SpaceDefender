#include "SpaceDefenders.hpp"

#include <iostream>

#include "LuaSFMLWrappers.hpp"

SpaceDefenders::SpaceDefenders()
{
    m_window.create(sf::VideoMode(1280, 720, 32), "Space Defenders");

    //Register C++
    registerLuaSFMLWrappers(m_luaHandler.getLuaState());

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

        prevFrameTime = frameClock.restart();
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

        case sf::Event::KeyPressed:
        {
            for (auto& func : m_luaHandler.getHookFunctions("eventKeyPressed"))
            {
                func(e);
            }
        } break;

        case sf::Event::KeyReleased:
        {
            for (auto& func : m_luaHandler.getHookFunctions("eventKeyReleased"))
            {
                func(e);
            }
        } break;

        default:
        {

        } break;
    }
}

void SpaceDefenders::update(float dt)
{
    for (auto& func : m_luaHandler.getHookFunctions("update"))
    {
        func(dt);
    }
}

void SpaceDefenders::draw()
{
    m_window.clear(sf::Color(40, 40, 40));

    for (auto& func : m_luaHandler.getHookFunctions("draw"))
    {
        m_window.draw(func().cast<LuaRectangleShape>());
    }

    m_window.display();
}
