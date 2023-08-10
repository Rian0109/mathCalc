#ifndef _MATH_CALC_PARSER_H
#define _MATH_CALC_PARSER_H
#pragma once

#include <stack>
#include <vector>
#include "lexer.h"
#include "parse_tree.h"

class Parser  {
public:
	Parser();
	Parser(std::vector<Token*>& tks);
	~Parser();

	ParseTree& parse(std::vector<Token*>& tks);
	void show_expresion(void) const;
	ParseTree& get_parse_tree(void);
private:
	ParseTree parse_tree;
	std::vector<char*> mathexp;
	std::stack<Binop*> node_stack;
	int check_expresion(std::vector<Token*>& tks);
	int eval(std::vector<Token*>& tks);
	//Binop* generate_parse_tree(Binop* root, std::vector<char*>::iterator ptr, std::vector<char*>::iterator end, std::vector<char*>*);
	int generate_parse_tree_it(std::vector<char*> mvec);
	const char* getResult(std::vector<char*> mvtemp, int it);
	bool is_operator(const char* c);
};

#endif // _MATH_CALC_PARSER_H
