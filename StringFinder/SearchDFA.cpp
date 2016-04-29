#include "stdafx.h"
#include "SearchDFA.h"

CSearchDFA::CSearchDFA()
{
}

CSearchDFA::~CSearchDFA()
{
}

void CSearchDFA::Compile(const std::string &inputString)
{
	m_needle = inputString;
	// TODO: реализовать "честную" компиляцию автомата с использованием префикс-функций.

	m_currentState = 0;
	m_sizeSearchString = m_needle.size();

	for (size_t index = 0; index < m_needle.size(); index++)
	{
		m_states.push_back(index + 1);
		m_symbolsTransition.push_back(m_needle[index]);
	}
}

size_t CSearchDFA::Find(const std::string &text, size_t from)
{
	// TODO: реализовать метод "по-честному".

	// Подсказка: можно использовать boost::string_ref, чтобы не извлекать подстроку из текста.
	// Это позволит оптимизировать повторные вызовы Search на одной строке.
	std::string templateString;
	size_t currentPosition = from;

	while (currentPosition < text.size())
	{
		templateString = text.substr(currentPosition, m_sizeSearchString);

		m_currentState = 0;
		for (const auto & element : templateString)
		{
			if (m_currentState == 0)
			{
				if (element == m_symbolsTransition[0])
				{
					m_currentState = 1;
				}
				else
				{
					break;
				}
			}
			else if ((m_currentState > 0) && (m_currentState < m_sizeSearchString))
			{
				if (element == m_symbolsTransition[m_currentState])// m_currentState = number next symbol
				{
					m_currentState = m_currentState + 1;
				}
			}
			else if (m_currentState > 0)
			{
				continue;
			}
			else
			{
				break;
			}
		}

		if (m_currentState == m_sizeSearchString)// TODO
		{
			return currentPosition;
		}

		currentPosition += 1;
	}

	return std::numeric_limits<size_t>::max();
}

size_t CSearchDFA::GetSizeSearchString() const
{
	return m_sizeSearchString;
}
