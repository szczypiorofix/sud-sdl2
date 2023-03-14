-- Set package pack for ./lua/...
package.path = package.path .. ";../lua/?.lua"

-- Welcome print
print( "Lua version: ".._VERSION.. ". Loading Lua modules ..." )

-- Loading modules - start
Player = require("Player")
Vector2 = require("Vector2")
Core = require("core.Core")

print( "Done." )
-- Loading modules - finish


-- Player ...
p = Player:new{}
p:setName("Todd")
p:printName()

-- Vector2
local a = Vector2(10,2)
local b = Vector2( 2, 3)
local c = a + b

print(c)



-- Core
systemCoreL = Core.new("LinuxSystem")
systemCoreW = Core.new("WindowsSystem")

print("systemCoreL = " .. systemCoreL.name)
print("systemCoreW = " .. systemCoreW.name)
