local collisionManager = {}
local bullet = require("data/scripts/bullet")
local asteroid = require("data/scripts/asteroid")

collisionManager.__index = collisionManager

function collisionManager.new(asteroids, bullets)
	local col = {}
	setmetatable(col, collisionManager)
	
	col.asteroids = asteroids
	col.bullets = bullets
	
	return col
end

function collisionManager:update(dt)
	for k, v in ipairs(self.asteroids) do
		for k1, v2 in ipairs(self.bullets) do
			if v.shape:intersecting(v2.shape) then
				v.alive = false
				v2.alive = false
			end
		end
	end
end

return collisionManager