#ifndef _MATH_CALC_LEXER_H
#define _MATH_CALC_LEXER_H
#pragma once

#include <vector>

typedef struct _Token {
	char* type;
	char* value;
} Token;

class Lexer {
public:
	Lexer();
	Lexer(const char* str);
	~Lexer();

	int tokenize(const char* str);
	const std::vector<Token*>& get_tokens(void) const;
private:
	std::vector<Token*> tokens;
	int add_token(const char* type, const char* value);
	const char* check_symbol(const char* sym);
	int is_constant(const char* c);
	int is_function(const char* f);
};

#endif // !_MATH_CALC_LEXER
