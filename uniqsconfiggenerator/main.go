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
	"uniqsconfiggenerator/xlsxhelper"
)

func main() {
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
