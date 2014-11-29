local vector = Vector2f(0, 0)
vector.x = 10
vector.y = 10

local rectShape = RectangleShape()
rectShape:setFillColor(Color(255, 180, 0, 255))
rectShape:setPosition(Vector2f(Window:getSize().x / 2, Window:getSize().y / 2))

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

	if Keyboard.isKeyPressed("W") then
		vecPos.y = vecPos.y - 100 * dt
	end
	
	if Keyboard.isKeyPressed("A") then
		vecPos.x = vecPos.x - 100 * dt
	end
	
	if Keyboard.isKeyPressed("S") then
		vecPos.y = vecPos.y + 100 * dt
	end
	
	if Keyboard.isKeyPressed("D") then
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
LuaHandler:hook("update", "grow", grow)
LuaHandler:hook("draw", "drawRect", drawRect)