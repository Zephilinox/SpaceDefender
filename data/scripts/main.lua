local vector = Vector2f(0, 0)
vector.x = 10
vector.y = 10

local rectShape = RectangleShape()
rectShape:setFillColor(Color(255, 180, 0, 255))
rectShape:setPosition(Vector2f(Window:getSize().x / 2, Window:getSize().y / 2))

function randomColor()
	if Input:isMousePressed("Left") then
		local newCol = Color(math.random(256)-1, math.random(256)-1, math.random(256)-1, 255)
		rectShape:setFillColor(newCol)
	end
end

function rotate(key)
	local rotation = rectShape:getRotation()
	
	if key == "Q" then
		rectShape:setRotation(rotation + 10)
	elseif key == "E" then
		rectShape:setRotation(rotation - 10)
	end
end

function move(dt)
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

	rectShape:setPosition(rectShape:getPosition() + vecPos)
end

function grow(dt)
	vector.x = vector.x + (100 * dt)
	rectShape:setSize(vector)
end

function drawRect()
	return rectShape
end

LuaHandler:hook("eventKeyPressed", "rotate", rotate)
LuaHandler:hook("update", "move", move)
LuaHandler:hook("update", "randomColor", randomColor)
LuaHandler:hook("update", "grow", grow)
LuaHandler:hook("draw", "drawRect", drawRect)