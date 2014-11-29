local vector = Vector2f()
vector.x = 10
vector.y = 10

local rectShape = RectangleShape()

function move(key)
	local vecPos = Vector2f()
	
	if key == "W" then
		vecPos.y = vecPos.y - 10
	elseif key == "A" then
		vecPos.x = vecPos.x - 10
		rectShape:setRotation(rectShape:getRotation() + 1)
	elseif key == "S" then
		vecPos.y = vecPos.y + 10
	elseif key == "D" then
		vecPos.x = vecPos.x + 10
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

LuaHandler:hook("eventKeyPressed", "move", move)
LuaHandler:hook("update", "grow", grow)
LuaHandler:hook("draw", "drawRect", drawRect)