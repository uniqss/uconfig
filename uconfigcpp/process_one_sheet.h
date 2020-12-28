#pragma once

#include <vector>
#include <string>

int ProcessOneSheet_lua(const std::string& xlsxName, const std::string& sheetName, const std::vector<std::string>& vecNames, const std::vector<std::string>& vecTypes, const std::vector<std::string>& vecDescriptions);

int ProcessOneSheet_js(const std::string& xlsxName, const std::string& sheetName, const std::vector<std::string>& vecNames, const std::vector<std::string>& vecTypes, const std::vector<std::string>& vecDescriptions);
