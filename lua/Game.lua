level = require("level")

local game = Game:new("new game")
game.name = "new game+"
game.level = level

game:init(
    {
        windowWidth = 1360,
        windowHeight = 768,
        amountOfTicks = 60,
        fullScreen = false,
        fpsCap = true,
        vsync = true
    }
)

return game
