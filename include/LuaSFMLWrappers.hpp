#ifndef LUASFMLWRAPPERS_HPP_INCLUDED
#define LUASFMLWRAPPERS_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <LuaBridge/luabridge.h>

class LuaVector2f
{
public:
    LuaVector2f() = default;
    LuaVector2f(sf::Vector2f v2f) {m_vector = v2f;}
    LuaVector2f(float x, float y) {m_vector.x = x; m_vector.y = y;}
    operator sf::Vector2f&() {return m_vector;}
    LuaVector2f operator +(LuaVector2f other) {return LuaVector2f(m_vector.x + other.getX(), m_vector.y + other.getY());}
    LuaVector2f operator -(LuaVector2f other) {return LuaVector2f(m_vector.x - other.getX(), m_vector.y - other.getY());}

    void setX(float x) {m_vector.x = x;}
    void setY(float y) {m_vector.y = y;}

    float getX() const {return m_vector.x;}
    float getY() const {return m_vector.y;}

private:
    sf::Vector2f m_vector;
};

class LuaColor
{
public:
    LuaColor() = default;
    LuaColor(int r, int g, int b, int a)
    {
        m_color.r = r;
        m_color.g = g;
        m_color.b = b;
        m_color.a = a;
    };
    LuaColor(sf::Color col) {m_color = col;}
    operator sf::Color&() {return m_color;}


private:
    sf::Color m_color;
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
    LuaVector2f getPosition() const {return LuaVector2f(m_shape.getPosition());}

    void setRotation (float angle) {m_shape.setRotation(angle);}
    float getRotation () const {return m_shape.getRotation();}

    void setFillColor(LuaColor col) {m_shape.setFillColor(col);}
    LuaColor getFillColor() {return m_shape.getFillColor();}

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
            addFunction("__add", &LuaVector2f::operator+).
            addFunction("__sub", &LuaVector2f::operator+).
        endClass().
        beginClass<LuaColor>("Color").
            addConstructor<void(*)(int, int, int, int)>().
        endClass().
        beginClass<LuaRectangleShape>("RectangleShape").
            addConstructor<void(*)(void)>().
            addFunction("setSize", &LuaRectangleShape::setSize).
            addFunction("getSize", &LuaRectangleShape::getSize).
            addFunction("setPosition", &LuaRectangleShape::setPosition).
            addFunction("getPosition", &LuaRectangleShape::getPosition).
            addFunction("setRotation", &LuaRectangleShape::setRotation).
            addFunction("getRotation", &LuaRectangleShape::getRotation).
            addFunction("setFillColor", &LuaRectangleShape::setFillColor).
            addFunction("getFillColor", &LuaRectangleShape::getFillColor).
        endClass();
}

#endif //LUASFMLWRAPPERS_HPP_INCLUDED
