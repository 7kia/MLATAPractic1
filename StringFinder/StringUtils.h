#pragma once

#include "SearchDFA.h"

class CStringUtils
{
public:
	CStringUtils() = delete;

	static unsigned Count(const std::string &text, CSearchDFA &dfa);
	static bool Contains(const std::string &text, CSearchDFA &dfa);
	static std::vector<size_t> FindAll(const std::string &text, CSearchDFA &dfa);
};

