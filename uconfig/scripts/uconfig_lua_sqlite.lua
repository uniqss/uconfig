local sqliteFilePath = "./sqlite.sql"
local function PrintTable2(sheetDatas)
    for rowidx, row in pairs(sheetDatas) do
        for colidx, col in pairs(row) do
            print("lua["..rowidx..","..colidx.."] type(col):"..type(col).." col:"..col)
        end
    end
end
local function PrintTable1(sheetDatas)
    for rowidx, row in pairs(sheetDatas) do
        print("lua["..rowidx.."] type(row):"..type(row).." row:"..row)
    end
end
local function tablelength(T)
    local count = 0
    for _ in pairs(T) do count = count + 1 end
    return count
end 

local function isempty(s)
    blank = s ~= nil and s:match("%S") ~= nil
    return not blank
end
local function DontGenerateColumn(cellIdx, cellCs)
    return isempty(cellIdx) or isempty(cellCs)
end
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
local function GenData(dir, outputCodeDir, outputDataDir, sheetName, sheetDatas)
    --PrintTable2(sheetDatas)
    --INSERT INTO "DT_Activity_Preview_Config" ("id","function_image","jump_param") VALUES (1,'/Game/Temp/UI/temporary_ui_b3/SuitImg_108.SuitImg_108','/Game/UI/Blueprint/InterfaceBlueprint/Exchange/WB_Exchange.WB_Exchange');
    --INSERT INTO "DT_Activity_Preview_Config" VALUES (1,'/Game/Temp/UI/temporary_ui_b3/SuitImg_108.SuitImg_108','/Game/UI/Blueprint/InterfaceBlueprint/Exchange/WB_Exchange.WB_Exchange');
    local sqlPrefix = "INSERT INTO \""..sheetName.."\" VALUES ("
    local sqlSuffix = ");\n"
    local tableIdx = sheetDatas[1]
    local tableName = sheetDatas[2]
    local tableType = sheetDatas[3]
    local tableCs = sheetDatas[4]
    local countIdx = tablelength(tableIdx)
    local countName = tablelength(tableName)
    local countType = tablelength(tableType)
    local countCs = tablelength(tableCs)
    local count = math.min(countName, countType)
    count = math.min(count, countIdx)
    count = math.min(count, countCs)
    local arrColumns = {}
    local arrColumnTypes = {}

    for idx=1,count do
        local cellIdx = tableIdx[idx]
        local cellName = tableName[idx]
        local cellType = tableType[idx]
        local cellCs = tableCs[idx]
        --print(idx.." cellIdx:"..cellIdx.." cellCs:"..cellCs.." cellType:"..cellType.." type(cellIdx):"..type(cellIdx).." type(cellCs):"..type(cellCs))
        if DontGenerateColumn(cellIdx, cellCs) then
            --print("DontGenerateColumn")
        else
            table.insert(arrColumns, idx)
            if cellType == "uint32" then
                table.insert(arrColumnTypes, "int")
            else
                table.insert(arrColumnTypes, "string")
            end
        end
    end

    PrintTable1(arrColumns)
    PrintTable1(arrColumnTypes)

    file = io.open (sqliteFilePath, "a")
    local rowcount = tablelength(sheetDatas)
    for rowidx=6,rowcount do
        local row = sheetDatas[rowidx]
        local allColEmpty = 1
        local sql = ""
        for key, colidx in pairs(arrColumns) do
            local colEmpty = isempty(row[colidx])
            local cellType = arrColumnTypes[key]
            if not colEmpty then
                allColEmpty = 0
                print("rowidx:"..rowidx.." key:"..key.." colidx:"..colidx.." cellType:"..cellType.." allColEmpty:"..allColEmpty.." row[colidx]:"..row[colidx])
                
                if cellType == "int" then
                    sql = sql..row[colidx]..","
                else
                    sql = sql.."'"..TrimColumnString(row[colidx]).."',"
                end
            else
                print("rowidx:"..rowidx.." key:"..key.." colidx:"..colidx.." cellType:"..cellType.." allColEmpty:"..allColEmpty.." row[colidx]:nil")

                if cellType == "int" then
                    sql = sql.."0,"
                else
                    sql = sql.."'',"
                end
            end
        end

        print("rowidx:"..rowidx.." allColEmpty:"..allColEmpty.." sql:"..sql)

        if allColEmpty == 0 then
            -- delete last ","
            sql = string.sub(sql, 1, -2)
            file:write(sqlPrefix..sql..sqlSuffix)
        end
    end

    file:write("\n")
    
    io.close(file)
end

function ProcessOneSheet(dir, outputCodeDir, outputDataDir, sheetName, sheetDatas)
    print("dir:" .. dir)
    print("outputCodeDir:" .. outputCodeDir)
    print("outputDataDir:" .. outputDataDir)
    print("sheetName:" .. sheetName)

    --PrintTable2(sheetDatas)

    local rowCount = tablelength(sheetDatas)
    if (rowCount < 5) then
        print("row count < 5 sheetName:".. sheetName)
        return 0
    end

    --- CREATE TABLE DT_Activity_Preview_Config ( id INT PRIMARY KEY NOT NULL,function_image TEXT,jump_param TEXT )
    local sql = "CREATE TABLE "..sheetName.." ( "
    --sql = sql.."id INT PRIMARY KEY NOT NULL,function_image TEXT,jump_param TEXT"
    local tableIdx = sheetDatas[1]
    local tableName = sheetDatas[2]
    local tableType = sheetDatas[3]
    local tableCs = sheetDatas[4]
    local countIdx = tablelength(tableIdx)
    local countName = tablelength(tableName)
    local countType = tablelength(tableType)
    local countCs = tablelength(tableCs)
    local count = math.min(countName, countType)
    count = math.min(count, countIdx)
    count = math.min(count, countCs)

    for idx=1,count do
        local cellIdx = tableIdx[idx]
        local cellName = tableName[idx]
        local cellType = tableType[idx]
        local cellCs = tableCs[idx]
        if DontGenerateColumn(cellIdx, cellCs) then
        else
            local sqltype = ""
            if cellType == "uint32" then
                sqltype = "INT"
            else
                sqltype = "TEXT"
            end
            if cellName == "id" then
                sql = sql..""..cellName.." "..sqltype.." PRIMARY KEY NOT NULL"
            else
                sql = sql..""..cellName.." "..sqltype
            end
            sql = sql..","
        end
    end
    
    -- delete last ","
    sql = string.sub(sql, 1, -2)

    sql = sql.." );\n\n"
    file = io.open (sqliteFilePath, "a")
    file:write(sql)
    io.close(file)

    GenData(dir, outputCodeDir, outputDataDir, sheetName, sheetDatas)
end

function BeforeProcess(dir, outputCodeDir, outputDataDir, fileNames, sheetNames)
    print("BeforeProcess dir:"..dir.." outputCodeDir:"..outputCodeDir.." outputDataDir:"..outputDataDir)
    --PrintTable1(fileNames)
    --PrintTable1(sheetNames)
    file = io.open (sqliteFilePath, "w+")
    file:write("-- file begin\n")
    io.close(file)
end

function AfterProcess(dir, outputCodeDir, outputDataDir, fileNames, sheetNames)
    print("AfterProcess dir:"..dir.." outputCodeDir:"..outputCodeDir.." outputDataDir:"..outputDataDir)
    --PrintTable1(fileNames)
    --PrintTable1(sheetNames)
    file = io.open (sqliteFilePath, "a")
    file:write("-- file end\n")
    io.close(file)
end
