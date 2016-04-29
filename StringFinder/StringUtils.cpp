#include "stdafx.h"
#include "StringUtils.h"

// Метод возвращает количество вхождений искомой подстроки в переданный текст.
unsigned CStringUtils::Count(const std::string &text, CSearchDFA &dfa)
{
	size_t position = 0;
	size_t foundPosition = 0;
	size_t counter = 0;

	while ((position + dfa.GetSizeSearchString()) < text.size())
	{
		foundPosition = dfa.Find(text, position);

		if (foundPosition == std::numeric_limits<size_t>::max())
		{
			break;
		}
		position = foundPosition + dfa.GetSizeSearchString();
		counter++;
	}

	return counter;
}

// Метод определяет, содержится ли подстрока в тексте
bool CStringUtils::Contains(const std::string &text, CSearchDFA &dfa)
{
	return dfa.Find(text, 0) < std::numeric_limits<size_t>::max();
}

// Метод находит все позиции вхождения подстроки в строку
// TODO: уточнить здесь, могут ли найденные вхождения пересекаться. Покрыть тестами.
std::vector<size_t> CStringUtils::FindAll(const std::string &text, CSearchDFA &dfa)
{
	size_t position = 0;
	size_t foundPosition = 0;
	std::vector<size_t> foundPositions;

	while ((position + dfa.GetSizeSearchString()) < text.size())
	{
		foundPosition = dfa.Find(text, position);

		if (foundPosition == std::numeric_limits<size_t>::max())
		{
			break;
		}
		foundPositions.push_back(foundPosition);

		position = foundPosition + dfa.GetSizeSearchString() + 1;
	}

	return foundPositions;
}
