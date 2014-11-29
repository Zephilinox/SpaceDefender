#ifndef LUASFMLWRAPPERS_HPP_INCLUDED
#define LUASFMLWRAPPERS_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <LuaBridge/luabridge.h>
#include <Thor/Input.hpp>

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

    void setFillColor(sf::Color col) {m_shape.setFillColor(col);}
    sf::Color getFillColor() {return m_shape.getFillColor();}

private:
    sf::RectangleShape m_shape;
};

class LuaWindow
{
public:
    LuaWindow(sf::RenderWindow* window) {m_window = window;}
    operator sf::RenderWindow&() {return *m_window;}

    LuaVector2f getSize() {return sf::Vector2f(m_window->getSize());}

private:
    sf::RenderWindow* m_window;
};

class LuaInput
{
public:
    bool isKeyPressed(std::string key)
    {
        return sf::Keyboard::isKeyPressed(thor::toKeyboardKey(key));
    }

    bool isMousePressed(std::string mouseButton)
    {
        return sf::Mouse::isButtonPressed(thor::toMouseButton(mouseButton));
    }
};

void registerLuaSFMLWrappers(lua_State* L)
{
    luabridge::getGlobalNamespace(L).
        beginClass<LuaVector2f>("Vector2f").
            addConstructor<void(*)(float, float)>().
            addProperty("x", &LuaVector2f::getX, &LuaVector2f::setX).
            addProperty("y", &LuaVector2f::getY, &LuaVector2f::setY).
            addFunction("__add", &LuaVector2f::operator+).
            addFunction("__sub", &LuaVector2f::operator+).
        endClass().
        beginClass<sf::Color>("Color").
            addConstructor<void(*)(int, int, int, int)>().
            addData("r", &sf::Color::r).
            addData("g", &sf::Color::g).
            addData("b", &sf::Color::b).
            addData("a", &sf::Color::a).
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
        endClass().
        beginClass<LuaWindow>("Window").
            addFunction("getSize", &LuaWindow::getSize).
        endClass().
        beginClass<LuaInput>("Input").
            addFunction("isKeyPressed", &LuaInput::isKeyPressed).
            addFunction("isMousePressed", &LuaInput::isMousePressed).
        endClass();

    //Push classes for lua access
    LuaInput luaInput;
    luabridge::push(L, luaInput);
    lua_setglobal(L, "Input");
}

#endif //LUASFMLWRAPPERS_HPP_INCLUDED
