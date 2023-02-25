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
-- v1 = CreateVector()   -- v1 is a table
-- v2 = CreateVector()	  -- v2 is a table
-- v1.x = 11
-- v2.x = 22

-- -- v3 = v1 + v2
-- result = v1.x + v2.x

-- res4 = v2.x



-- player = {
--     name = "Gracz1",
--     age = 43
-- }



-- Player = require("Player")

-- todd = Player:new()
-- todd:setName("Todd Howard")
-- -- todd:printName();



-- level01 = {
--     sizeX = 20,
--     sizeY = 32,
--     content = "#########_____######"
-- }



sprite = Sprite:new()
sprite:Move( 5, 7 )
-- sprite:Draw()
-- print(sprite)

sprite2 = Sprite:new()
sprite2:Move( 3, 3 )
sprite2:Move(-1, 2)
-- sprite2:Draw()

-- print(sprite2)





-- EOF