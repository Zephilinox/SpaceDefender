local selflet = {}
selflet.__index = selflet

function selflet.new(pos, vel)
	local self = {}
	setmetatable(self, selflet)
	
	self.shape = RectangleShape()
	self.shape:setFillColor(Color(255, 50, 50, 255))
	self.shape:setSize(Vector2f(20, 2))
	self.shape:setOrigin(Vector2f(0, 1))
	self.shape:setRotation(vel:degrees())
	self.shape:setPosition(pos)
	
	self.velocity = Vector2f(-vel.x, -vel.y)
	
	self.alive = true
	
	return self
end

function selflet:update(dt)
	self:move(dt)
	self:visible()
end

function selflet:draw()
	Window:drawShape(self.shape)
end

function selflet:visible()
	local winSize = Window:getSize()
	local pos = self.shape:getPosition()
	
	if pos.x < 0 then
		self.alive = false
	elseif pos.x > winSize.x then
		self.alive = false
	elseif pos.y < 0 then
		self.alive = false
	elseif pos.y > winSize.y then
		self.alive = false
	end
end

function selflet:move(dt)
	local vel = Vector2f(self.velocity.x, self.velocity.y)
	vel.x = vel.x * dt
	vel.y = vel.y * dt
	self.shape:setPosition(self.shape:getPosition() + vel)
end

return selflet