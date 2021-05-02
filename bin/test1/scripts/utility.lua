local utility = {}

function utility.PrintTable1(vecDatas)
    print("lua table elements:")
    for tKey, tValue in pairs(vecDatas) do
        print("\t "..tKey.." => "..tValue)
    end
end
function utility.PrintTable2(vecDatas)
    print("lua table elements:"..#vecDatas)
    for i=1,#vecDatas do
        for j=1,#vecDatas[i] do
            print(i..j.." => "..vecDatas[i][j])
        end
    end
end
function utility.tablelength(T)
    local count = 0
    for _ in pairs(T) do count = count + 1 end
    return count
end

local function camelCase(s)
    return string.gsub(s, "_%w+", function(word)
        local first = string.sub(word, 2, 2)
        local rest = string.sub(word, 3)
        return string.upper(first) .. rest
    end)
end
function utility.CamelCase(s)
    local camel = camelCase(s)
    --print("camel:"..camel)
    return (camel:gsub("^%l", string.upper))
end

--- Check if a file or directory exists in this path
local function exists(file)
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
local function isdir(path)
    -- "/" works on both Unix and Windows
    return exists(path.."/")
end
function utility.createDirIfNotExists(path)
    if isdir(path) then
        return
    end
    os.execute("mkdir " .. path)
end

function utility.Split(s, delimiter)
    result = {};
    for match in (s..delimiter):gmatch("(.-)"..delimiter) do
        table.insert(result, match);
    end
    return result;
end

return utility
