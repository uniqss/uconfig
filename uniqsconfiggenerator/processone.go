package main

import (
	"fmt"
	log "github.com/sirupsen/logrus"
	"uniqsconfiggenerator/constants"
	"uniqsconfiggenerator/generator"
	"uniqsconfiggenerator/xlsxhelper"
)

func ProcessOneXLSX(dir string, outPutDir string, info *xlsxhelper.XLSXInfo) {
	//fmt.Println("ProcessOneXLSX dir:", dir, " outPutDir:", outPutDir)
	xlsxName := info.XLSXName
	fmt.Println("开始处理:", xlsxName)

	for _, sheetInfo := range info.Sheets {
		ProcessOneSheet(sheetInfo)
	}
}
func ProcessOneSheet(sheetInfo *xlsxhelper.XLSXSheetInfo) {
	if len(sheetInfo.Table) < constants.RowHeadLen {
		log.Error("ProcessOneSheetCpp table rows < RowHeadLen")
		return
	}

	header := generator.NewHeader()
	header.TrimHeader(sheetInfo)

	if !header.NeedGenerateSheet() {
		log.Warn("ProcessOneSheet header.NeedGenerateSheet.else  name:", sheetInfo.SheetName)
		return
	}

	generator.GenerateJson(sheetInfo, header)
}
