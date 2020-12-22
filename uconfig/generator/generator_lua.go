package generator

import (
	log "github.com/sirupsen/logrus"
	"github.com/yuin/gopher-lua"
	"uconfig/constants"
	"uconfig/xlsxhelper"
)

func ProcessOneSheet(dir string, outputCodeDir string, outputDataDir string, sheetInfo *xlsxhelper.XLSXSheetInfo) {
	L := lua.NewState()
	defer L.Close()
	if err := L.DoFile(constants.LuaFile); err != nil {
		panic(err)
	}

	luaTable := Array2LuaTable2(L, sheetInfo.Table)

	err := L.CallByParam(lua.P{
		Fn:      L.GetGlobal("ProcessOneSheet"),
		NRet:    1,
		Protect: true,
	},
		lua.LString(dir),
		lua.LString(outputCodeDir),
		lua.LString(outputDataDir),
		lua.LString(sheetInfo.SheetName),
		luaTable)

	if err != nil {
		panic(err)
	}
	ret := L.Get(-1) // returned value
	L.Pop(1)         // remove received value
	log.Info("ret:", ret)
}

func BeforeProcess(dir string, outputCodeDir string, outputDataDir string, fileNames []string, sheetNames []string) {
	L := lua.NewState()
	defer L.Close()
	if err := L.DoFile(constants.LuaFile); err != nil {
		panic(err)
	}

	err := L.CallByParam(lua.P{
		Fn:      L.GetGlobal("BeforeProcess"),
		NRet:    1,
		Protect: true,
	},
		lua.LString(dir),
		lua.LString(outputCodeDir),
		lua.LString(outputDataDir),
		Array2LuaTable1(L, fileNames),
		Array2LuaTable1(L, sheetNames))

	if err != nil {
		panic(err)
	}
	ret := L.Get(-1) // returned value
	L.Pop(1)         // remove received value
	log.Info("ret:", ret)
}

func AfterProcess(dir string, outputCodeDir string, outputDataDir string, fileNames []string, sheetNames []string) {
	L := lua.NewState()
	defer L.Close()
	if err := L.DoFile(constants.LuaFile); err != nil {
		panic(err)
	}

	err := L.CallByParam(lua.P{
		Fn:      L.GetGlobal("AfterProcess"),
		NRet:    1,
		Protect: true,
	},
		lua.LString(dir),
		lua.LString(outputCodeDir),
		lua.LString(outputDataDir),
		Array2LuaTable1(L, fileNames),
		Array2LuaTable1(L, sheetNames))

	if err != nil {
		panic(err)
	}
	ret := L.Get(-1) // returned value
	L.Pop(1)         // remove received value
	log.Info("ret:", ret)
}
