local player = {}
local gun = require("data/scripts/gun")

player.shape = RectangleShape()
player.shape:setFillColor(Color(255, 180, 0, 255))
player.shape:setSize(Vector2f(24, 32))
player.shape:setPosition(Vector2f(Window:getSize().x / 2, Window:getSize().y / 2))
player.shape:setOrigin(Vector2f(12, 16))

player.gun = gun:new(player.shape:getPosition())

function player:handleKeyPressed(key)
	self:randomColor(key)
end

function player:handleKeyReleased(key)
	self:reset(key)
end

function player:update(dt)
	self.gun:update(dt)
	self.gun:updatePos(self.shape:getPosition())
	
	self:followMouse(dt)
	self:move(dt)
	self:shoot(dt)
end

function player:draw()
	self.gun:draw()
	
	Window:draw(self.shape)
end

function player:randomColor(key)
	if key == "R" then
		self.shape:setFillColor(Color(	math.random(0, 255),
										math.random(0, 255),
										math.random(0, 255),
										255))
	end
end

function player:move(dt)	
	local vecPos = Vector2f(0, 0)
	
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
	if Input:isKeyPressed("Space") then
		local target = Input:getMousePosition(Window)
		local speed = 300;
		
		self.gun:shoot(target, speed)
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
		self.gun = gun:new()
	end
end

return player