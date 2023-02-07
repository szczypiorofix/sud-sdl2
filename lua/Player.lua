GameObject = require("GameObject")

local Player = {}

function Player:new()
    Player = {
        name = "Default name",
        x = 10,
        y = 12
    }

    function Player:setName( _name )
        Player.name = _name
    end

    function Player:printName()
        print("Player name "..p.name)
    end

    setmetatable(Player, self)
    self._index = self
    return Player
end

return Player
