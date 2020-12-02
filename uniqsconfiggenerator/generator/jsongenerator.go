package generator

import "uniqsconfiggenerator/xlsxhelper"

/*
如果不需要生成的列，在json里面就不要生成了，因为这个json是给代码生成工具用的，只有结构，没有数据
希望生成的json的样子：
{
	“CodeName”：["CodeName1", "CodeName2"],
	"Type": ["Type1", "Type2"],
	"Description": ["Description1", "description2"],
	"PrimaryKeys": {
		"1": ["0"],
		"2": ["1", "2"],
		"3": ["3", "4", "5"]
	}
}
 */

func GenerateJson(sheetInfo *xlsxhelper.XLSXSheetInfo, header *Header)  {
	
}
