#include "csvhelper.h"
#include <algorithm>

#include "strtk.hpp"

#include <string>
#include <codecvt>

using namespace std::string_literals;

bool read_csv(const std::string& filename, std::vector<std::pair<std::string, std::vector<std::string>>>& result)
{
	std::ifstream myFile(filename);

	bool bRet = false;
	do
	{
		if (!myFile.is_open())
		{
			std::cout << "read_csv Could not open file filename:" << filename << std::endl;
			break;
		}

		std::string line, colname;
		std::string val;

		if (myFile.good())
		{
			std::getline(myFile, line);

			std::stringstream ss(line);

			while (std::getline(ss, colname, ',')) {

				result.push_back({ colname, std::vector<std::string> {} });
			}
		}

		while (std::getline(myFile, line))
		{
			std::stringstream ss(line);

			int colIdx = 0;

			while (ss >> val) {
				result.at(colIdx).second.push_back(val);

				if (ss.peek() == ',') ss.ignore();

				colIdx++;
			}
		}

		bRet = true;

	} while (false);

	myFile.close();

	return bRet;
}

bool read_csv2(const std::string& filename, std::vector<std::string>& header, std::vector<std::vector<std::string>>& result)
{
	std::ifstream myFile(filename);

	bool bRet = false;
	do
	{
		if (!myFile.is_open())
		{
			std::cout << "read_csv Could not open file filename:" << filename << std::endl;
			break;
		}

		std::string line, colname;
		std::string val;

		if (myFile.good())
		{
			std::getline(myFile, line);

			std::stringstream ss(line);

			while (std::getline(ss, colname, ',')) {

				header.push_back(colname);
			}
		}

		std::vector<std::string> vecTmp;
		vecTmp.resize(header.size());

		while (std::getline(myFile, line))
		{
			std::stringstream ss(line);

			int colIdx = 0;

			auto resultSize = result.size();
			result.push_back(vecTmp);
			auto& rLine = result[resultSize];

			while (ss >> val)
			{
				rLine.push_back(val);

				if (ss.peek() == ',')
					ss.ignore();

				colIdx++;
			}
		}

		bRet = true;

	} while (false);

	myFile.close();

	return bRet;
}

bool read_csv3(const std::string& filename, std::vector<std::string>& names, std::vector<std::string>& types, std::vector<std::vector<std::string>>& result)
{
	std::ifstream myFile(filename);

	bool bRet = false;
	do
	{
		if (!myFile.is_open())
		{
			std::cout << "read_csv Could not open file filename:" << filename << std::endl;
			break;
		}

		std::string line, columnval;
		std::string val;

		// names
		if (myFile.good())
		{
			std::getline(myFile, line);

			std::stringstream ss(line);

			while (std::getline(ss, columnval, ',')) {

				names.push_back(columnval);
			}
		}

		// types
		if (myFile.good())
		{
			std::getline(myFile, line);

			std::stringstream ss(line);

			while (std::getline(ss, columnval, ',')) {

				types.push_back(columnval);
			}
		}

		// names and types length must equal, and all columns exceeded this length will be omitted.
		if (names.size() != types.size())
		{
			std::cout << "read_csv names and types length not equal. filename:" << filename << std::endl;
			break;
		}

		std::vector<std::string> vecTmp;
		// ²¹Æë
		vecTmp.resize(names.size());

		auto maxColIdx = names.size();

		while (std::getline(myFile, line))
		{
			std::vector<std::string> columns;
			TrimLine(line, columns);

			auto resultSize = result.size();
			result.push_back(vecTmp);
			auto& rLine = result[resultSize];

			for (size_t colIdx = 0; colIdx < columns.size() && colIdx < maxColIdx; colIdx++)
			{
				std::string& column = columns[colIdx];

				//std::string toutf8;
				//to_utf8(column, toutf8);
				//std::cout << toutf8 << std::endl;

				//std::string fromutf8;
				//from_utf8(column, fromutf8);
				//std::cout << fromutf8 << std::endl;

				rLine[colIdx] = column;
			}
		}

		bRet = true;

	} while (false);

	myFile.close();

	return bRet;
}

void TrimLine(const std::string& row, std::vector<std::string>& columns)
{
	strtk::parse(row, ",", columns);
}

void to_utf8(const std::string& str, std::string& dst, const std::locale& loc) {
	using wcvt = std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t>;
	std::u32string wstr(str.size(), U'\0');
	std::use_facet<std::ctype<char32_t>>(loc).widen(str.data(), str.data() + str.size(), &wstr[0]);
	dst = wcvt{}.to_bytes(wstr.data(), wstr.data() + wstr.size());
}

void from_utf8(const std::string& str, std::string& dst, const std::locale& loc) {
	using wcvt = std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t>;
	auto wstr = wcvt{}.from_bytes(str);
	std::string result(wstr.size(), '0');
	std::use_facet<std::ctype<char32_t>>(loc).narrow(wstr.data(), wstr.data() + wstr.size(), '?', &result[0]);
	dst = result;
}
