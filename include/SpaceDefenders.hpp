#ifndef SPACEDEFENDERS_HPP
#define SPACEDEFENDERS_HPP

#include <SFML/Graphics.hpp>

#include "LuaHandler.hpp"

class SpaceDefenders
{
public:
    SpaceDefenders();
    void run();

private:
    void gameLoop();

    void handleEvent(const sf::Event& e);
    void update(float dt);
    void draw();

    sf::RenderWindow m_window;

    LuaHandler m_luaHandler;
};

#endif //SPACEDEFENDERS_HPP
