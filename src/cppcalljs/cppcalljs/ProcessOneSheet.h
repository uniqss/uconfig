#pragma once

#include<vector>
#include<string>

#include "v8pp/context.hpp"

int ProcessOneSheet(v8pp::context& context,
	const std::string& xlsxName,
	const std::string& sheetName,
	const std::vector<std::string>& vecNames, // ��2��
	const std::vector<std::string>& vecTypes, // ��3��
	const std::vector<std::string>& vecDescriptions // ��5��
);
