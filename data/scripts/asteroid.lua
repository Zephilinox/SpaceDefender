local asteroid = {}
asteroid.__index = asteroid

function asteroid.new(pos, vel)
	local ast = {}
	setmetatable(ast, asteroid)
	
	ast.shape = RectangleShape()
	ast.shape:setFillColor(Color(100, 50, 0, 255))
	ast.shape:setSize(Vector2f(20, 20))
	ast.shape:setOrigin(Vector2f(10, 10))
	ast.shape:setRotation(vel:degrees())
	ast.shape:setPosition(pos)
	
	ast.velocity = vel	
	
	return ast
end

function asteroid:update(dt)	
	self:move(dt)
end

function asteroid:draw()	
	Window:draw(self.shape)
end

function asteroid:move(dt)	
	local vel = Vector2f(self.velocity.x, self.velocity.y)
	vel.x = vel.x * dt
	vel.y = vel.y * dt
	self.shape:setPosition(self.shape:getPosition() + vel)
end

return asteroid