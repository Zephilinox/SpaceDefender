local player = require("data/scripts/player").new()
local level = require("data/scripts/level").new()
local earth = require("data/scripts/earth").new()
local collisionManager = require("data/scripts/collisionManager").new(level:getAsteroids(), player:getGun():getBullets(), earth, player)

local state = "Playing"
local text = Text(FontDejavu)
text:setPosition(Vector2f(Window:getSize().x/2 - 400, Window:getSize().y/2 - 32))

function handleKeyPressed(key)
	if state == "Playing" then
		player:handleKeyPressed(key)
	elseif key == "R" then
		player = require("data/scripts/player").new()
		level = require("data/scripts/level").new()
		earth = require("data/scripts/earth").new()
		collisionManager = require("data/scripts/collisionManager").new(level:getAsteroids(), player:getGun():getBullets(), earth, player)
		state = "Playing"
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
	else
		text.string = "Game Over! Press R to restart. You destroyed " .. tostring(player.score) .. " asteroids!"
	end
end

function draw()	
	if state == "Playing" then
		earth:draw()
		player:draw()
		level:draw()
	else
		Window:drawText(text)
	end
end

LuaHandler:hook("eventKeyPressed", "mainKeyPressed", handleKeyPressed)
LuaHandler:hook("eventKeyReleased", "mainKeyReleased", handleKeyReleased)
LuaHandler:hook("update", "mainUpdate", update)
LuaHandler:hook("draw", "mainDraw", draw)