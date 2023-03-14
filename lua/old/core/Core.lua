local Core = {}

-- MetaCore = {}
Core.__indes = Core

function Core.new(name)
    local instance = setmetatable({}, Core)
    instance.name = name
    return instance
end

print("Core object loaded...")

return Core
