local player = {}
player.shape = RectangleShape()
player.shape:setFillColor(Color(255, 180, 0, 255))
player.shape:setSize(Vector2f(10, 10))
player.shape:setPosition(Vector2f(Window:getSize().x / 2, Window:getSize().y / 2))
player.shape:setOrigin(Vector2f(0, 5))

function player:randomColor()
	if Input:isMousePressed("Left") then
		local newCol = Color(math.random(256)-1, math.random(256)-1, math.random(256)-1, 255)
		self.shape:setFillColor(newCol)
	end
end

function player:rotate(key)
	local rotation = player.shape:getRotation()
	
	if key == "Q" then
		self.shape:setRotation(rotation + 10)
	elseif key == "E" then
		self.shape:setRotation(rotation - 10)
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

function player:grow(dt)
	local vector = self.shape:getSize()
	
	if vector.x < 100 then
		vector.x = vector.x + (100 * dt)
		self.shape:setSize(vector)
	end
end

function player:followMouse(dt)
	local shapePos = self.shape:getPosition()
	local mousePos = Input:getMousePosition(Window)
	local diff = Vector2f(shapePos.x - mousePos.x, shapePos.y - mousePos.y)
	
	self.shape:setRotation(diff:degrees())
end

function player:drawRect()
	return self.shape
end

LuaHandler:hook("eventKeyPressed", "rotate", player.rotate, player)
LuaHandler:hook("update", "move", player.move, player)
LuaHandler:hook("update", "followMouse", player.followMouse, player)
LuaHandler:hook("update", "randomColor", player.randomColor, player)
LuaHandler:hook("update", "grow", player.grow, player)
LuaHandler:hook("draw", "drawRect", player.drawRect, player)