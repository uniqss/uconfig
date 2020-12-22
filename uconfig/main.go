package main

import (
	"fmt"
	log "github.com/sirupsen/logrus"
	"gopkg.in/ini.v1"
	"io/ioutil"
	"os"
	"strings"
	"uconfig/constants"
	"uconfig/generator"
	"uconfig/xlsxhelper"
)

func main() {

	iniFileName := "uniqs.ini"
	cfg, err := ini.Load(iniFileName)
	if err != nil {
		log.Fatal("ini.Load failed iniFileName:", iniFileName)
	}

	constants.XLSXDir = cfg.Section(constants.UConfigSectionName).Key("xlsx_dir").String()
	if !strings.HasSuffix(constants.XLSXDir, "\\") && !strings.HasSuffix(constants.XLSXDir, "/") {
		constants.XLSXDir += "/"
	}
	fmt.Println("xlsx_dir:", constants.XLSXDir)

	constants.OutputCodeDir = cfg.Section(constants.UConfigSectionName).Key("output_code_dir").String()
	if !strings.HasSuffix(constants.OutputCodeDir, "\\") && !strings.HasSuffix(constants.OutputCodeDir, "/") {
		constants.OutputCodeDir += "/"
	}
	fmt.Println("output_code_dir:", constants.OutputCodeDir)

	constants.OutputDataDir = cfg.Section(constants.UConfigSectionName).Key("output_data_dir").String()
	if !strings.HasSuffix(constants.OutputDataDir, "\\") && !strings.HasSuffix(constants.OutputDataDir, "/") {
		constants.OutputDataDir += "/"
	}
	fmt.Println("output_data_dir:", constants.OutputDataDir)

	constants.LuaFile = cfg.Section(constants.UConfigSectionName).Key("lua_file").String()
	fmt.Println("lua_file:", constants.LuaFile)

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

	var xlsxInfos []*xlsxhelper.XLSXInfo

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
			constants.FileNames = append(constants.FileNames, fName)
			xlsxInfos = append(xlsxInfos, XLSXInfo)
		} else {
			log.Debug("XLSXInfo is nil fName:", fName)
		}
	}

	generator.BeforeProcess(constants.XLSXDir, constants.OutputCodeDir, constants.OutputDataDir, constants.FileNames, constants.SheetNames)

	for _, XLSXInfo := range xlsxInfos {
		ProcessOneXLSX(constants.XLSXDir, constants.OutputCodeDir, constants.OutputDataDir, XLSXInfo)
	}

	generator.AfterProcess(constants.XLSXDir, constants.OutputCodeDir, constants.OutputDataDir, constants.FileNames, constants.SheetNames)
}
