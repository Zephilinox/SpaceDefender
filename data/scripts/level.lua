local level = {}
local asteroid = require("data/scripts/asteroid")

level.__index = level

function level.new()
	local self = {}
	setmetatable(self, level)
	
	self.asteroids = {}
	self.spawnClock = Clock()
	
	for i = 0, 16, 1 do
		self:spawnAsteroid()
	end
	
	return self
end

function level:update(dt)
	for k, v in ipairs(self.asteroids) do
		v:update(dt)
		
		if not v.alive then
			table.remove(self.asteroids, k)
		end
	end
	
	if self.spawnClock:seconds() > math.random(0.3, 1) then
		self.spawnClock:restart()
		
		self:spawnAsteroid()
	end
end

function level:draw()
	for k, v in ipairs(self.asteroids) do
		v:draw()
	end
end

function level:spawnAsteroid()
	local degrees = math.random(0, 360)
	local pos = Math:degreesToVector(degrees)
	
	pos.x = pos.x * (Window:getSize().x/2) * math.random(1.5, 2)
	pos.y = pos.y * (Window:getSize().y/2) * math.random(1.5, 2)
	pos.x = pos.x + Window:getSize().x/2
	pos.y = pos.y + Window:getSize().y/2
	
	local center = Vector2f(Window:getSize().x/2, Window:getSize().y/2)
	local dif = Vector2f(pos.x - center.x, pos.y - center.y)
	local dir = Math:normalise(dif)
	dir.x = dir.x * -100
	dir.y = dir.y * -100
	
	self.asteroids[#self.asteroids + 1] = asteroid.new(pos, dir)
end

function level:getAsteroids()
	return self.asteroids
end

return level