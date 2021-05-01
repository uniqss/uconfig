#pragma once

#include<vector>
#include<string>

int ProcessOneSheet(const std::string& xlsxName,
	const std::string& sheetName,
	const std::vector<std::string>& vecNames, // ��2��
	const std::vector<std::string>& vecTypes, // ��3��
	const std::vector<std::string>& vecDescriptions // ��5��
);

int ProcessOneSheetAllData(const std::string& xlsxName, const std::string& sheetName,
	const std::vector < std::vector<std::string>>& datas);

int BeforeProcess();

int ProcessOneSheetAllDataSol2(const std::string& xlsxName, const std::string& sheetName,
	const std::vector < std::vector<std::string>>& datas);

int AfterProcess();
