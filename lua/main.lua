-- ##### DO NOT CHAMGE THIS PART !!! #####
-- Set package pack for ./lua/... for proper loading of Lua scripts
package.path = package.path .. ";../lua/?.lua"
-- #######################################



-- ################ SCRIPT CODE ################

print( "Lua version: ".._VERSION )

-- load 'Core' module
-- Core = require("core.Core")



-- ############ LEVEL ################
level1 = Level:new({
    name = "level_01",
    width = 12,
    height = 8,
    background = "############"
                .. "#..........#"
                .. "#..........#"
                .. "###...#....#"
                .. "#..........#"
                .. "#..........#"
                .. "#..........#"
                .. "############",
    foreground = "            "
                .. "            "
                .. "    T       "
                .. "            "
                .. "    tT T    "
                .. "   Tt       "
                .. "            "
                .. "            "
})

-- another level
local level2 = Level:new({
    name = "level_02",
    width = 30,
    height = 10,
    background = "##############################"
                .."#............................#"
                .."#............................#"
                .."#............................#"
                .."#............................#"
                .."#.......................###..#"
                .."#.......................#.#..#"
                .."#.......................###..#"
                .."#............................#"
                .."##############################",
    foreground = "                              "
                .."                              "
                .."       tT                     "
                .."         Tt  tT TTTT          "
                .."          tT                  "
                .."             tt               "
                .."                              "
                .."                              "
                .."                              "
                .."                              "
})



-- ############ GAME ################
game = Game:new("new game")
game.name = "new game+"

game.level = level1 -- assign level1 or level2

-- x = game.level
-- print(x)

