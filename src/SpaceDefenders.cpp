#include "SpaceDefenders.hpp"

#include <iostream>

#include <Thor/Input.hpp>

#include "LuaSFMLWrappers.hpp"

SpaceDefenders::SpaceDefenders()
{
    m_window.create(sf::VideoMode(1280, 720, 32), "Space Defenders");

    reloadLua();
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
        if (m_fpsDelay.getElapsedTime() > sf::seconds(1))
        {
            m_fpsDelay.restart();
            std::cout << "FPS: " << 1.f / prevFrameTime.asSeconds() << "\n";
        }
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
            if (e.key.code == sf::Keyboard::F12)
            {
                reloadLua();
            }

            for (auto& func : m_luaHandler->getHookFunctions("eventKeyPressed"))
            {
                if (func.second.isNil())
                {
                    func.first(thor::toString(e.key.code));
                }
                else
                {
                    func.first(func.second, thor::toString(e.key.code));
                }
            }
        } break;

        case sf::Event::KeyReleased:
        {
            for (auto& func : m_luaHandler->getHookFunctions("eventKeyReleased"))
            {
                if (func.second.isNil())
                {
                    func.first(thor::toString(e.key.code));
                }
                else
                {
                    func.first(func.second, thor::toString(e.key.code));
                }
            }
        } break;

        default:
        {

        } break;
    }
}

void SpaceDefenders::update(float dt)
{
    for (auto& func : m_luaHandler->getHookFunctions("update"))
    {
        if (func.second.isNil())
        {
            func.first(dt);
        }
        else
        {
            func.first(func.second, dt);
        }
    }
}

void SpaceDefenders::draw()
{
    m_window.clear(sf::Color(40, 40, 40));

    for (auto& func : m_luaHandler->getHookFunctions("draw"))
    {
        if (func.second.isNil())
        {
            func.first();
        }
        else
        {
            func.first(func.second);
        }
    }

    m_window.display();
}

void SpaceDefenders::reloadLua()
{
    m_luaHandler = std::unique_ptr<LuaHandler>(new LuaHandler());

    //Register C++
    registerLuaSFMLWrappers(m_luaHandler->getLuaState());

    //Push window to the lua state for access
    LuaWindow luaWindow(&m_window);
    luabridge::push(m_luaHandler->getLuaState(), luaWindow);
    lua_setglobal(m_luaHandler->getLuaState(), "Window");

    m_luaHandler->loadFile("data/scripts/main.lua");
    m_luaHandler->execute();
}
