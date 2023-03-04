-- ##### DO NOT CHAMGE THIS PART !!! #####
-- Set package pack for ./lua/... for proper loading of Lua scripts
package.path = package.path .. ";../lua/?.lua"
-- #######################################


-- ################ SCRIPT CODE ################

print( "Lua version: ".._VERSION )

-- load 'Core' module
-- Core = require("core.Core")




-- ############ LEVEL ################
level = Level:new(
    {
        name = "level_01",
        width = 12,
        height = 6,
        content = "############"
               .. "#..........#"
               .. "#..........#"
               .. "#..........#"
               .. "#..........#"
               .. "############"
    }
)


-- level.name = "level_001"
-- level.width = 12
-- level.height = 6
-- level.content = "############"
-- .. "#..........#"
-- .. "#..........#"
-- .. "#..........#"
-- .. "#..........#"
-- .. "############"



-- ############ GAME ################
game = Game:new("new game")

game.level = level


print("LUA GAME->LEVEL")
print(game.level.width)


-- game.level = level
-- game.name = "new game+"

-- print(level.content)


-- EOF
