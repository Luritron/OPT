#include "SyntaxAnalyzer.h"
#include <string>
#include <iostream>

bool SyntaxAnalyzer::identifier(node& subtree, int pos) {	//?
	if (!tables.isIdentifier(pos))
	{
		Errors(6, pos);
		return false;
	}
	node t1;
	t1.name = "<identifier>";
	node t2;
	t2.lexemeId = pos;
	t1.children.push_back(t2);
	subtree.children.push_back(t1);
}

bool SyntaxAnalyzer::labels_list(node& subtree, int pos) {
	if (tables.isComma(pos)) {
		node l1;
		l1.lexemeId = pos;
		subtree.children.push_back(l1);
		tables.lexemes[pos].parsed = true;
		pos++;
		if (!tables.isConstIntIdentifier(pos)) {	//?
			Errors(8, pos);
			return false;
		}
		node l2;
		l2.lexemeId = pos;
		subtree.children.push_back(l2);
		tables.lexemes[pos].parsed = true;
		node ll4;
		ll4.name = "<labels--list>";
		if (!labels_list(ll4, pos + 1))
			return false;
		if (ll4.children.size() == 0) {
			node llt;
			llt.name = "<empty>";
			ll4.children.push_back(llt);
		}
		subtree.children.push_back(ll4);
		return true;
	}
	return true;
}

bool SyntaxAnalyzer::labels_declarations(node& subtree, int pos) {
	if (!tables.isLabel(pos)) {
		node ll1;
		ll1.name = "<empty>";
		subtree.children.push_back(ll1);
		return true;
	}
	node ll11;
	ll11.lexemeId = pos;
	subtree.children.push_back(ll11);
	tables.lexemes[pos].parsed = true;
	pos++;
	if (!tables.isConstIntIdentifier(pos)) {	//?
		Errors(8, pos);
		return false;
	}
	node ll2;
	ll2.lexemeId = pos;
	tables.lexemes[pos].parsed = true;
	subtree.children.push_back(ll2);
	pos++;
	node ll4;
	ll4.name = "<labels--list>";
	if (!labels_list(ll4, pos))
		return false;
	if (ll4.children.size() == 0) {
		node llt;
		llt.name = "<empty>";
		ll4.children.push_back(llt);
	}
	subtree.children.push_back(ll4);
	while (pos < tables.lexemes.size() - 1 && tables.lexemes[pos].parsed)
		pos++;
	if (!tables.isSemicolon(pos)) {
		Errors(2, pos);
		return false;
	}
	node ll3;
	ll3.lexemeId = pos;
	tables.lexemes[pos].parsed = true;
	subtree.children.push_back(ll3);
}

bool SyntaxAnalyzer::statement(node& subtree, int pos) {
	node st1;
	st1.name = "<statement>";
	if (tables.isConstIntIdentifier(pos)) {	//?
		node st2;
		st2.lexemeId = pos;
		tables.lexemes[pos].parsed = true;
		st1.children.push_back(st2);
		pos++;
		if (!tables.isColon(pos))
		{
			Errors(7, pos);
			return false;
		}
		node st3;
		st3.lexemeId = pos;
		tables.lexemes[pos].parsed = true;
		st1.children.push_back(st3);
		pos++;
		subtree.children.push_back(st1);
		node st7;
		st7.name = "<statements-list>";
		if (!statement(st7, pos))
			return false;
		if (st7.children.size() == 0) {
			node stt;
			stt.name = "<empty>";
			st7.children.push_back(stt);
		}
		subtree.children.push_back(st7);
		return true;
	}
	if (tables.isGoto(pos) || tables.isIn(pos) || tables.isOut(pos)) {
		node st2;
		st2.lexemeId = pos;
		tables.lexemes[pos].parsed = true;
		st1.children.push_back(st2);
		pos++;
		if (!tables.isConstIntIdentifier(pos)) {	//?
			Errors(8, pos);
			return false;
		}
		node st3;
		st3.lexemeId = pos;
		tables.lexemes[pos].parsed = true;
		st1.children.push_back(st3);
		pos++;
		if (!tables.isSemicolon(pos))
		{
			Errors(2, pos);
			return false;
		}
		node st4;
		st4.lexemeId = pos;
		tables.lexemes[pos].parsed = true;
		st1.children.push_back(st4);
		pos++;
		subtree.children.push_back(st1);
		node st7;
		st7.name = "<statements-list>";
		if (!statement(st7, pos))
			return false;
		if (st7.children.size() == 0) {
			node stt;
			stt.name = "<empty>";
			st7.children.push_back(stt);
		}
		subtree.children.push_back(st7);
		return true;
	}
	if (tables.isLink(pos)) {
		node st2;
		st2.lexemeId = pos;
		tables.lexemes[pos].parsed = true;
		st1.children.push_back(st2);
		pos++;
		if (!tables.isIdentifier(pos)) {	//!
			Errors(6, pos);
			return false;
		}
		node st3;
		st3.name = "<variable-identifier>";
		identifier(st3, pos);
		tables.lexemes[pos].parsed = true;
		st1.children.push_back(st3);
		pos++;
		if (!tables.isComma(pos))
		{
			Errors(9, pos);
			return false;
		}
		node st4;
		st4.lexemeId = pos;
		tables.lexemes[pos].parsed = true;
		st1.children.push_back(st4);
		pos++;
		if (!tables.isConstIntIdentifier(pos)) {	//?
			Errors(8, pos);
			return false;
		}
		node st5;
		st5.lexemeId = pos;
		tables.lexemes[pos].parsed = true;
		st1.children.push_back(st5);
		pos++;
		if (!tables.isSemicolon(pos))
		{
			Errors(2, pos);
			return false;
		}
		node st6;
		st6.lexemeId = pos;
		tables.lexemes[pos].parsed = true;
		st1.children.push_back(st6);
		pos++;
		subtree.children.push_back(st1);
		node st7;
		st7.name = "<statements-list>";
		if (!statement(st7, pos))
			return false;
		if (st7.children.size() == 0) {
			node stt;
			stt.name = "<empty>";
			st7.children.push_back(stt);
		}
		subtree.children.push_back(st7);
		return true;
	}
	return true;
}

bool SyntaxAnalyzer::block(node& subtree, int pos) {
	node bl1;
	bl1.name = "<declarations>";
	node bl2;
	bl2.name = "<label-declarations>";
	if (!labels_declarations(bl2, pos))
		return false;
	bl1.children.push_back(bl2);
	subtree.children.push_back(bl1);
	while (pos < tables.lexemes.size() - 1 && tables.lexemes[pos].parsed)
		pos++;
	if (!tables.isBegin(pos)) {
		Errors(4, pos);
		return false;
	}
	node bl3;
	bl3.lexemeId = pos;
	tables.lexemes[pos].parsed = true;
	subtree.children.push_back(bl3);
	pos++;


	node bl4;
	bl4.name = "<statements-list>";
	if (!statement(bl4, pos))
		return false;
	if (bl4.children.size() == 0) {
		node blt;
		blt.name = "<empty>";
		bl4.children.push_back(blt);
	}
	subtree.children.push_back(bl4);

	while (pos < tables.lexemes.size() - 1 && tables.lexemes[pos].parsed)
		pos++;
	if (!tables.isEnd(pos)) {
		Errors(5, pos);
		return false;
	}
	node bl5;
	bl5.lexemeId = pos;
	tables.lexemes[pos].parsed = true;
	subtree.children.push_back(bl5);
	return true;
}

bool SyntaxAnalyzer::program(node& subtree, int pos) {
	if (!tables.isProgram(pos)) {
		Errors(3, pos);
		return false;
	}
	node pr1;
	pr1.lexemeId = pos;
	//tables.lexemes[pos].parsed = true;
	subtree.children.push_back(pr1);
	pos++;
	if (!tables.isIdentifier(pos)) {	//!
		Errors(6, pos);
		return false;
	}
	node pr2;
	pr2.name = "<procedure-identifier>";
	identifier(pr2, pos);
	//tables.lexemes[pos].parsed = true;
	subtree.children.push_back(pr2);
	pos++;
	if (!tables.isSemicolon(pos)) {
		Errors(2, pos);
		return false;
	}
	node pr3;
	pr3.lexemeId = pos;
	//tables.lexemes[pos].parsed = true;
	subtree.children.push_back(pr3);

	pos++;
	node pr4;
	pr4.name = "<block>";
	if (!block(pr4, pos))
		return false;
	subtree.children.push_back(pr4);
	while (pos < tables.lexemes.size() - 1 && tables.lexemes[pos].parsed)
		pos++;
	if (!tables.isDot(pos)) {
		Errors(1, pos);
		return false;
	}
	node pr5;
	pr5.lexemeId = pos++;
	subtree.children.push_back(pr5);
	return true;
}

void SyntaxAnalyzer::start() {
	syntaxTreeRoot.name = "<signal-program>";
	syntaxTreeRoot.lexemeId = -1;
	node child;
	child.name = "<program>";
	child.lexemeId = -1;
	syntaxTreeRoot.children.push_back(child);
	int pos = 0;
	try {
		program(syntaxTreeRoot.children[0], pos);
	}
	catch (std::out_of_range)
	{
		std::cout << "[ERROR] Pos is out of vector lexemes. Pos is " << pos << ". Vector of lexemes size is " << tables.lexemes.size() << "\n";
		exit(-1);
	}
}

void SyntaxAnalyzer::printTree(std::ostream& out)
{
	printSubTree(out, syntaxTreeRoot, 0);
	out << std::endl << errorStr;
}

void SyntaxAnalyzer::printSubTree(std::ostream& out, node& subtree, int depth)
{
	std::string buffer;
	for (int i = 0; i < depth; i++)
		buffer += "--";
	if (subtree.name != "")
		buffer += subtree.name;
	else
		buffer += std::to_string(tables.lexemes[subtree.lexemeId].code) + " " + tables.lexemes[subtree.lexemeId].name;
	out << buffer << std::endl;
	for (int i = 0; i < subtree.children.size(); i++)
		printSubTree(out, subtree.children[i], depth + 1);
}

void SyntaxAnalyzer::Errors(int error_code, int pos) {
	switch (error_code) {
	case 1:	// Dot												// error with END.
		errorStr += "Syntactic error on Line ";
		errorStr += std::to_string(tables.lexemes[pos].row);
		errorStr += " Column ";
		errorStr += std::to_string(tables.lexemes[pos].col);
		errorStr += ": \".\" is passed after the END\n";
		break;
	case 2:	// Semicolon
		errorStr += "Syntactic error on Line ";
		errorStr += std::to_string(tables.lexemes[pos].row);
		errorStr += " Column ";
		errorStr += std::to_string(tables.lexemes[pos].col);
		errorStr += ": \";\" is passed\n";
		break;
	case 3:	// Program
		errorStr += "Syntactic error on Line ";
		errorStr += std::to_string(tables.lexemes[pos].row);
		errorStr += " Column ";
		errorStr += std::to_string(tables.lexemes[pos].col);
		errorStr += ": Keyword \"PROGRAM\" is passed\n";
		break;
	case 4:	// Begin
		errorStr += "Syntactic error on Line ";
		errorStr += std::to_string(tables.lexemes[pos].row);
		errorStr += " Column ";
		errorStr += std::to_string(tables.lexemes[pos].col);
		errorStr += ": Keyword \"BEGIN\" is passed\n";
		break;
	case 5:	// End
		errorStr += "Syntactic error on Line ";
		errorStr += std::to_string(tables.lexemes[pos].row);
		errorStr += " Column ";
		errorStr += std::to_string(tables.lexemes[pos].col);
		errorStr += ": Keyword \"END\" is passed\n";
		break;
	case 6:	// Identifier
		errorStr += "Syntactic error on Line ";
		errorStr += std::to_string(tables.lexemes[pos].row);
		errorStr += " Column ";
		errorStr += std::to_string(tables.lexemes[pos].col);
		errorStr += ": Must be identifier\n";
		break;
	case 7:	// Colon
		errorStr += "Syntactic error on Line ";
		errorStr += std::to_string(tables.lexemes[pos].row);
		errorStr += " Column ";
		errorStr += std::to_string(tables.lexemes[pos].col);
		errorStr += ": \":\" is passed\n";
		break;
	case 8:	// Integer
		errorStr += "Syntactic error on Line ";
		errorStr += std::to_string(tables.lexemes[pos].row);
		errorStr += " Column ";
		errorStr += std::to_string(tables.lexemes[pos].col);
		errorStr += ": Must be unsigned integer\n";
		break;
	case 9:	// Comma
		errorStr += "Syntactic error on Line ";
		errorStr += std::to_string(tables.lexemes[pos].row);
		errorStr += " Column ";
		errorStr += std::to_string(tables.lexemes[pos].col);
		errorStr += ": \",\" is passed\n";
		break;
	case 10:	// Label
		errorStr += "Syntactic error on Line ";
		errorStr += std::to_string(tables.lexemes[pos].row);
		errorStr += " Column ";
		errorStr += std::to_string(tables.lexemes[pos].col);
		errorStr += ": LABEL is passed\n";
		break;
	}
}
