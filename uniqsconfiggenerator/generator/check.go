package generator

import (
	log "github.com/sirupsen/logrus"
	"uniqsconfiggenerator/xlsxhelper"
)

func ProcessOneSheetCheck(sheetInfo *xlsxhelper.XLSXSheetInfo, header *Header){
	sheetName := sheetInfo.SheetName
	log.Info("sheetName:", sheetName)

	// check列是否有重名
	// check类型行是否是当前支持的类型
	// check所有数据的主KEY唯一性
	// check所有数据是否是对应的类型
	// check所有的Sheet是否有重名(生成是用的Sheet的名字来做的)

	for _, rowInfo := range sheetInfo.Table {
		for _, colInfo := range rowInfo {
			_ = colInfo
		}
	}
}

