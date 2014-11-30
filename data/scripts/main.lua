local player = require("data/scripts/player")
local level = require("data/scripts/level").new()
local earth = require("data/scripts/earth").new()
local collisionManager = require("data/scripts/collisionManager").new(level:getAsteroids(), player:getGun():getBullets(), earth)

local state = "Playing"

function handleKeyPressed(key)
	if state == "Playing" then
		player:handleKeyPressed(key)
	end
end

function handleKeyReleased(key)
	if state == "Playing" then
		player:handleKeyReleased(key)
	end
end

function update(dt)
	if state == "Playing" then
		player:update(dt)
		level:update(dt)
		collisionManager:update()
		
		if earth.health <= 0 then
			state = "GameOver"
		end
	end
end

function draw()
	if state == "Playing" then
		earth:draw()
		player:draw()
		level:draw()
	end
end

LuaHandler:hook("eventKeyPressed", "mainKeyPressed", handleKeyPressed)
LuaHandler:hook("eventKeyReleased", "mainKeyReleased", handleKeyReleased)
LuaHandler:hook("update", "mainUpdate", update)
LuaHandler:hook("draw", "mainDraw", draw)