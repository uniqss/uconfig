package main

import (
	"fmt"
	log "github.com/sirupsen/logrus"
	"uconfig/generator"
	"uconfig/xlsxhelper"
)

func ProcessOneXLSX(dir string, outputCodeDir string, outputDataDir string, info *xlsxhelper.XLSXInfo) {
	//fmt.Println("ProcessOneXLSX dir:", dir, " outputCodeDir:", outputCodeDir)
	xlsxName := info.XLSXName
	fmt.Println("开始处理:", xlsxName)

	for _, sheetInfo := range info.Sheets {
		ProcessOneSheet(dir, outputCodeDir, outputDataDir, sheetInfo)
	}
}
func ProcessOneSheet(dir string, outputCodeDir string, outputDataDir string, sheetInfo *xlsxhelper.XLSXSheetInfo) {
	log.Debugf("ProcessOneSheet dir:%v outputCodeDir:%v outputDataDir:%v SheetName:%v", dir, outputCodeDir, outputDataDir, sheetInfo.SheetName)

	generator.ProcessOneSheet(dir, outputCodeDir, outputDataDir, sheetInfo)
}
