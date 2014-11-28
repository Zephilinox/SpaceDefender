local vector = Vector2f()

function hello()
	vector.x = vector.x + 1
	print("Vector = " .. vector.x .. ", " .. vector.y)
end

LuaHandler:hook("tick", "Hello", hello)