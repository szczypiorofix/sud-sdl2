-- ##### DO NOT CHANGE THIS PART !!! #####
-- Set package pack for ./lua/... for proper loading of Lua scripts
package.path = package.path .. ";../lua/?.lua"
-- #######################################



-- ################ SCRIPT CODE ################

print( "Lua version: ".._VERSION )

-- load 'Game' module
Game = require("Game")

game = Game



player = Player:new({
    name = "Gracz 1",
    x = 3,
    y = 12,
    width = 160,
    height = 200
})

-- player.Move( function( self ) 
--         print("player:Move call from Lua!")
--         print(self)
--     end
-- )


