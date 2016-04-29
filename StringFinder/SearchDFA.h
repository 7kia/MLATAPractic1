#pragma once

class CSearchDFA
{
public:
	CSearchDFA();
	~CSearchDFA();

	void Compile(const std::string &inputString);
	size_t Find(const std::string &text, size_t from = 0);

	size_t GetSizeSearchString() const;
private:
	std::string			m_needle;
	size_t				m_sizeSearchString;

	std::vector<int>	m_states;
	std::vector<char>	m_symbolsTransition;
	int					m_currentState;
};
