local vector = Vector2f(0, 0)
vector.x = 10
vector.y = 10

local player = {}
player.shape = RectangleShape()
player.shape:setFillColor(Color(255, 180, 0, 255))
player.shape:setPosition(Vector2f(Window:getSize().x / 2, Window:getSize().y / 2))

function player:randomColor()
	if Input:isMousePressed("Left") then
		local newCol = Color(math.random(256)-1, math.random(256)-1, math.random(256)-1, 255)
		player.shape:setFillColor(newCol)
	end
end

function player:rotate(key)
	local rotation = player.shape:getRotation()
	
	if key == "Q" then
		player.shape:setRotation(rotation + 10)
	elseif key == "E" then
		player.shape:setRotation(rotation - 10)
	end
end

function player:move(dt)
	player.shape:setPosition(Input:getMousePosition(Window))
	
	local vecPos = Vector2f(0, 0)

	if Input:isKeyPressed("W") then
		vecPos.y = vecPos.y - 100 * dt
	end
	
	if Input:isKeyPressed("A") then
		vecPos.x = vecPos.x - 100 * dt
	end
	
	if Input:isKeyPressed("S") then
		vecPos.y = vecPos.y + 100 * dt
	end
	
	if Input:isKeyPressed("D") then
		vecPos.x = vecPos.x + 100 * dt
	end

	player.shape:setPosition(player.shape:getPosition() + vecPos)
end

function player:grow(dt)
	vector.x = vector.x + (100 * dt)
	player.shape:setSize(vector)
end

function player:drawRect()
	return player.shape
end

function plain(dt)
	print(dt)
end

LuaHandler:hook("eventKeyPressed", "rotate", player.rotate, player)
LuaHandler:hook("update", "move", player.move, player)
LuaHandler:hook("update", "plain", plain)
LuaHandler:hook("update", "randomColor", player.randomColor, player)
LuaHandler:hook("update", "grow", player.grow, player)
LuaHandler:hook("draw", "drawRect", player.drawRect, player)