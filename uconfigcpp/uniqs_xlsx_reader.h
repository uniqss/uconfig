#pragma once

#include<vector>
#include<string>

int read_xlsx(const char* filename, std::vector<std::pair<std::string, std::vector<std::vector<std::string> > > >& vecResult);
int read_xlsx(const std::string& filename, std::vector<std::pair<std::string, std::vector<std::vector<std::string> > > >& vecResult);

