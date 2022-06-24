#include "lexicalAnalyzer.h"
#include <iostream>
#include <iomanip>

using namespace std;


void Lexer::startLexer(const string file_name, std::ostream &out, const uint tab) { // default tab = 4
	initAttributes();
	initKeyWords();
	setTab(tab);
	readInputSigFile(file_name);
	print_lexemeTable(out);
	print_errorLexemeTable(out);
}

void Lexer::print_lexemeTable(std::ostream &out) {
	if (!m_tables.lexemes.empty()) {
		out << std::setw(16) << "Line" << std::setw(16) << "Column"
			<< std::setw(16) << "Code" << std::setw(30) << "Token" << endl;
		out << "|-------------------------------------------------------------------------------|" << endl << endl;
		for (const auto &it : m_tables.lexemes)
			it.printLexeme(out);
		out << "\n|-------------------------------------------------------------------------------|" << endl << endl;
		out << "\n";
	}
	else if (m_tables.lexemes.empty() && m_tables.errorLexemeTable.empty())
		out << "\n Empty sig file" << endl;
	else
		out << std::setw(37) << "No lexemes to analyze\n" << endl;
}

void Lexer::print_errorLexemeTable(std::ostream &out) {
	if (!m_tables.errorLexemeTable.empty()) {
		for (const auto &it : m_tables.errorLexemeTable) {
			if (it.name[0] == '(' && it.name[1] == '*')
				out << std::setw(66) << "Lexical error: *) expected but end of file found:  " << it.name << endl;
			else if (it.name[0] == '(' && it.name[1] != '*')
				out << std::setw(67) << "Lexical error: **) expected but end of file found:  " << it.name << endl;
			else
				out << std::setw(50) << "Lexical error: Illegal symbol(s):  " << it.name << endl;
			out << std::setw(21) << "Line: " << it.row << "; Column: "
				<< it.col << "; Code: " << it.code << ";\n" << endl;
		}
		out << "\n|-------------------------------------------------------------------------------|" << endl << endl;
		out << "\n\n";
	}
	else if (m_tables.lexemes.empty() && m_tables.errorLexemeTable.empty())
		out << "\n Empty sig file" << endl;
	else
		out << std::setw(43) << "No ERROR lexemes to analyze\n" << endl;
}

void Lexer::initAttributes() {
	for (uint i = 0; i < 128; i++) {
		if (((i > 7) && (i < 14)) || (i == ' ')) // space symbols = 0
			Attributes[i] = CODE_SPACE;
		else if ((i >= 'A') && (i <= 'Z')) // identifiers and key words symbols = 1
			Attributes[i] = CODE_IDENTIFIER;
		else if ((i >= '0') && (i <= '9')) // number symbols = 2
			Attributes[i] = CODE_NUMBER;
		else if ((i == '.') || (i == ',') || (i == ';') || (i == ':'))
			Attributes[i] = CODE_SEPARATOR; /*separator symbols*/
		else if (i == '(')
			Attributes[i] = CODE_COMMENT; // start comment symbol = 4
		else
			Attributes[i] = CODE_ERROR; // error (inadmissible) symbols = 5
	}
}

void Lexer::initKeyWords() {
	if (m_tables.keyWordsTable.empty()) {
		m_tables.keyWordsTable["PROGRAM"] = keyWordsCounter++;
		m_tables.keyWordsTable["BEGIN"] = keyWordsCounter++;
		m_tables.keyWordsTable["END"] = keyWordsCounter++;
		m_tables.keyWordsTable["LABEL"] = keyWordsCounter++;
		m_tables.keyWordsTable["GOTO"] = keyWordsCounter++;
		m_tables.keyWordsTable["LINK"] = keyWordsCounter++;
		m_tables.keyWordsTable["IN"] = keyWordsCounter++;
		m_tables.keyWordsTable["OUT"] = keyWordsCounter++;
	}
}

void Lexer::setTab(uint tab) {
	if (tab >= 0 && tab <= 8)
		tabulation = tab;
	else
		throw std::exception("\nInvalid tabulation\n");
}

void Lexer::readInputSigFile(const string file_name) {
	try {
		if (file_name.empty())
			throw std::invalid_argument("error file_name");

		auto n = file_name.rfind(".sig");

		if (n == string::npos)
			sig_file.open(file_name + ".sig", std::ios::in);
		else
			sig_file.open(file_name, std::ios::in);
		if (!sig_file.is_open())
			throw std::runtime_error("Impossible to open the sig_file");
	}
	catch (const std::exception &ex) {
		cout << "\n" << ex.what() << endl;
		exit(-1);
	}

	temp = sig_file.get();
	
	while (true)
	{
		if (sig_file.eof())
			return;

		INP(temp);
	}

	sig_file.close();
}

void Lexer::countCurrentPos(const char &character) {
	if (character == '\t') {
		switch ((currentCol - 1) % tabulation) {
			case 0:
				currentCol += tabulation;
				break;
			case 1:
				currentCol += tabulation - 1;
				break;
			case 2:
				currentCol += tabulation - 2;
				break;
			case 3:
				currentCol += tabulation - 3;
				break;
			case 4:
				currentCol += tabulation - 4;
				break;
			case 5:
				currentCol += tabulation - 5;
				break;
			case 6:
				currentCol += tabulation - 6;
				break;
			case 7:
				currentCol += tabulation - 7;
				break;
		}
	}	
	else if (character != '\n')
		currentCol++;
	else {
		currentCol = 1;
		currentRow++;
	}
}

void Lexer::push_back_token(const uint code, const size_t row, const size_t col, const string &name) {
	if (code >= startErrorCounter)
		m_tables.errorLexemeTable.emplace_back(code, row, col, name);
	else
		m_tables.lexemes.emplace_back(code, row, col, name);
}

void Lexer::compare_push_back_lexeme_to_tables(unordered_map<string, uint>& codeNameTable, string& bufToken, uint &codeNameCounter) {
	if (!bufToken.empty()) {
		lexemeCodeFromTable = searchTokenFromTable(codeNameTable, bufToken);
		if (lexemeCodeFromTable == 0) {
			push_back_token(codeNameCounter, currentRow, startCol, bufToken);
			codeNameTable[bufToken] = codeNameCounter++;
		} 
		else
			push_back_token(lexemeCodeFromTable, currentRow, startCol, bufToken);
	}
}

void Lexer::INP(const char &character) {
	try {
		switch (Attributes[character]) {
			case CODE_SPACE:				// space symbols = 0
				space_process();
				break;
			case CODE_IDENTIFIER:			// identifiers and key words symbols = 1
				letter_process();
				break;
			case CODE_NUMBER:				// number symbols = 2
				digit_process();
				break;
			case CODE_SEPARATOR:			// separator symbols = 3
				delimiter_process();
				break;
			case CODE_COMMENT:				// start comment symbol = 4
				comment_process();
				break;
			case CODE_ERROR:				// error (inadmissible) symbols = 5
				error_process();
				break;
			default:
				if (!sig_file.eof())
					throw std::runtime_error("Incorrect INP switch case error");
		}
	}
	catch (const std::runtime_error &ex) {
		cout << "\n" << ex.what() << endl;
	}
}

void Lexer::letter_process() { // identifiers and key words symbols = 1
	string bufToken;
	startCol = currentCol;
	bool flag = true;

	while (true) {
		bufToken.push_back(temp);
		countCurrentPos(temp);
		temp = sig_file.get();
		if (Attributes[temp] == CODE_SPACE || Attributes[temp] == CODE_SEPARATOR
			|| Attributes[temp] == CODE_COMMENT || sig_file.eof())
			break;
		if (flag == true)
			if (Attributes[temp] != CODE_IDENTIFIER && Attributes[temp] != CODE_NUMBER)
				flag = false;
	}

	if (flag == true) {
		lexemeCodeFromTable = searchTokenFromTable(m_tables.keyWordsTable, bufToken);
		if (lexemeCodeFromTable == 0)
			compare_push_back_lexeme_to_tables(m_tables.identifiersTable, bufToken, identifiersCounter);
		else
			push_back_token(lexemeCodeFromTable, currentRow, startCol, bufToken);
		bufToken.clear();
	} else
		error_process(bufToken);
}

void Lexer::digit_process() { // number symbols = 2
	string bufToken;
	startCol = currentCol;
	bool flag = true;

	while (true) {
		bufToken.push_back(temp);
		countCurrentPos(temp);
		temp = sig_file.get();
		if (Attributes[temp] == CODE_SPACE || Attributes[temp] == CODE_SEPARATOR
			|| Attributes[temp] == CODE_COMMENT || sig_file.eof())
			break;
		if (flag == true)
			if (Attributes[temp] != CODE_NUMBER)
				flag = false;
	}

	if (flag == true) {
		compare_push_back_lexeme_to_tables(m_tables.const_uintIntTable, bufToken, constCounter);
		bufToken.clear();
	}
	else
		error_process(bufToken);
}

void Lexer::delimiter_process() { // separator symbols = 3
	string bufToken;
	startCol = currentCol;
	bufToken.push_back(temp);
	countCurrentPos(temp);
	temp = sig_file.get();
	compare_push_back_lexeme_to_tables(m_tables.separatorsTable, bufToken, separatorsCounter);
	bufToken.clear();
}

void Lexer::comment_process() { // start comment symbol = 4
	startCol = currentCol;
	countCurrentPos(temp);
	temp = sig_file.get();
	bool endCom = false;
	if (temp == '*') {
		string bufToken("(");
		while (true) {
			bufToken.push_back(temp);
			countCurrentPos(temp);
			temp = sig_file.get();
			if (temp == EOF) {
				error_process(bufToken);
				return;
			}
			else if (temp == '*')
				while (1) {
					bufToken.push_back(temp);
					countCurrentPos(temp);
					temp = sig_file.get();
					if (temp == EOF) {
						error_process(bufToken);
						return;
					}
					else if (temp == ')') {
						countCurrentPos(temp);
						temp = sig_file.get();
						bufToken.clear();
						endCom = true;
						break;
					}
					else if (temp != '*')
						break;
				}
			if (endCom)
				break;
		}
	}
	if (endCom)
		return;
	else if (temp == EOF)
		error_process("(");
	else {
		countCurrentPos(temp);
		temp = sig_file.get();
		error_process("(");
	}
}

void Lexer::space_process() { // space symbols = 0
	while (true) {
		countCurrentPos(temp);
		temp = sig_file.get();
		if (Attributes[temp] != CODE_SPACE || sig_file.eof())
			break;
	}
}

void Lexer::error_process(const string &bufTokenFromAnotherCategory) { // error (inadmissible) symbols = 5
	bool flag = true;
	if (!bufTokenFromAnotherCategory.empty())
		flag = false;

	string bufToken;
	if (flag == false)
		bufToken = bufTokenFromAnotherCategory;

	if (flag == true) {
		startCol = currentCol;
		while (true) {
			bufToken.push_back(temp);
			countCurrentPos(temp);
			temp = sig_file.get();
			if (Attributes[temp] == CODE_SPACE || Attributes[temp] == CODE_SEPARATOR
				|| Attributes[temp] == CODE_COMMENT || sig_file.eof())
				break;
		}
	}

	compare_push_back_lexeme_to_tables(m_tables.errorTokenTable, bufToken, errorCounter);
	bufToken.clear();
}

uint Lexer::searchTokenFromTable(const unordered_map<string, uint>& infoTable, const string &bufToken) const {
	auto const iter = infoTable.find(bufToken);
	if (iter != infoTable.end())
		return iter->second;
	return 0;
} // return 0 = searching failed, return > 0 = number was found
