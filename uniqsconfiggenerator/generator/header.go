package generator

import (
	"strings"
	"uniqsconfiggenerator/constants"
	"uniqsconfiggenerator/xlsxhelper"
)

type Header struct {
	IsComment    []string
	PrimaryKey   []string
	CodeName     []string
	Type         []string
	ClientServer []string
	Description  []string
}

func NewHeader() *Header {
	return &Header{}
}

func (h *Header) TrimHeader(sheetInfo *xlsxhelper.XLSXSheetInfo) {
	idx := 0
	h.IsComment = sheetInfo.Table[idx]
	idx++
	h.PrimaryKey = sheetInfo.Table[idx]
	idx++
	h.CodeName = sheetInfo.Table[idx]
	idx++
	h.Type = sheetInfo.Table[idx]
	idx++
	h.ClientServer = sheetInfo.Table[idx]
	idx++
	h.Description = sheetInfo.Table[idx]
}

func (h *Header) NeedGenerateSheet() bool {
	for i := 0; i < len(h.Type); i++ {
		if h.NeedGenerateCol(i) {
			return true
		}
	}

	return false
}

func (h *Header) NeedGenerateCol(idx int) bool {
	if h.IsComment[idx] != "" && h.IsComment[idx][0] == '#' {
		return false
	}

	if strings.Contains(h.ClientServer[idx], constants.Peer) {
		return true
	}

	return false
}
