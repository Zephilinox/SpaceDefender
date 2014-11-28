#include "LuaHandler.hpp"

#include <iostream>

LuaHandler::LuaHandler()
{
    m_luaState = luaL_newstate();
    luaL_openlibs(m_luaState);
}

bool LuaHandler::hook(std::string eventName, std::string uniqueFuncName, luabridge::LuaRef luaFunc)
{
    if (m_hooks.count(eventName))
    {
        if (luaFunc.isFunction())
        {
            m_hooks[eventName].push_back(luaFunc);
            std::cout << "Succeeded in hooking" << uniqueFuncName << " to " << eventName << "\n";
            return true;
        }
        else
        {
            std::cout << "Failed to hook " << uniqueFuncName << " to " << eventName << " because function is invalid\n";
        }
    }
    else
    {
        std::cout << "Failed to hook " << uniqueFuncName << " to " << eventName << " because event is invalid\n";
    }

    return false;
}

lua_State* LuaHandler::getLuaState()
{
    return m_luaState;
}

std::vector<luabridge::LuaRef>& LuaHandler::getHookFunctions(std::string eventName)
{
    return m_hooks[eventName]; //todo: error check
}
