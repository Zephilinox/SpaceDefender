local player = {}
local bullet = require("data/scripts/bullet")

player.shape = RectangleShape()
player.shape:setFillColor(Color(255, 180, 0, 255))
player.shape:setSize(Vector2f(10, 10))
player.shape:setPosition(Vector2f(Window:getSize().x / 2, Window:getSize().y / 2))
player.shape:setOrigin(Vector2f(5, 5))
player.shape:setRotation(350)

player.bullets = {}

function player:randomColor()
	if Input:isMousePressed("Left") then
		local newCol = Color(math.random(256)-1, math.random(256)-1, math.random(256)-1, 255)
		self.shape:setFillColor(newCol)
	end
end

function player:move(dt)	
	local vecPos = Vector2f(0, 0)
	
	for k, v in ipairs(self.bullets) do
		v:move(dt)
	end
	
	if Input:isKeyPressed("W") then
		vecPos.y = vecPos.y - 100 * dt
	end
	
	if Input:isKeyPressed("A") then
		vecPos.x = vecPos.x - 100 * dt
	end
	
	if Input:isKeyPressed("S") then
		vecPos.y = vecPos.y + 100 * dt
	end
	
	if Input:isKeyPressed("D") then
		vecPos.x = vecPos.x + 100 * dt
	end

	self.shape:setPosition(player.shape:getPosition() + vecPos)
end

function player:shoot(dt)
	for k, v in ipairs(self.bullets) do
		if v:visible() == false then
			print(#self.bullets)
			table.remove(self.bullets, k)
		end
	end
	
	if Input:isKeyPressed("Space") then
		print(#self.bullets)
		local shapePos = self.shape:getPosition()
		local mousePos = Input:getMousePosition(Window)
		local diff = Vector2f(shapePos.x - mousePos.x, shapePos.y - mousePos.y)
		diff = Math:normalise(diff)
		diff.x = diff.x * 300
		diff.y = diff.y * 300
		
		self.bullets[#self.bullets + 1] = bullet.new(self.shape:getPosition(), diff)
	end
end

function player:grow(dt)
	local vector = self.shape:getSize()
	
	if vector.x < 40 then
		vector.x = vector.x + (100 * dt)
		self.shape:setSize(vector)
	end
end

function player:followMouse(dt)
	local shapePos = self.shape:getPosition()
	local mousePos = Input:getMousePosition(Window)
	local diff = Vector2f(shapePos.x - mousePos.x, shapePos.y - mousePos.y)
	local targetDeg = diff:degrees()

	self.shape:setRotation(targetDeg)
end

function player:reset(key)
	if key == "F" then
		self.bullets = {}
	end
end

function player:draw()
	for k, v in ipairs(self.bullets) do
		v:draw()
	end
	
	Window:draw(self.shape)
end

LuaHandler:hook("eventKeyPressed", "reset", player.reset, player)
LuaHandler:hook("update", "shoot", player.shoot, player)
LuaHandler:hook("update", "move", player.move, player)
LuaHandler:hook("update", "followMouse", player.followMouse, player)
LuaHandler:hook("update", "randomColor", player.randomColor, player)
LuaHandler:hook("update", "grow", player.grow, player)
LuaHandler:hook("draw", "draw", player.draw, player)

return player