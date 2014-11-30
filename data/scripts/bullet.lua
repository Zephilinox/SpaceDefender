local bullet = {}
bullet.__index = bullet

function bullet.new(pos, vel)
	local bul = {}
	setmetatable(bul, bullet)
	
	bul.shape = RectangleShape()
	bul.shape:setFillColor(Color(255, 50, 50, 255))
	bul.shape:setSize(Vector2f(100, 10))
	bul.shape:setOrigin(Vector2f(0, 5))
	bul.velocity = Vector2f(0, 0)
	
	bul.shape:setPosition(pos)
	bul.velocity = vel
	
	return bul	
end

function bullet:move(dt)
	local vel = Vector2f(self.velocity.x, self.velocity.y)
	vel.x = vel.x * dt * 10
	vel.y = vel.y * dt * 10
	self.shape:setPosition(self.shape:getPosition() + vel)
end

function bullet:draw()
	Window:draw(self.shape)
end

return bullet