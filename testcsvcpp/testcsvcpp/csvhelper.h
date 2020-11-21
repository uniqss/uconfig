#pragma once

#include <vector>
#include <utility> // std::pair
#include <fstream>
#include<iostream>
#include <sstream> // std::stringstream

bool read_csv(const std::string& filename, std::vector<std::pair<std::string, std::vector<std::string>>>& result);

bool read_csv2(const std::string& filename, std::vector<std::string>& header, std::vector<std::vector<std::string>>& result);

bool read_csv3(const std::string& filename, std::vector<std::string>& names, std::vector<std::string>& types, std::vector<std::vector<std::string>>& result);

void TrimLine(const std::string& row, std::vector<std::string>& columns);


void to_utf8(const std::string& str, std::string& dst, const std::locale& loc = std::locale{});

void from_utf8(const std::string& str, std::string& dst, const std::locale& loc = std::locale{});

