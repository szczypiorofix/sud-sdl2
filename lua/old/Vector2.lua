
local vec2_meta = {
    -- Addition operator overloading
    __add = function( a, b )
        return Vector2(
            a.x + b.x,
            a.y + b.y
        )
    end,

    -- Subtraction operator overloading
    __sub = function( a, b )
        return Vector2(
            a.x - b.x,
            a.y - b.y
        )
    end,

    -- Multiplication operator overloading
    __mul = function( f )
        return Vector2(
            a.x * f,
            a.y * f
        )
    end,

    -- Call Vector2 as a function
    __call = function( self )
        print("Vector2{" .. self.x .. ", " .. self.y .. "}")
    end,

    -- tostring function overloading
    __tostring = function( self )
        return "Vector2 - {".. self.x .. ":" .. self.y .."}"
    end
}

function Vector2(x, y)
    local v = {
        x = x or 0,
        y = y or 0
    }
    setmetatable(v, vec2_meta)
    return v
end

print("Vector2 object loaded")

return Vector2
