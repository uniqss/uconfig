﻿#pragma once

#include <vector>
#include <string>

int ProcessOneSheet(const std::string &xlsxName,
                    const std::string &sheetName,
                    const std::vector<std::string> &vecNames, // 第2行
                    const std::vector<std::string> &vecTypes, // 第3行
                    const std::vector<std::string> &vecDescriptions);

int ProcessOneSheetAllData(const std::string &xlsxName, const std::string &sheetName,
                           const std::vector<std::vector<std::string>> &datas);

int BeforeProcess(const std::string &scriptsPath);

int ProcessOneSheetAllDataSol2(const std::string &function, const std::string &xlsxName, const std::string &sheetName,
                               const std::vector<std::vector<std::string>> &datas);

int AfterProcess(const std::string &function, const std::vector<std::string> &vecSheetNames);
