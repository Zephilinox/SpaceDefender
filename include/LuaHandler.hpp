#ifndef LUAHANDLER_HPP
#define LUAHANDLER_HPP

#include <unordered_map>
#include <vector>

#include <Lua5.2/lua.hpp>
#include <LuaBridge/luabridge.h>

class LuaHandler
{
public:
    LuaHandler();

    bool hook(std::string eventName, std::string uniqueFuncName, luabridge::LuaRef luaFunc);
    void loadFile(std::string file);
    void execute();

    lua_State* getLuaState();
    std::vector<luabridge::LuaRef>& getHookFunctions(std::string eventName);

private:
    lua_State* m_luaState;
    std::unordered_map<std::string, std::vector<luabridge::LuaRef>> m_hooks;

    static int traceback(lua_State* L);
};

#endif //LUAHANDLER_HPP
