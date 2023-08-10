#ifndef _MATH_CALC_INTERPRETER_H_
#define _MATH_CALC_INTERPRETER_H_
#pragma once

#include <iostream>
#include "parse_tree.h"

class Interpreter {
public:
	Interpreter();
	~Interpreter();

	int interpret(ParseTree& tree);
private:
	void resolv(Binop* root);
	bool is_operator(const char* c);
};

#endif // !_MATH_CALC_INTERPRETER_H_
