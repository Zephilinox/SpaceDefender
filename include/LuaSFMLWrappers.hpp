#ifndef LUASFMLWRAPPERS_HPP_INCLUDED
#define LUASFMLWRAPPERS_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <LuaBridge/luabridge.h>
#include <Thor/Input.hpp>
#include <Thor/Vectors.hpp>

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

    float degrees() const
    {
        float degrees = std::atan2(m_vector.y, m_vector.x) * (180.f / 3.141592653);
        if (degrees < 180) degrees += 180;
        return degrees;
    }

    sf::Vector2f getVector() {return m_vector;}

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

    void setOrigin(LuaVector2f origin) {m_shape.setOrigin(origin);}
    LuaVector2f getOrigin() {return m_shape.getOrigin();}

    bool intersecting(LuaRectangleShape other)
    {
        sf::FloatRect boundingBox1(m_shape.getPosition(), m_shape.getSize());
        sf::FloatRect boundingBox2(other.m_shape.getPosition(), other.m_shape.getSize());

        return boundingBox1.intersects(boundingBox2);
    }

private:
    sf::RectangleShape m_shape;
};

class LuaClock
{
public:
    LuaClock() = default;
    operator sf::Clock&() {return m_clock;}

    float restart() {m_clock.restart().asSeconds();}
    float seconds() {return m_clock.getElapsedTime().asSeconds();}

private:
    sf::Clock m_clock;
};

class LuaMath
{
public:
    LuaMath() = default;

    float signedAngle(LuaVector2f vec1, LuaVector2f vec2)
    {
        return thor::signedAngle(vec1.getVector(), vec2.getVector());
    }

    float lengthSquared(LuaVector2f vec)
    {
        return (vec.getX()*vec.getX() + vec.getY()*vec.getY());
    }

    float length(LuaVector2f vec)
    {
        return std::sqrt(lengthSquared(vec));
    }

    LuaVector2f normalise(LuaVector2f vec)
    {
        float lenSqr = lengthSquared(vec);
        if (lenSqr != 0)
        {
            float len = length(vec);
            return LuaVector2f(vec.getX() / len, vec.getY() / len);
        }

        return LuaVector2f(0, 0);
    }

    LuaVector2f degreesToVector(float degrees)
    {
        float rad = degrees * (3.141592653f / 180.f);
        LuaVector2f vec = LuaVector2f(std::sin(rad), -std::cos(rad));
        return vec;
    }
};

class LuaFont
{
public:
    LuaFont() = default;

    operator sf::Font&() {return *font;}

    sf::Font* font;
};

class LuaText
{
public:
    LuaText(LuaFont font)
    {
        m_text.setFont(font);
    }

    operator sf::Text&() {return m_text;}

    void setString(std::string str) {m_text.setString(str);}
    std::string getString() const {return m_text.getString();}

    void setPosition(LuaVector2f vec) {m_text.setPosition(vec);}
    LuaVector2f getPosition() {return m_text.getPosition();}

private:
    sf::Text m_text;

};

class LuaWindow
{
public:
    LuaWindow(sf::RenderWindow* window) {m_window = window;}
    operator sf::RenderWindow&() {return *m_window;}
    void drawShape(LuaRectangleShape& shape) {m_window->draw(shape);}
    void drawText(LuaText& text) {m_window->draw(text);}

    LuaVector2f getSize() {return sf::Vector2f(m_window->getSize());}

    sf::RenderWindow* getWindow() {return m_window;}

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

    LuaVector2f getMousePosition(LuaWindow window) {return sf::Vector2f(sf::Mouse::getPosition(*window.getWindow()));}
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
            addFunction("degrees", &LuaVector2f::degrees).
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
            addFunction("setOrigin", &LuaRectangleShape::setOrigin).
            addFunction("getOrigin", &LuaRectangleShape::getOrigin).
            addFunction("intersecting", &LuaRectangleShape::intersecting).
        endClass().
        beginClass<LuaClock>("Clock").
            addConstructor<void(*)(void)>().
            addFunction("restart", &LuaClock::restart).
            addFunction("seconds", &LuaClock::seconds).
        endClass().
        beginClass<LuaFont>("Font").
        endClass().
        beginClass<LuaText>("Text").
            addConstructor<void(*)(LuaFont)>().
            addProperty("string", &LuaText::getString, &LuaText::setString).
            addFunction("setPosition", &LuaText::setPosition).
            addFunction("getPosition", &LuaText::getPosition).
        endClass().
        beginClass<LuaWindow>("Window").
            addFunction("getSize", &LuaWindow::getSize).
            addFunction("drawShape", &LuaWindow::drawShape).
            addFunction("drawText", &LuaWindow::drawText).
        endClass().
        beginClass<LuaInput>("Input").
            addFunction("isKeyPressed", &LuaInput::isKeyPressed).
            addFunction("isMousePressed", &LuaInput::isMousePressed).
            addFunction("getMousePosition", &LuaInput::getMousePosition).
        endClass().
        beginClass<LuaMath>("Math").
            addFunction("signedAngle", &LuaMath::signedAngle).
            addFunction("lengthSquared", &LuaMath::lengthSquared).
            addFunction("length", &LuaMath::length).
            addFunction("normalise", &LuaMath::normalise).
            addFunction("degreesToVector", &LuaMath::degreesToVector).
        endClass();

    //Push classes for lua access
    LuaInput luaInput;
    luabridge::push(L, luaInput);
    lua_setglobal(L, "Input");

    LuaMath luaMath;
    luabridge::push(L, luaMath);
    lua_setglobal(L, "Math");
}

#endif //LUASFMLWRAPPERS_HPP_INCLUDED
