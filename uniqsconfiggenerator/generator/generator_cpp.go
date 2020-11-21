package generator

import (
	log "github.com/sirupsen/logrus"
	"uniqsconfiggenerator/constants"
	"uniqsconfiggenerator/xlsxhelper"
)

func ProcessOneSheetCpp(sheetInfo *xlsxhelper.XLSXSheetInfo, header *Header) {
	sheetName := sheetInfo.SheetName
	log.Info("sheetName:", sheetName)

	GenCode(sheetName, header)
	GenData(sheetInfo, header)
}

func GenCode(sheetName, header *Header){

}

func GenData(sheetInfo *xlsxhelper.XLSXSheetInfo, header *Header){
	for rowIdx, rowInfo := range sheetInfo.Table {
		if rowIdx < constants.RowHeadLen {
			continue
		}
		for idx, colInfo := range rowInfo {
			if !header.NeedGenerateCol(idx) {
				continue
			}

			_ = colInfo
		}
	}
}
