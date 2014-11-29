#include "LuaHandler.hpp"

#include <iostream>

#include "Utility.hpp"

LuaHandler::LuaHandler()
{
    //Setup lua state
    m_luaState = luaL_newstate();
    luaL_openlibs(m_luaState);
    lua_pushcfunction(m_luaState, traceback);

    //Tell lua about this class
    luabridge::getGlobalNamespace(getLuaState()).
        beginClass<LuaHandler>("LuaHandler").
            addFunction("hook", &LuaHandler::hook).
        endClass();

    //Push this class to the lua state for access
    luabridge::push(m_luaState, this);
    lua_setglobal(m_luaState, "LuaHandler");

    //Create events
    m_hooks["invalid"];
    m_hooks["eventKeyPressed"];
    m_hooks["eventKeyReleased"];
    m_hooks["update"];
    m_hooks["draw"];
}

bool LuaHandler::hook(std::string eventName, std::string uniqueFuncName, luabridge::LuaRef luaFunc)
{
    if (m_hooks.count(eventName))
    {
        if (luaFunc.isFunction())
        {
            m_hooks[eventName].push_back(luaFunc);
            std::cout << "Succeeded in hooking " << uniqueFuncName << " to " << eventName << "\n";
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

std::vector<luabridge::LuaRef>& LuaHandler::getHookFunctions(std::string eventName)
{
    if (m_hooks.count(eventName))
    {
        return m_hooks[eventName];
    }
    else
    {
        return m_hooks["invalid"];
    }
}

lua_State* LuaHandler::getLuaState()
{
    return m_luaState;
}

void LuaHandler::loadFile(std::string file)
{
    int error = luaL_loadfile(m_luaState, file.c_str());
    if (error)
    {
        switch (error)
        {
            case LUA_ERRSYNTAX:
            {
                std::cout << "Syntax Error: " << std::string(lua_tostring(m_luaState, -1)) << "\n";
            } break;

            case LUA_ERRFILE:
            {
                std::cout << "Could not find file\n";
            } break;

            default:
            {
                std::cout << "ErrorCode = " << error << "\n";
            } break;
        }
    }
}

void LuaHandler::execute()
{
    int error = lua_pcall(m_luaState, 0, 0, lua_gettop(m_luaState) - 1);
    if (error)
    {
        switch (error)
        {
            case LUA_ERRRUN:
            {
                std::cout << "Runtime Error: " << std::string(lua_tostring(m_luaState, -1)) << "\n";
            } break;

            case LUA_ERRMEM:
            {
                std::cout << "Memory Allocation Error\n";
            } break;

            case LUA_ERRERR:
            {
                std::cout << "Error while running error handler\n";
            } break;

            default:
            {
                std::cout << "ErrorCode" << error<< "\n";
            } break;
        }
    }
}

int LuaHandler::traceback(lua_State* L)
{
	const char *msg = lua_tostring(L, 1);
	//fprintf(stderr, "Traceback msg: %s\n", msg); //cout breaks function
	if (msg)
	{
		luaL_traceback(L, L, msg, 1);
	}
	else if (!lua_isnoneornil(L, 1))
	{
		if (!luaL_callmeta(L, 1, "__tostring"))
		{
			lua_pushliteral(L, "(no error message)");
		}
	}

    return 1;
}
