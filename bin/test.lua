local function camelCase(s)
	return string.gsub(s, "_%w+", function(word)
		local first = string.sub(word, 2, 2)
		local rest = string.sub(word, 3)
		return string.upper(first) .. rest
	end)
end
local function CamelCase(s)
    local camel = camelCase(s)
    print("camel:"..camel)
    return (camel:gsub("^%l", string.upper))
end

local function transType(ctype)
    if ctype == "uint32" then
        return "uint32"
    elseif ctype == "string" then
        return "string"
    elseif ctype == "repeated string" then
        return "[]string"
    elseif ctype == "repeated uint32" then
        return "[]uint32"
    end
end

str = "snake_case_hello_world_123_haha"

camel = CamelCase(str)
print(camel)

--[[
snake = snake_case(camel)
print(snake)
--]]

print(transType("uint32"))
print(transType("string"))
print(transType("repeated string"))
print(transType("repeated uint32"))

local file = nil
local function func2()
    file:write("fuck", "\n")
end
local function localFunc()
    file = io.open("./fuck.txt", "w+")
    func2()
    io.close(file)
end

--- Check if a file or directory exists in this path
function exists(file)
    local ok, err, code = os.rename(file, file)
    if not ok then
        if code == 13 then
            -- Permission denied, but it exists
            return true
        end
    end
    return ok, err
end
--- Check if a directory exists in this path
function isdir(path)
    -- "/" works on both Unix and Windows
    return exists(path.."/")
end
function createDirIfNotExists(path)
    if isdir(path) then
        return
    end
    os.execute("mkdir " .. path)
end

function file_exists(path)
    local file = io.open(path, "rb")
    if file then file:close() end
    return file ~= nil
end

local fexist = isdir("./xxx/")

print(fexist)

fexist = isdir("../cppcalllua_exe")
print(fexist)
