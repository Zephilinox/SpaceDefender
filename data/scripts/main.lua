local player = require("data/scripts/player")
local level = require("data/scripts/level").new()
local collisionManager = require("data/scripts/collisionManager").new(level:getAsteroids(), player:getGun():getBullets())

function handleKeyPressed(key)
	player:handleKeyPressed(key)
end

function handleKeyReleased(key)
	player:handleKeyReleased(key)
end

function update(dt)
	player:update(dt)
	level:update(dt)
	collisionManager:update()	
end

function draw()
	player:draw()
	level:draw()
end

LuaHandler:hook("eventKeyPressed", "mainKeyPressed", handleKeyPressed)
LuaHandler:hook("eventKeyReleased", "mainKeyReleased", handleKeyReleased)
LuaHandler:hook("update", "mainUpdate", update)
LuaHandler:hook("draw", "mainDraw", draw)