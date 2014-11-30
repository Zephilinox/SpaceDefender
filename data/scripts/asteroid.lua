local asteroid = {}
asteroid.__index = asteroid

function asteroid.new(pos, vel)
	local self = {}
	setmetatable(self, asteroid)
	
	self.shape = RectangleShape()
	self.shape:setFillColor(Color(100, 50, 0, 255))
	self.shape:setSize(Vector2f(20, 20))
	self.shape:setOrigin(Vector2f(10, 10))
	self.shape:setRotation(vel:degrees())
	self.shape:setPosition(pos)
	
	self.velocity = vel
	
	self.alive = true
	
	return self
end

function asteroid:update(dt)	
	self:move(dt)
end

function asteroid:draw()	
	Window:drawShape(self.shape)
end

function asteroid:move(dt)	
	local vel = Vector2f(self.velocity.x, self.velocity.y)
	vel.x = vel.x * dt
	vel.y = vel.y * dt
	self.shape:setPosition(self.shape:getPosition() + vel)
end

return asteroid