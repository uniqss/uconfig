package generator

import (
	log "github.com/sirupsen/logrus"
	"uniqsconfiggenerator/xlsxhelper"
)

func ProcessOneSheetJs(sheetInfo *xlsxhelper.XLSXSheetInfo, header *Header){
	sheetName := sheetInfo.SheetName
	log.Info("sheetName:", sheetName)

	for _, rowInfo := range sheetInfo.Table {
		for _, colInfo := range rowInfo {
			_ = colInfo
		}
	}
}
