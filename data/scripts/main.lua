local player = require("data/scripts/player")

function handleKeyPressed(key)
	player:handleKeyPressed(key)
end

function handleKeyReleased(key)
	player:handleKeyReleased(key)
end

function update(dt)
	player:update(dt)
end

function draw()
	player:draw()
end

LuaHandler:hook("eventKeyPressed", "mainKeyPressed", handleKeyPressed)
LuaHandler:hook("eventKeyReleased", "mainKeyReleased", handleKeyReleased)
LuaHandler:hook("update", "mainUpdate", update)
LuaHandler:hook("draw", "mainDraw", draw)