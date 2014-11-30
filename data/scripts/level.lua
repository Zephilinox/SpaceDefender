local level = {}
local asteroid = require("data/scripts/asteroid")

level.__index = level

function level.new()
	local lev = {}
	setmetatable(lev, level)
	
	lev.asteroids = {}
	lev.spawnClock = Clock()
	
	for i = 0, 16, 1 do
		lev:spawnAsteroid()
	end
	
	return lev
end

function level:update(dt)
	for k, v in ipairs(self.asteroids) do
		v:update(dt)
	end
	
	if self.spawnClock:seconds() > 1 then
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
	local diff = Vector2f(pos.x - center.x, pos.y - center.y)
	local dir = Math:normalise(diff)
	dir.x = dir.x * -100
	dir.y = dir.y * -100
	
	self.asteroids[#self.asteroids + 1] = asteroid.new(pos, dir)
end

return level