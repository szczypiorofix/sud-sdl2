-- ##### DO NOT CHAMGE THIS PART !!! #####
-- Set package pack for ./lua/... for proper loading of Lua scripts
package.path = package.path .. ";../lua/?.lua"
-- #######################################



-- ################ SCRIPT CODE ################

print( "Lua version: ".._VERSION )

-- load 'Core' module
-- Core = require("core.Core")



-- ############ LEVEL ################
-- first level
level = Level:new(
    {
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
    }
)

-- another level
local level2 = Level:new(
    {
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
    }
)

-- assign level2 to global level
level = level2


-- ############ GAME ################
-- game = Game:new("new game")
-- game.name = "new game+"




-- EOF
