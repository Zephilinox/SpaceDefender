local earth = {}
earth.__index = earth

local maxHealth = 20

function earth.new()
	local self = {}
	setmetatable(self, earth)
	
	self.shape = RectangleShape()
	self.shape:setFillColor(Color(40, 255, 40, 255))
	self.shape:setSize(Vector2f(64, 64))
	self.shape:setOrigin(Vector2f(32, 32))
	self.shape:setPosition(Vector2f(Window:getSize().x/2, Window:getSize().y/2))
	
	self.health = maxHealth
	self.healthText = Text(FontDejavu)
	self.healthText:setPosition(Vector2f(Window:getSize().x - 50, 50))
	self.healthText.string = tostring(self.health)
	
	return self
end

function earth:update()
	local lostColor = (255-40) / maxHealth --subtract 40 as that is the min we want
	
	local col = Color(40,
                      255 - (lostColor * (maxHealth - self.health)),
                      40,
                      255)
	
	self.shape:setFillColor(col)
	print("Health: " .. self.health)
	self.healthText.string = tostring(self.health)
end

function earth:draw()
	Window:drawShape(self.shape)
	Window:drawText(self.healthText)
end

return earth