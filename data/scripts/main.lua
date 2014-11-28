local vector = Vector2f()
vector.x = 10
vector.y = 10

local rectShape = RectangleShape()

function grow(dt)
	vector.x = vector.x + (100 * dt)
	rectShape.size = vector
	rectShape.position = vector
end

function drawRect()
	return rectShape
end

LuaHandler:hook("tick", "grow", grow)
LuaHandler:hook("draw", "drawRect", drawRect)