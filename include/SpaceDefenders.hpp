#ifndef SPACEDEFENDERS_HPP
#define SPACEDEFENDERS_HPP

#include <SFML/Graphics.hpp>

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
};

#endif //SPACEDEFENDERS_HPP
