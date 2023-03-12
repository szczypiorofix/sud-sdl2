-- ##### DO NOT CHANGE THIS PART !!! #####
-- Set package pack for ./lua/... for proper loading of Lua scripts
package.path = package.path .. ";../lua/?.lua"
-- #######################################



-- ################ SCRIPT CODE ################

print( "Lua version: ".._VERSION )

-- load 'Game' module
Game = require("Game")

game = Game



pod = function( self )
    print("Calling OnDraw function")
    print( self.name )
end


player = Player:new({
    name = "Gracz 1",
    x = 3,
    y = 12,
    width = 160,
    height = 200,
    OnDraw = function(self)
        print("Calling OnDraw function")
        print( self.name )
    end
})

-- print(player.OnDraw)

-- player.OnDraw = pod

-- player.OnDraw = function( self )
--     print( self.name )
-- end


-- print(player)

-- print(player.OnDraw)
