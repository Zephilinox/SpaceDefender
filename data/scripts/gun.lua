local gun = {}
local bullet = require("data/scripts/bullet")

gun.__index = gun

function gun.new(pos)
	local g = {}
	setmetatable(g, gun)
	
	g.bullets = {}
	g.pos = pos
	
	return g	
end

function gun:update(dt)
	self:cullBullets()
	
	for k, v in ipairs(self.bullets) do
		v:update(dt)
	end
end

function gun:updatePos(pos)
	self.pos = pos
end

function gun:draw()
	for k, v in ipairs(self.bullets) do
		v:draw()
	end
end

function gun:cullBullets()
	for k, v in ipairs(self.bullets) do
		if v:visible() == false then
			print(#self.bullets)
			table.remove(self.bullets, k)
		end
	end
end

function gun:shoot(target, speed)
	local diff = Vector2f(self.pos.x - target.x, self.pos.y - target.y)
	local norm = Math:normalise(diff)
	local vel = Vector2f(norm.x, norm.y)
	vel.x = vel.x * speed
	vel.y = vel.y * speed
	
	self.bullets[#self.bullets + 1] = bullet.new(self.pos, vel)
end

return gun