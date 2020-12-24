function PrintTable1(table)
    for rowidx, row in pairs(table) do
        print("lua["..rowidx.."] type(row):"..type(row).." row:"..row)
    end
end

print("fuck")
fuck = {}
for i=1,10 do
    --istr = tostring(i)
    if i % 2 == 0 then
    else
        table.insert(fuck, i)
    end
end

PrintTable1(fuck)

s = "hello_world"
i, j = string.find(s, "hello")
print(i, j)                      --> 1    5
print(string.sub(s, i, j))       --> hello
print(string.sub(s, j + 1))


s = "asdf\"/Ghello_world"
i, j = string.find(s, "\"/G")
print(string.sub(s, j - 1))

local function TrimColumnString(column)
    -- /G前面如果是单引号或者双引号，则/G前面的全部去掉
    -- 尾巴上如果是单引号或者双引号，则去掉
    local ret = column
    _, j = string.find(ret, "\"/G")
    if j ~= nil then
        ret = string.sub(ret, j - 1)
    end
    _, j = string.find(ret, "\'/G")
    if j ~= nil then
        ret = string.sub(ret, j - 1)
    end
    
    local last = string.sub(ret, string.len(ret))
    if last == '\'' or last == '\"' then
        ret = string.sub(ret, 1, -2)
    end
    return ret
end


s = "asdf\"/Ghello_world\'"

local ret = TrimColumnString(s)
print(ret)
