local collisionManager = {}
local bullet = require("data/scripts/bullet")
local asteroid = require("data/scripts/asteroid")

collisionManager.__index = collisionManager

function collisionManager.new(asteroids, bullets, earth, player)
	local self = {}
	setmetatable(self, collisionManager)
	
	self.asteroids = asteroids
	self.bullets = bullets
	self.earth = earth
	self.player = player
	
	return self
end

function collisionManager:update(dt)
	for k, v in ipairs(self.asteroids) do
		for k1, v2 in ipairs(self.bullets) do
			if v.shape:intersecting(v2.shape) then
				v.alive = false
				v2.alive = false
				self.player.score = self.player.score + 1
			end
		end
		
		if v.shape:intersecting(self.earth.shape) then
			v.alive = false
			self.earth.health = self.earth.health - 1
			self.earth:update()
		end
	end
end

return collisionManager