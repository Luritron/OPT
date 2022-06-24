#pragma once

#include "lexicalAnalyzer.h"


struct node {
	std::string name;
	int lexemeId;
	std::vector<node> children;
};

class SyntaxAnalyzer {
public:
	explicit SyntaxAnalyzer(LexemeTables& _tables) : tables(_tables) { }
	
	void start();
	void printTree(std::ostream& out);

private:
	bool identifier(node& subtree, int pos);
	bool labels_list(node& subtree, int pos);
	bool labels_declarations(node& subtree, int pos);
	bool statement(node& subtree, int pos);
	bool block(node& subtree, int pos);
	bool program(node& subtree, int pos);	// delete pos

	void printSubTree(std::ostream& out, node& subtree, int depth);

	void Errors(int p, int pos);

	LexemeTables tables;

	node syntaxTreeRoot;
	
	bool err = false;
	bool err1 = false;

	std::string errorStr = "";
	//int pos;
};
