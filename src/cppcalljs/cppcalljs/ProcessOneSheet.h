#pragma once

#include<vector>
#include<string>

#include "v8pp/context.hpp"

int ProcessOneSheet(v8pp::context& context,
	const std::string& xlsxName,
	const std::string& sheetName,
	const std::vector<std::string>& vecNames, // 第2行
	const std::vector<std::string>& vecTypes, // 第3行
	const std::vector<std::string>& vecDescriptions // 第5行
);
