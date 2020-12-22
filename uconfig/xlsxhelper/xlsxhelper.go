package xlsxhelper

import (
	"fmt"
	"github.com/tealeg/xlsx"
	"uconfig/constants"
)

type XLSXSheetInfo struct {
	SheetName string
	Table     [][]string
}

func NewXLSXSheetInfo(sheetName string) *XLSXSheetInfo {
	return &XLSXSheetInfo{
		SheetName: sheetName,
	}
}

type XLSXInfo struct {
	XLSXName string
	Sheets   []*XLSXSheetInfo
}

func NewXLSXInfo(XLSXName string) *XLSXInfo {
	return &XLSXInfo{XLSXName: XLSXName}
}

func ReadOneXLSX(dir string, excelFileName string, outPutDir string) *XLSXInfo {
	retInfo := NewXLSXInfo(excelFileName)
	//fmt.Println("ReadOneXLSX dir:", dir, " excelFileName:", excelFileName, " outPutDir:", outPutDir)
	fmt.Println("开始读取:", excelFileName)
	xlFile, err := xlsx.OpenFile(dir + excelFileName)
	if err != nil {
		fmt.Printf("open failed: %s\n", err)
		return nil
	}
	for _, sheet := range xlFile.Sheets {
		sheetInfo := NewXLSXSheetInfo(sheet.Name)
		constants.SheetNames = append(constants.SheetNames, sheet.Name)
		//fmt.Printf("Sheet Name: %s\n", sheet.Name)
		for _, row := range sheet.Rows {
			var rowInfo []string
			for _, cell := range row.Cells {
				text := cell.String()
				rowInfo = append(rowInfo, text)
				//fmt.Printf("%s\t", text)
			}
			sheetInfo.Table = append(sheetInfo.Table, rowInfo)
			//fmt.Println()
		}
		retInfo.Sheets = append(retInfo.Sheets, sheetInfo)
		//fmt.Println()
	}

	return retInfo
}
