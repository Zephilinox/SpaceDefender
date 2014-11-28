#ifndef LUASFMLWRAPPERS_HPP_INCLUDED
#define LUASFMLWRAPPERS_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <LuaBridge/luabridge.h>

class LuaVector2f
{
public:
    LuaVector2f() = default;
    LuaVector2f(sf::Vector2f v2f) {m_vector = v2f;}
    operator sf::Vector2f&() {return m_vector;}

    void setX(float x) {m_vector.x = x;}
    void setY(float y) {m_vector.y = y;}

    float getX() const {return m_vector.x;}
    float getY() const {return m_vector.y;}

private:
    sf::Vector2f m_vector;
};

class LuaRectangleShape
{
public:
    LuaRectangleShape() = default;
    LuaRectangleShape(sf::RectangleShape shape) {m_shape = shape;}
    operator sf::RectangleShape&() {return m_shape;}

    void setSize(LuaVector2f vecSize) {m_shape.setSize(vecSize);}
    LuaVector2f getSize() const {return LuaVector2f(m_shape.getSize());}

    void setPosition (LuaVector2f vecPos) {m_shape.setPosition(vecPos);}
    LuaVector2f getPosition() const {return LuaVector2f(m_shape.getPosition());} //Can't do shape.position.x because the luaVec returned is const

private:
    sf::RectangleShape m_shape;
};

void registerLuaSFMLWrappers(lua_State* L)
{
    luabridge::getGlobalNamespace(L).
        beginClass<LuaVector2f>("Vector2f").
            addConstructor<void(*)(void)>().
            addProperty("x", &LuaVector2f::getX, &LuaVector2f::setX).
            addProperty("y", &LuaVector2f::getY, &LuaVector2f::setY).
        endClass().
        beginClass<LuaRectangleShape>("RectangleShape").
            addConstructor<void(*)(void)>().
            addProperty("size", &LuaRectangleShape::getSize, &LuaRectangleShape::setSize).
            addProperty("position", &LuaRectangleShape::getPosition, &LuaRectangleShape::setPosition).
        endClass();
}

#endif //LUASFMLWRAPPERS_HPP_INCLUDED
