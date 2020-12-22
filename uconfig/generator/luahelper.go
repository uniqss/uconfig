package generator

import lua "github.com/yuin/gopher-lua"

func Array2LuaTable2(L *lua.LState, array [][]string) *lua.LTable {
	luaTable := L.NewTable()
	for _, row := range array {
		luaTableRow := L.NewTable()
		for _, col := range row {
			luaTableRow.Append(lua.LString(col))
		}
		luaTable.Append(luaTableRow)
	}

	return luaTable
}

func Array2LuaTable1(L *lua.LState, array []string) *lua.LTable {
	luaTable := L.NewTable()
	for _, row := range array {
		luaTable.Append(lua.LString(row))
	}

	return luaTable
}
