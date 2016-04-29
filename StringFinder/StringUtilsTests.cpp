#include "stdafx.h"
#include "StringUtils.h"
#include "SearchDFA.h"
#include <sstream>
#include <boost/algorithm/string.hpp>


#include <string>
#include <iostream>// for std::cin and std::cout
#include <fstream>
#include <memory>

#include <chrono>

using std::vector;
using std::string;

const std::string PATH_RIGHT_DATA = "Right\\";


void CompareFiles(const std::string & first, const std::string & second)
{
	std::ifstream resultFile(first);
	std::ifstream rightResultFile(second);

	std::istream_iterator<char> iterResultFile(resultFile), endIter;
	std::istream_iterator<char> iterRightRsultFile(rightResultFile);

	BOOST_CHECK_EQUAL_COLLECTIONS(iterResultFile, endIter, iterRightRsultFile, endIter);
};

std::vector<size_t> FindAllInFile(std::ifstream & file, CSearchDFA &dfa)
{
	std::vector<size_t> result;
	std::vector<size_t> current;
	std::string inputString;

	while (getline(file, inputString))
	{
		current = CStringUtils::FindAll(inputString, dfa);
		result.insert(result.end(), current.begin(), current.end());
	}

	return result;
}

BOOST_AUTO_TEST_SUITE(StringUtils_class)
	BOOST_AUTO_TEST_CASE(can_check_if_contains)
	{
		const std::string needle = "ax";
		const std::string text = "axdaxabxo!";
		CSearchDFA dfa;
		dfa.Compile(needle);
		BOOST_CHECK(CStringUtils::Contains(text, dfa));
	}

	BOOST_AUTO_TEST_CASE(can_count_all_matches)
	{
		const std::string needle = "ax";
		const std::string text = "axdaxabxo!";
		CSearchDFA dfa;
		dfa.Compile(needle);
		unsigned count = CStringUtils::Count(text, dfa);
		BOOST_CHECK_EQUAL(count, 2);
	}

	BOOST_AUTO_TEST_CASE(can_find_all_matches)
	{
		const std::string needle = "ax";
		const std::string text = "axdaxabxo!";
		CSearchDFA dfa;
		dfa.Compile(needle);
		std::vector<size_t> matches = CStringUtils::FindAll(text, dfa);
		std::vector<size_t> expected = {0, 3};
		BOOST_CHECK(matches == expected);
		
	}


	BOOST_AUTO_TEST_CASE(word_is_not_exist_in_string)
	{
		const std::string needle = "aZx";
		const std::string text = "axdaxabxo!";
		CSearchDFA dfa;
		dfa.Compile(needle);
		std::vector<size_t> matches = CStringUtils::FindAll(text, dfa);
		std::vector<size_t> expected;
		BOOST_CHECK(matches == expected);
	}

	BOOST_AUTO_TEST_CASE(word_is_empty)
	{
		const std::string needle = "";
		const std::string text = "axdaxabxo!";
		CSearchDFA dfa;
		dfa.Compile(needle);
		std::vector<size_t> matches = CStringUtils::FindAll(text, dfa);
		std::vector<size_t> expected;
		BOOST_CHECK(matches == expected);
	}

	BOOST_AUTO_TEST_CASE(string_is_empty)
	{
		const std::string needle = "aZx";
		const std::string text = "";
		CSearchDFA dfa;
		dfa.Compile(needle);
		std::vector<size_t> matches = CStringUtils::FindAll(text, dfa);
		std::vector<size_t> expected;
		BOOST_CHECK(matches == expected);
	}

	BOOST_AUTO_TEST_CASE(word_is_larger_than_whole_string)
	{
		const std::string needle = "aZx";
		const std::string text = "a!";
		CSearchDFA dfa;
		dfa.Compile(needle);
		std::vector<size_t> matches = CStringUtils::FindAll(text, dfa);
		std::vector<size_t> expected;
		BOOST_CHECK(matches == expected);
	}

	BOOST_AUTO_TEST_CASE(word_is_equal_to_input_string)
	{
		const std::string needle = "aZx";
		const std::string text = "aZx";
		CSearchDFA dfa;
		dfa.Compile(needle);
		std::vector<size_t> matches = CStringUtils::FindAll(text, dfa);
		std::vector<size_t> expected = { 0 };
		BOOST_CHECK(matches == expected);
	}


	BOOST_AUTO_TEST_CASE(upper_edge_test)
	{
		
		// Через системные часы получаем объект типа time_point.
		auto timePointBefore = std::chrono::system_clock::now();

		////
		const std::string needle = "aZx";

		std::ifstream inputFile("inputBig.txt");

		CSearchDFA dfa;
		dfa.Compile(needle);
		std::vector<size_t> matches = FindAllInFile(inputFile, dfa);//CStringUtils::FindAll(text, dfa);
		//std::vector<size_t> expected;
		////

		// Получаем второй момент времени (после операции).
		auto timePointAfter = std::chrono::system_clock::now();
		auto timeDeltaMsec = std::chrono::duration_cast<std::chrono::milliseconds>(timePointAfter - timePointBefore);
		std::cerr << "Total time: " << timeDeltaMsec.count() << std::endl;
		//BOOST_CHECK(matches == expected);
	}

BOOST_AUTO_TEST_SUITE_END()