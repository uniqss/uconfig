function PrintTable2(table)
    for rowidx, row in ipairs(table) do
        for colidx, col in ipairs(row) do
            print("lua["..rowidx..","..colidx.."] type(col):"..type(col).." col:"..col)
        end
    end
end
function PrintTable1(table)
    for rowidx, row in ipairs(table) do
        print("lua["..rowidx.."] type(row):"..type(row).." row:"..row)
    end
end

function ProcessOneSheet(dir, outputCodeDir, outputDataDir, sheetName, table)
    print("dir:" .. dir)
    print("outputCodeDir:" .. outputCodeDir)
    print("outputDataDir:" .. outputDataDir)
    print("sheetName:" .. sheetName)

    PrintTable2(table)

    return 3 + 4
end

function BeforeProcess(dir, outputCodeDir, outputDataDir, fileNames, sheetNames)
    print("BeforeProcess dir:"..dir.." outputCodeDir:"..outputCodeDir.." outputDataDir:"..outputDataDir)
    PrintTable1(fileNames)
    PrintTable1(sheetNames)
end

function AfterProcess(dir, outputCodeDir, outputDataDir, fileNames, sheetNames)
    print("AfterProcess dir:"..dir.." outputCodeDir:"..outputCodeDir.." outputDataDir:"..outputDataDir)
    PrintTable1(fileNames)
    PrintTable1(sheetNames)
end
