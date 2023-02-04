local GameObject = {}

function GameObject:new()
    GameObject = {
        x = 0,
        y = 0,
        name = "game_object"
    }
    setmetatable(GameObject, self)
    self._index = self
    return self
end

return GameObject