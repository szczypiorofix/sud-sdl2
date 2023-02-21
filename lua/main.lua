-- Set package pack for ./lua/...
package.path = package.path .. ";../lua/?.lua"



-- Welcome print
-- print( "Lua version: ".._VERSION.. ". Loading Lua modules ..." )

-- Loading Lua modules
-- Core = require("core.Core")

-- print("main.lua loaded")


-- TestModel from c++
-- local obj = TestModel(42)
-- print("TestModel - get() = " .. obj:get())    -- 42
-- obj:set(-1.5)
-- print("TestModel - get() = " .. obj:get())    -- -1.5



-- calling C/C++ functions
-- sprite = CreateSprite()
-- MoveSprite(sprite, 2, 5)




-- Vector2D

v1 = CreateVector()   -- v1 is a table
v2 = CreateVector()	  -- v2 is a table
v1.x = 11
v2.x = 42
v3 = v1 + v2
result = v3.x



-- EOF