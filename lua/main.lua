-- ##### DO NOT CHANGE THIS PART !!! #####
-- Set package pack for ./lua/... for proper loading of Lua scripts
package.path = package.path .. ";../lua/?.lua"
-- #######################################



-- ################ SCRIPT CODE ################

print( "Lua version: ".._VERSION )

-- load 'Game' module
Game = require("Game")

game = Game

