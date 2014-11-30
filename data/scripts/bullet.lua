local bullet = {}
bullet.__index = bullet

function bullet.new(pos, vel)
	local bul = {}
	setmetatable(bul, bullet)
	
	bul.shape = RectangleShape()
	bul.shape:setFillColor(Color(255, 50, 50, 255))
	bul.shape:setSize(Vector2f(20, 2))
	bul.shape:setOrigin(Vector2f(0, 1))
	bul.velocity = Vector2f(0, 0)
	
	bul.shape:setPosition(pos)
	bul.shape:setRotation(vel:degrees())
	bul.velocity = Vector2f(-vel.x, -vel.y)
	
	return bul	
end

function bullet:visible()
	local winSize = Window:getSize()
	local pos = self.shape:getPosition()
	
	if pos.x < 0 then
		return false
	elseif pos.x > winSize.x then
		return false
	elseif pos.y < 0 then
		return false
	elseif pos.y > winSize.y then
		return false
	else
		return true
	end
end

function bullet:move(dt)
	local vel = Vector2f(self.velocity.x, self.velocity.y)
	vel.x = vel.x * dt
	vel.y = vel.y * dt
	self.shape:setPosition(self.shape:getPosition() + vel)
end

function bullet:draw()
	Window:draw(self.shape)
end

return bullet