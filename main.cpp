#include "LexicalAnalyzer.h"
#include "SyntaxAnalyzer.h"

#include <iostream>
#include <fstream>

int main() {

	try {
		std::ofstream lex_file_out1;
		lex_file_out1.open("test/generated_lexemes1.txt");
		if (!lex_file_out1.is_open())
			throw std::runtime_error("Impossible to open the generated_lexemes1 file_out");

		/*std::ofstream lex_file_out2;
		lex_file_out2.open("test/generated_lexemes2.txt", std::ios::out);
		if (!lex_file_out2.is_open())
			throw std::runtime_error("Impossible to open the generated_lexemes2 file_out");

		std::ofstream lex_file_out3;
		lex_file_out3.open("test/generated_lexemes3.txt", std::ios::out);
		if (!lex_file_out3.is_open())
			throw std::runtime_error("Impossible to open the generated_lexemes3 file_out");

		std::ofstream lex_file_out4;
		lex_file_out4.open("test/generated_lexemes4.txt", std::ios::out);
		if (!lex_file_out4.is_open())
			throw std::runtime_error("Impossible to open the generated_lexemes4 file_out");

		std::ofstream lex_file_out5;
		lex_file_out5.open("test/generated_lexemes5.txt", std::ios::out);
		if (!lex_file_out5.is_open())
			throw std::runtime_error("Impossible to open the generated_lexemes5 file_out");

		std::ofstream lex_file_out6;
		lex_file_out6.open("test/generated_lexemes6.txt", std::ios::out);
		if (!lex_file_out6.is_open())
			throw std::runtime_error("Impossible to open the generated_lexemes6 file_out");

		std::ofstream lex_file_out7;
		lex_file_out7.open("test/generated_lexemes7.txt", std::ios::out);
		if (!lex_file_out7.is_open())
			throw std::runtime_error("Impossible to open the generated_lexemes7 file_out");

		std::ofstream lex_file_out8;
		lex_file_out8.open("test/generated_lexemes8.txt", std::ios::out);
		if (!lex_file_out8.is_open())
			throw std::runtime_error("Impossible to open the generated_lexemes8 file_out");

		std::ofstream lex_file_out9;
		lex_file_out9.open("test/generated_lexemes9.txt", std::ios::out);
		if (!lex_file_out9.is_open())
			throw std::runtime_error("Impossible to open the generated_lexemes9 file_out");

		std::ofstream lex_file_out10;
		lex_file_out10.open("test/generated_lexemes10.txt", std::ios::out);
		if (!lex_file_out10.is_open())
			throw std::runtime_error("Impossible to open the generated_lexemes10 file_out");*/

		LexemeTables t1Tables, t2Tables, t3Tables, t4Tables, t5Tables, t6Tables, t7Tables, t8Tables, t9Tables, t10Tables;

		Lexer s1(t1Tables);
		s1.startLexer("test1", lex_file_out1);
		/*Lexer s2(t2Tables);
		s2.startLexer("test2", lex_file_out2);
		Lexer s3(t3Tables);
		s3.startLexer("test3", lex_file_out3);
		Lexer s4(t4Tables);
		s4.startLexer("test4", lex_file_out4);
		Lexer s5(t5Tables);
		s5.startLexer("test5", lex_file_out5);
		Lexer s6(t6Tables);
		s6.startLexer("test6", lex_file_out6);
		Lexer s7(t7Tables);
		s7.startLexer("test7", lex_file_out7);
		Lexer s8(t8Tables);
		s8.startLexer("test8", lex_file_out8);
		Lexer s9(t9Tables);
		s9.startLexer("test9", lex_file_out9);
		Lexer s10(t10Tables);
		s10.startLexer("test10", lex_file_out10);*/

		std::ofstream synt_file_out1;
		synt_file_out1.open("test/generated_syntax1.txt", std::ios::out);
		if (!synt_file_out1.is_open())
			throw std::runtime_error("Impossible to open the generated_syntax1 file_out");

		/*std::ofstream synt_file_out2;
		synt_file_out2.open("test/generated_syntax2.txt", std::ios::out);
		if (!synt_file_out2.is_open())
			throw std::runtime_error("Impossible to open the generated_syntax2 file_out");

		std::ofstream synt_file_out3;
		synt_file_out3.open("test/generated_syntax3.txt", std::ios::out);
		if (!synt_file_out3.is_open())
			throw std::runtime_error("Impossible to open the generated_syntax3 file_out");

		std::ofstream synt_file_out4;
		synt_file_out4.open("test/generated_syntax4.txt", std::ios::out);
		if (!synt_file_out4.is_open())
			throw std::runtime_error("Impossible to open the generated_syntax4 file_out");

		std::ofstream synt_file_out5;
		synt_file_out5.open("test/generated_syntax5.txt", std::ios::out);
		if (!synt_file_out5.is_open())
			throw std::runtime_error("Impossible to open the generated_syntax5 file_out");

		std::ofstream synt_file_out6;
		synt_file_out6.open("test/generated_syntax6.txt", std::ios::out);
		if (!synt_file_out6.is_open())
			throw std::runtime_error("Impossible to open the generated_syntax6 file_out");

		std::ofstream synt_file_out7;
		synt_file_out7.open("test/generated_syntax7.txt", std::ios::out);
		if (!synt_file_out7.is_open())
			throw std::runtime_error("Impossible to open the generated_syntax7 file_out");

		std::ofstream synt_file_out8;
		synt_file_out8.open("test/generated_syntax8.txt", std::ios::out);
		if (!synt_file_out8.is_open())
			throw std::runtime_error("Impossible to open the generated_syntax8 file_out");

		std::ofstream synt_file_out9;
		synt_file_out9.open("test/generated_syntax9.txt", std::ios::out);
		if (!synt_file_out9.is_open())
			throw std::runtime_error("Impossible to open the generated_syntax9 file_out");

		std::ofstream synt_file_out10;
		synt_file_out10.open("test/generated_syntax10.txt", std::ios::out);
		if (!synt_file_out10.is_open())
			throw std::runtime_error("Impossible to open the generated_syntax10 file_out");*/
		
		SyntaxAnalyzer s1P(t1Tables);
		s1P.start();
		s1P.printTree(synt_file_out1);

		/*SyntaxAnalyzer s2P(t2Tables);
		s2P.start();
		s2P.printTree(synt_file_out2);

		SyntaxAnalyzer s3P(t3Tables);
		s3P.start();
		s3P.printTree(synt_file_out3);

		SyntaxAnalyzer s4P(t4Tables);
		s4P.start();
		s4P.printTree(synt_file_out4);

		SyntaxAnalyzer s5P(t5Tables);
		s5P.start();
		s5P.printTree(synt_file_out5);

		SyntaxAnalyzer s6P(t6Tables);
		s6P.start();
		s6P.printTree(synt_file_out6);

		SyntaxAnalyzer s7P(t7Tables);
		s7P.start();
		s7P.printTree(synt_file_out7);

		SyntaxAnalyzer s8P(t8Tables);
		s8P.start();
		s8P.printTree(synt_file_out8);

		SyntaxAnalyzer s9P(t9Tables);
		s9P.start();
		s9P.printTree(synt_file_out9);

		SyntaxAnalyzer s10P(t10Tables);
		s10P.start();
		s10P.printTree(synt_file_out10);*/
		
		std::cout << "\nALL INFORMATION WRITEN TO FILES" << std::endl;
	}
	catch (std::exception &ex) {
		std::cout << "\n" << ex.what() << std::endl;
	}
	catch (...) {
		exit(1);
	}

	return 0;
}