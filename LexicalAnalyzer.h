#pragma once

#include <fstream>
#include <vector>
#include <unordered_map>
#include <ostream>
#include <iomanip>

typedef unsigned uint;

struct Lexeme { // attributes of one lexeme

public:
	Lexeme(uint _code, size_t _row, size_t _col, std::string _name) : code(_code), row(_row), col(_col), name(_name), parsed(false) {}		// delete parsed

	void printLexeme(std::ostream& out) const {
		out << std::setw(8) << "|" << std::setw(8) << row << std::setw(8) << "|" << std::setw(8) << col
			<< std::setw(8) << "|" << std::setw(8) << code << std::setw(8) << "|" << std::setw(22) << name << std::endl;
	}

	uint code = 0;
	size_t row = 0;
	size_t col = 0;
	std::string name;
	bool parsed;	//delete parsed
};

inline uint getTokenCode(std::unordered_map<std::string, uint>& table, const char* keyWord) {
	auto iter = table.find(std::string(keyWord));
	return iter == table.end() ? 0 : iter->second;
}

struct LexemeTables {

	std::vector<Lexeme> lexemes;		 // information about lexemes row, col, code, name)
	std::vector<Lexeme> errorLexemeTable;	 // information about ERROR lexemes (row, col, code, name)

	uint minKeyWordsCounter = 401; // lexeme codes
	uint minConstCounter = 501;
	uint minIdentifiersCounter = 1001;
	uint minSeparatorsCounter = 1;
	uint minErrorCounter = 5001;
	uint minStartErrorCounter = 5001;


	std::unordered_map<std::string, uint> keyWordsTable;
	std::unordered_map<std::string, uint> const_uintIntTable;
	std::unordered_map<std::string, uint> identifiersTable;
	std::unordered_map<std::string, uint> errorTokenTable;
	std::unordered_map<std::string, uint> separatorsTable;

	uint getLexemeCode(uint pos) { return lexemes[pos].code; }
	size_t getLexemeRow(uint pos) { return lexemes[pos].row; }
	size_t getLexemeCol(uint pos) { return lexemes[pos].col; }
	std::string getLexemeName(uint pos) { return lexemes[pos].name; }
	void setParsed(uint pos, bool parsed) { lexemes[pos].parsed = parsed; }		// delete
	bool getParsed(uint pos) { return lexemes[pos].parsed; }		// delete

	bool isProgram(uint pos) { return getLexemeCode(pos) == getTokenCode(keyWordsTable, "PROGRAM"); }
	bool isBegin(uint pos) { return getLexemeCode(pos) == getTokenCode(keyWordsTable, "BEGIN"); }
	bool isEnd(uint pos) { return getLexemeCode(pos) == getTokenCode(keyWordsTable, "END"); }
	bool isLabel(uint pos) { return getLexemeCode(pos) == getTokenCode(keyWordsTable, "LABEL"); }
	bool isGoto(uint pos) { return getLexemeCode(pos) == getTokenCode(keyWordsTable, "GOTO"); }
	bool isLink(uint pos) { return getLexemeCode(pos) == getTokenCode(keyWordsTable, "LINK"); }
	bool isIn(uint pos) { return getLexemeCode(pos) == getTokenCode(keyWordsTable, "IN"); }
	bool isOut(uint pos) { return getLexemeCode(pos) == getTokenCode(keyWordsTable, "OUT"); }

	bool isSemicolon(uint pos) { return getLexemeCode(pos) == getTokenCode(separatorsTable, ";"); }
	bool isColon(uint pos) { return getLexemeCode(pos) == getTokenCode(separatorsTable, ":"); }
	bool isComma(uint pos) { return getLexemeCode(pos) == getTokenCode(separatorsTable, ","); }
	bool isDot(uint pos) { return getLexemeCode(pos) == getTokenCode(separatorsTable, "."); }

	bool isConstIntIdentifier(uint pos) {
		return getLexemeCode(pos) >= minConstCounter && getLexemeCode(pos) < minIdentifiersCounter;
	}
	bool isIdentifier(uint pos) {
		return getLexemeCode(pos) >= minIdentifiersCounter && getLexemeCode(pos) < minErrorCounter;
	}
	//bool isConstIntIdentifier(uint pos) {
	//	return getLexemeCode(pos) >= minConstCounter && getLexemeCode(pos) < minIdentifiersCounter;
	//}
	//bool isIdentifier(uint pos) {
	//	return getLexemeCode(pos) >= minConstCounter && getLexemeCode(pos) < minIdentifiersCounter;
	//}

};


class Lexer { // lexical analyzer
public:
	Lexer() = delete;
	Lexer(LexemeTables& tables) : m_tables(tables), keyWordsCounter(tables.minKeyWordsCounter),
		constCounter(tables.minConstCounter), identifiersCounter(tables.minIdentifiersCounter),
		separatorsCounter(tables.minSeparatorsCounter), errorCounter(tables.minErrorCounter),
		startErrorCounter(tables.minStartErrorCounter) {}

	~Lexer() = default;
	void startLexer(const std::string file_name, std::ostream &out, const uint tab = 4);
	void print_lexemeTable(std::ostream &out);
	void print_errorLexemeTable(std::ostream &out);
	void setTab(uint tab);

private:

	void initAttributes();
	void initKeyWords();
	void readInputSigFile(const std::string file_name);
	void countCurrentPos(const char &character);
	void push_back_token(const uint code, const size_t row, const size_t col, const std::string &name);
	void compare_push_back_lexeme_to_tables(std::unordered_map<std::string, uint> &codeNameTable,
											std::string &bufToken, uint &codeNameCounter);

	void INP(const char &character); // entering the next character
	void letter_process(); // processing identifier token = 1
	void digit_process(); // processing number token = 2
	void delimiter_process(); // processing separator token = 3
	void comment_process(); // processing and deleting comments = 4
	void space_process(); // skipping the next space character = 0
	void error_process(const std::string &bufTokenFromAnotherCategory = "");; // errors processing = 5

	uint searchTokenFromTable(const std::unordered_map<std::string, uint> &infoTable, const std::string &bufToken) const;
	
	enum AttributesCode {
		CODE_SPACE,				// space symbols = 0
		CODE_IDENTIFIER,		// identifiers and key words symbols = 1
		CODE_NUMBER,			// number symbols = 2
		CODE_SEPARATOR,			// separator symbols = 3
		CODE_COMMENT,			// start comment symbol = 4
		CODE_ERROR				// error (inadmissible) symbols = 5
	} Attributes[128]; // array for ASCII code symbols
	
	uint keyWordsCounter;
	uint constCounter;
	uint identifiersCounter;
	uint separatorsCounter;
	uint errorCounter;
	uint startErrorCounter;

	size_t currentRow = 1;
	size_t currentCol = 1;

	uint tabulation = 0;

	std::ifstream sig_file;

	// working temporary variables
	char temp = 0;							// for every character from file
	size_t startRow = 1;					// for calculating token positions
	size_t startCol = 1;					// for calculating token positions
	uint lexemeCodeFromTable = 0; // for checking lexemes in tables

	LexemeTables &m_tables;
};