package main

import (
	"flag"
	"fmt"
	log "github.com/sirupsen/logrus"
	"gopkg.in/ini.v1"
	"io/ioutil"
	"os"
	"strings"
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

	if header.NeedGenerateSheet() {
		if constants.Mode == "check" {
			generator.ProcessOneSheetCheck(sheetInfo, header)
		} else if constants.Mode == "cpp" {
			generator.ProcessOneSheetCpp(sheetInfo, header)
		} else if constants.Mode == "go" {
			generator.ProcessOneSheetGo(sheetInfo, header)
		} else if constants.Mode == "lua" {
			generator.ProcessOneSheetLua(sheetInfo, header)
		} else if constants.Mode == "js" {
			generator.ProcessOneSheetJs(sheetInfo, header)
		}
	} else {
		log.Warn("ProcessOneSheet header.NeedGenerateSheet.else  name:", sheetInfo.SheetName)
	}
}

var indent = 0

func WriteGoLine(file *os.File, str string) {
	for i := 0; i < indent; i++ {
		file.WriteString("\t")
	}
	file.WriteString(str + "\n")
}

func WriteGoFiles(DTConfigs []string) {
	iniFileName := "uniqs.ini"
	cfg, err := ini.Load(iniFileName)
	if err != nil {
		log.Fatal("ini.Load failed iniFileName:", iniFileName)
	}
	outPutDir := cfg.Section(constants.UniqsSectionName).Key("dtconfig_go_output_dir").String()
	if !strings.HasSuffix(outPutDir, "\\") && !strings.HasSuffix(outPutDir, "/") {
		outPutDir += "/"
	}
	fmt.Println("dtconfig_go_output_dir:", outPutDir)
	err = os.MkdirAll(outPutDir, os.ModePerm)
	if err != nil {
		log.Error("os.MkdirAll failed. err:", err)
	}

	fileName := ""
	var file *os.File

	// export.go
	if 1 == 1 {
		indent = 0
		fileName = "export.go"
		fileName = outPutDir + fileName
		file, err = os.OpenFile(fileName, os.O_CREATE|os.O_TRUNC|os.O_WRONLY, os.ModePerm)
		if err != nil {
			log.Error("os.Open failed. fileName:", fileName)
			return
		}
		defer file.Close()

		WriteGoLine(file, "package DataTables")
		WriteGoLine(file, "")
		for _, c := range DTConfigs {
			cfg := c
			cfgData := cfg + "_Data"
			WriteGoLine(file, "func Get"+cfg+"() *"+cfgData+" {")
			indent++
			WriteGoLine(file, "return inst.Get(\""+cfg+"\").(*"+cfgData+")")
			indent--
			WriteGoLine(file, "}")
			WriteGoLine(file, "")
		}
	}

	// init_generated.go
	if 1 == 1 {
		indent = 0
		fileName = "init_generated.go"
		fileName = outPutDir + fileName
		file, err = os.OpenFile(fileName, os.O_CREATE|os.O_TRUNC|os.O_WRONLY, os.ModePerm)
		if err != nil {
			log.Error("os.Open failed. fileName:", fileName)
			return
		}
		defer file.Close()

		WriteGoLine(file, "package DataTables")
		WriteGoLine(file, "")
		WriteGoLine(file, "func InitGenerated() {")
		indent++
		for _, c := range DTConfigs {
			cfg := c
			cfgData := cfg + "_Data"
			WriteGoLine(file, "inst.Register(\""+cfg+"\", &"+cfgData+"{})")
		}
		indent--
		WriteGoLine(file, "}")
		WriteGoLine(file, "")
	}
}

func main() {
	modeFlag := flag.String("mode", "cpp", "which mode to generate check/cpp/go/js/lua")
	constants.Mode = *modeFlag
	log.Info("main mode:", constants.Mode)

	peerFlag := flag.String("peer", "s", "which peer to generate c/s means client/server peer")
	constants.Peer = *peerFlag
	strings.ToLower(constants.Peer)
	if constants.Peer != "s" && constants.Peer != "c" {
		log.Error("peer must be c or s")
		return
	}
	log.Info("main peer:", constants.Peer)

	flag.Parse()

	iniFileName := "uniqs.ini"
	cfg, err := ini.Load(iniFileName)
	if err != nil {
		log.Fatal("ini.Load failed iniFileName:", iniFileName)
	}

	constants.XLSXDir = cfg.Section(constants.UniqsSectionName).Key("xlsx_dir").String()
	if !strings.HasSuffix(constants.XLSXDir, "\\") && !strings.HasSuffix(constants.XLSXDir, "/") {
		constants.XLSXDir += "/"
	}
	fmt.Println("xlsx_dir:", constants.XLSXDir)

	constants.OutputCodeDir = cfg.Section(constants.UniqsSectionName).Key("output_code_dir").String()
	if !strings.HasSuffix(constants.OutputCodeDir, "\\") && !strings.HasSuffix(constants.OutputCodeDir, "/") {
		constants.OutputCodeDir += "/"
	}
	fmt.Println("output_code_dir:", constants.OutputCodeDir)

	constants.OutputDataDir = cfg.Section(constants.UniqsSectionName).Key("output_data_dir").String()
	if !strings.HasSuffix(constants.OutputDataDir, "\\") && !strings.HasSuffix(constants.OutputDataDir, "/") {
		constants.OutputDataDir += "/"
	}
	fmt.Println("output_data_dir:", constants.OutputDataDir)

	constants.TemplateDir = cfg.Section(constants.UniqsSectionName).Key("template_dir").String()
	if !strings.HasSuffix(constants.TemplateDir, "\\") && !strings.HasSuffix(constants.TemplateDir, "/") {
		constants.TemplateDir += "/"
	}
	fmt.Println("template_dir:", constants.TemplateDir)

	files, err := ioutil.ReadDir(constants.XLSXDir)
	if err != nil {
		log.Fatal("ioutil.ReadDir failed", err)
	}
	err = os.MkdirAll(constants.OutputCodeDir, os.ModePerm)
	if err != nil {
		log.Fatal("os.MkdirAll OutputCodeDir failed. err:", err)
	}
	err = os.MkdirAll(constants.OutputDataDir, os.ModePerm)
	if err != nil {
		log.Fatal("os.MkdirAll OutputDataDir failed. err:", err)
	}

	for _, f := range files {
		fName := f.Name()
		//fmt.Println(fName)
		if f.IsDir() {
			continue
		}
		if strings.HasPrefix(fName, "~$") {
			continue
		}
		if !strings.HasSuffix(fName, ".xlsx") {
			continue
		}

		XLSXInfo := xlsxhelper.ReadOneXLSX(constants.XLSXDir, fName, constants.OutputCodeDir)
		if XLSXInfo != nil {
			ProcessOneXLSX(constants.XLSXDir, constants.OutputCodeDir, XLSXInfo)
		}
	}
}
