function hello()
	print("Hello World")
end

LuaHandler:hook("tick", "Hello", hello)